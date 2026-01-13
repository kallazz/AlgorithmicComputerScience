import sys
import numpy as np
from typing import Tuple

def read_tga(filename: str) -> Tuple[bytes, np.ndarray, int, int]:
    """
    Reads a TGA file, handling the header, optional Image ID, and pixel data.
    Ignores the TGA footer by reading only the required number of bytes.
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
            raise ValueError(f"Unsupported bit depth: {depth}. Only 24 or 32-bit TGA files are supported.")

        # Skip Image ID field if present
        if id_length > 0:
            f.read(id_length)
            
        # Calculate exact number of bytes for pixel data
        bytes_per_pixel = depth // 8
        num_pixels = width * height
        expected_bytes = num_pixels * bytes_per_pixel
        
        # Read only the pixel data, effectively ignoring potential TGA footer
        raw_data = f.read(expected_bytes)
        if len(raw_data) < expected_bytes:
            raise ValueError("File contains less pixel data than specified in header.")
            
        data = np.frombuffer(raw_data, dtype=np.uint8)
        
        # Reshape to (height, width, BGR/BGRA)
        pixels = data.reshape((height, width, bytes_per_pixel))
        
        # Prepare a clean header for the output file (resetting ID length to 0)
        out_header = bytearray(header)
        out_header[0] = 0
        
        # Return only the BGR channels for quantization (ignoring Alpha)
        return bytes(out_header), pixels[:, :, :3].astype(np.float64), width, height

def save_tga(filename: str, header: bytes, pixels: np.ndarray) -> None:
    """
    Saves the quantized pixel data into a TGA file using the provided header.
    """
    with open(filename, 'wb') as f:
        f.write(header)
        # Clip values to valid range [0, 255] and convert back to uint8
        out_pixels = np.clip(pixels, 0, 255).astype(np.uint8)
        f.write(out_pixels.tobytes())

def calculate_mse(original: np.ndarray, quantized: np.ndarray) -> float:
    """
    Calculates the Mean Squared Error for the entire image.
    """
    return float(np.mean((original - quantized) ** 2))

def calculate_snr(original: np.ndarray, mse: float) -> Tuple[float, float]:
    """
    Calculates the Signal-to-Noise Ratio in linear scale and decibels.
    """
    signal_power = np.mean(original ** 2)
    if mse == 0:
        return float('inf'), float('inf')
    snr_linear = float(signal_power / mse)
    snr_db = float(10 * np.log10(snr_linear))
    return snr_linear, snr_db

def lbg_quantization(pixels: np.ndarray, num_bits: int) -> np.ndarray:
    """
    Performs Vector Quantization using the Linde-Buzo-Gray (LBG) algorithm
    with the Taxicab (L1) metric.
    """
    # Flatten image to a list of BGR vectors (N x 3)
    vectors = pixels.reshape(-1, 3)
    target_count = 2 ** num_bits
    
    # Initialize with the mean of all pixels (1st centroid)
    centroids = np.array([np.mean(vectors, axis=0)])
    
    epsilon = 0.01   # Centroid splitting parameter
    threshold = 0.001 # Convergence threshold
    
    print(f"Starting LBG algorithm for 2^{num_bits} = {target_count} colors...")

    for i in range(num_bits):
        # Splitting: Double the current number of centroids
        centroids = np.vstack([centroids * (1 + epsilon), centroids * (1 - epsilon)])
        
        prev_distortion = 0.0
        while True:
            # Assignment step using Taxicab Metric (L1 distance)
            # diff shape: (num_pixels, num_centroids, 3)
            diff = np.abs(vectors[:, np.newaxis, :] - centroids)
            distances = diff.sum(axis=2) # L1 distance sum
            labels = np.argmin(distances, axis=1)
            
            # Update step: Centroids move to the mean of assigned vectors
            new_centroids = np.zeros_like(centroids)
            for k in range(len(centroids)):
                mask = (labels == k)
                if np.any(mask):
                    new_centroids[k] = np.mean(vectors[mask], axis=0)
                else:
                    # If a cluster is empty, re-seed it with a random pixel
                    new_centroids[k] = vectors[np.random.randint(len(vectors))]
            
            centroids = new_centroids
            
            # Use MSE to check for convergence (distortion change)
            current_distortion = np.mean(np.sum((vectors - centroids[labels])**2, axis=1))
            if prev_distortion > 0 and abs(prev_distortion - current_distortion) / prev_distortion < threshold:
                break
            prev_distortion = float(current_distortion)
            
        print(f"Level reached: 2^{i+1} colors")

    # Final assignment to the calculated codebook
    final_diff = np.abs(vectors[:, np.newaxis, :] - centroids)
    final_labels = np.argmin(final_diff.sum(axis=2), axis=1)
    quantized_vectors = centroids[final_labels]
    
    return quantized_vectors.reshape(pixels.shape)

def main() -> None:
    if len(sys.argv) != 4:
        print("Usage: python3 script.py <input.tga> <output.tga> <bits>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]
    try:
        bits = int(sys.argv[3])
    except ValueError:
        print("Error: The number of bits must be an integer.")
        sys.exit(1)

    try:
        # Load image
        header, pixels, w, h = read_tga(input_path)
        print(f"Image loaded: {w}x{h}")
        
        original_pixels = pixels.copy()
        
        # Execute LBG Quantization
        quantized_pixels = lbg_quantization(pixels, bits)
        
        # Compute quality metrics
        mse = calculate_mse(original_pixels, quantized_pixels)
        snr_linear, snr_db = calculate_snr(original_pixels, mse)
        
        # Save the result
        save_tga(output_path, header, quantized_pixels)
        
        # Results output
        print(f"\nmse = {mse:.6f}")
        print(f"SNR = {snr_linear:.6f} ({snr_db:.6f}dB)")

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()