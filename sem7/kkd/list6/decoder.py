import numpy as np
import sys
import pickle
from typing import Dict, Tuple, List

def write_tga(filename: str, header: bytes, image: np.ndarray) -> None:
    """Saves image in TGA format."""
    with open(filename, 'wb') as f:
        f.write(header)
        img_data = np.clip(np.round(image), 0, 255).astype(np.uint8)
        f.write(img_data.tobytes())

def expand(y: np.ndarray, alpha: float) -> np.ndarray:
    """Inverse of nonlinear transformation."""
    return np.sign(y) * (np.abs(y) ** (1/alpha))

def dequantize(indices: np.ndarray, step: float, t_min: float, alpha: float) -> np.ndarray:
    """Dequantization - inverse of non_uniform_quantize."""
    recon_t = indices * step + t_min
    return expand(recon_t, alpha)

def decode_channel(encoded: Dict) -> np.ndarray:
    """Decodes one channel from encoded data."""
    h, w = encoded['shape']
    work_w = encoded['work_w']
    
    # Dequantize L_diff
    L_diff_q = dequantize(
        encoded['L_indices'],
        encoded['L_step'],
        encoded['L_tmin'],
        alpha=0.8
    )
    
    # DPCM decoding (L band reconstruction)
    L_recon = np.cumsum(L_diff_q, axis=1)
    
    # Dequantize H
    H_q = dequantize(
        encoded['H_indices'],
        encoded['H_step'],
        encoded['H_tmin'],
        alpha=0.5
    )
    
    # Signal reconstruction (Synthesis)
    recon_channel = np.zeros((h, w))
    recon_channel[:, 0:work_w:2] = L_recon + H_q
    recon_channel[:, 1:work_w:2] = L_recon - H_q
    
    # If width was odd, last column remains zero
    # (or can be copied from second-to-last)
    if work_w < w:
        recon_channel[:, w-1] = recon_channel[:, w-2]
    
    return recon_channel

def calculate_stats(orig: np.ndarray, decoded: np.ndarray) -> Tuple[float, List[float], float]:
    """Calculates MSE and SNR statistics."""
    mse_total = np.mean((orig - decoded) ** 2)
    mse_per_channel = [np.mean((orig[:,:,i] - decoded[:,:,i]) ** 2) for i in range(3)]
    
    # SNR = 10 * log10( MSE_original_signal / MSE_noise )
    signal_power = np.mean(orig ** 2)
    noise_power = mse_total
    snr = 10 * np.log10(signal_power / noise_power) if noise_power > 0 else float('inf')
    
    return mse_total, mse_per_channel, snr

def main() -> None:
    if len(sys.argv) < 3:
        print("Usage: python decoder.py <input_file.enc> <output_file.tga> [original_file.tga]")
        return
    
    input_path = sys.argv[1]
    output_path = sys.argv[2]
    original_path = sys.argv[3] if len(sys.argv) > 3 else None
    
    # Read encoded data
    try:
        with open(input_path, 'rb') as f:
            encoded_data = pickle.load(f)
    except Exception as e:
        print(f"Error reading encoded file: {e}")
        return
    
    # Decode channels
    height = encoded_data['height']
    width = encoded_data['width']
    k = encoded_data['k']
    
    decoded_img = np.zeros((height, width, 3))
    
    for c in range(3):
        decoded_img[:, :, c] = decode_channel(encoded_data['channels'][c])
    
    # Save
    write_tga(output_path, encoded_data['header'], decoded_img)
    print(f"Decoded image {width}x{height} with k={k}")
    print(f"Saved to: {output_path}")
    
    # Statistics (if original file provided)
    if original_path:
        try:
            from encoder import read_tga
            _, orig_pixels, _, _ = read_tga(original_path)
            mse_t, mse_c, snr = calculate_stats(orig_pixels, decoded_img)
            
            print(f"\n--- Statistics for k={k} ---")
            print(f"Total MSE: {mse_t:.4f}")
            print(f"MSE Channel B: {mse_c[0]:.4f}")
            print(f"MSE Channel G: {mse_c[1]:.4f}")
            print(f"MSE Channel R: {mse_c[2]:.4f}")
            print(f"SNR: {snr:.4f} dB")
        except Exception as e:
            print(f"Cannot calculate statistics: {e}")

if __name__ == "__main__":
    main()