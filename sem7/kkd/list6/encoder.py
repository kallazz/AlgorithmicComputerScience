import numpy as np
import sys
import pickle
from typing import Tuple, Dict

def read_tga(filename: str) -> Tuple[bytes, np.ndarray, int, int]:
    """
    Reads a TGA file, handling header, optional Image ID and pixel data.
    Ignores TGA footer.
    Returns BGR header (24-bit), data (float64), width and height.
    """
    with open(filename, 'rb') as f:
        header = f.read(18)
        if len(header) < 18:
            raise ValueError("Invalid TGA header.")
        
        id_length = header[0]
        width = header[12] + (header[13] << 8)
        height = header[14] + (header[15] << 8)
        depth = header[16]
        
        if depth not in [24, 32]:
            raise ValueError(f"Unsupported bit depth: {depth}. Only 24 or 32 bits.")
        
        if id_length > 0:
            f.read(id_length)
        
        bytes_per_pixel = depth // 8
        num_pixels = width * height
        expected_bytes = num_pixels * bytes_per_pixel
        raw_data = f.read(expected_bytes)
        
        if len(raw_data) < expected_bytes:
            raise ValueError("File contains less data than declared in header.")
        
        data = np.frombuffer(raw_data, dtype=np.uint8)
        pixels = data.reshape((height, width, bytes_per_pixel))
        
        # Prepare output header (force 24 bits and no ID)
        out_header = bytearray(header)
        out_header[0] = 0  # ID length = 0
        out_header[16] = 24  # Force 24-bit output
        
        # Return only BGR channels (cut Alpha if exists)
        return bytes(out_header), pixels[:, :, :3].astype(np.float64), width, height

def compand(x: np.ndarray, alpha: float) -> np.ndarray:
    """Nonlinear transformation (companding)."""
    return np.sign(x) * (np.abs(x) ** alpha)

def non_uniform_quantize(data: np.ndarray, k: int, min_val: float, max_val: float, alpha: float) -> Tuple[np.ndarray, float, float]:
    """Non-uniform quantization using companding."""
    levels = 2**k
    
    # Transform to nonlinear space
    t_data = compand(data, alpha)
    t_min = compand(min_val, alpha)
    t_max = compand(max_val, alpha)
    
    # Uniform quantization in transformed space
    step = (t_max - t_min) / (levels - 1)
    indices = np.round((t_data - t_min) / step).astype(np.int32)
    indices = np.clip(indices, 0, levels - 1)
    
    return indices, step, t_min

def encode_channel(channel: np.ndarray, k: int) -> Dict:
    """Encodes one channel returning quantized data."""
    h, w = channel.shape
    work_w = w if w % 2 == 0 else w - 1
    
    # 1. Split into subbands (Filtering)
    even_columns = channel[:, 0:work_w:2]
    odd_columns = channel[:, 1:work_w:2]
    
    L = (even_columns + odd_columns) / 2.0  # Low band (average)
    H = (even_columns - odd_columns) / 2.0  # High band (difference)
    
    # 2. Encode L band (DPCM)
    L_diff = np.zeros_like(L)
    L_diff[:, 0] = L[:, 0]
    L_diff[:, 1:] = L[:, 1:] - L[:, :-1]
    
    # Quantize L_diff
    L_indices, L_step, L_tmin = non_uniform_quantize(L_diff, k, -255, 255, alpha=0.8)
    
    # 3. Encode H band
    H_indices, H_step, H_tmin = non_uniform_quantize(H, k, -128, 128, alpha=0.5)
    
    return {
        'L_indices': L_indices,
        'L_step': L_step,
        'L_tmin': L_tmin,
        'H_indices': H_indices,
        'H_step': H_step,
        'H_tmin': H_tmin,
        'work_w': work_w,
        'shape': channel.shape
    }

def main() -> None:
    if len(sys.argv) < 4:
        print("Usage: python encoder.py <input_file.tga> <output_file.enc> <k>")
        return
    
    input_path = sys.argv[1]
    output_path = sys.argv[2]
    k = int(sys.argv[3])
    
    if not (1 <= k <= 7):
        print("Parameter k must be in range 1-7")
        return
    
    # Read file
    try:
        header, pixels, width, height = read_tga(input_path)
    except Exception as e:
        print(f"Read error: {e}")
        return
    
    # Encode channels (B, G, R)
    encoded_data = {
        'header': header,
        'width': width,
        'height': height,
        'k': k,
        'channels': []
    }
    
    for c in range(3):
        encoded_channel = encode_channel(pixels[:, :, c], k)
        encoded_data['channels'].append(encoded_channel)
    
    # Save encoded data
    with open(output_path, 'wb') as f:
        pickle.dump(encoded_data, f)
    
    print(f"Encoded image {width}x{height} with k={k}")
    print(f"Saved to: {output_path}")

if __name__ == "__main__":
    main()