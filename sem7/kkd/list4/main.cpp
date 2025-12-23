#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstdint>
#include <stdexcept>

// --- DATA STRUCTURES ---

#pragma pack(push, 1)
struct TGAHeader {
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;
    uint16_t colorMapOrigin;
    uint16_t colorMapLength;
    uint8_t colorMapDepth;
    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t pixelDepth;
    uint8_t imageDescriptor;
};
#pragma pack(pop)

struct Pixel {
    uint8_t r, g, b;
};

struct Image {
    int width;
    int height;
    std::vector<Pixel> data;

    // Safe access with boundary check (ambient color: black)
    Pixel getPixel(int x, int y) const {
        if (x < 0 || y < 0 || x >= width || y >= height) {
            return {0, 0, 0};
        }
        return data[static_cast<size_t>(y) * width + x];
    }
};

struct Result {
    std::string methodName;
    double entropyTotal;
    double entropyRed;
    double entropyGreen;
    double entropyBlue;
};

// --- HELPER FUNCTIONS ---

// Load TGA (24/32 bits per pixel, uncompressed)
Image loadTGA(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    TGAHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(TGAHeader));

    if (header.imageType != 2) {
        throw std::runtime_error("Only uncompressed RGB images (type 2) are supported.");
    }

    if (header.idLength > 0) {
        file.ignore(header.idLength);
    }

    const int width = header.width;
    const int height = header.height;
    const int bitsPerPixel = header.pixelDepth;

    if (bitsPerPixel != 24 && bitsPerPixel != 32) {
        throw std::runtime_error("Only 24 or 32-bit images are supported.");
    }

    const int bytesPerPixel = bitsPerPixel / 8;
    const size_t dataSize = static_cast<size_t>(width) * height * bytesPerPixel;
    std::vector<uint8_t> rawData(dataSize);

    file.read(reinterpret_cast<char*>(rawData.data()), static_cast<std::streamsize>(dataSize));

    Image img;
    img.width = width;
    img.height = height;
    img.data.resize(static_cast<size_t>(width) * height);

    // Handle image orientation (top-left vs bottom-left)
    const bool isBottomUp = !(header.imageDescriptor & 0x20);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const int srcIdx = (isBottomUp ? (height - 1 - y) : y) * width * bytesPerPixel + x * bytesPerPixel;
            const size_t destIdx = static_cast<size_t>(y) * width + x;

            // TGA is usually BGR
            img.data[destIdx].b = rawData[srcIdx];
            img.data[destIdx].g = rawData[srcIdx + 1];
            img.data[destIdx].r = rawData[srcIdx + 2];
        }
    }

    return img;
}

double calculateShannonEntropy(const std::vector<long long>& histogram, const long long totalCount) {
    double entropy = 0.0;
    if (totalCount == 0) return 0.0;

    for (int i = 0; i < 256; ++i) {
        if (histogram[i] > 0) {
            const double p = static_cast<double>(histogram[i]) / totalCount;
            entropy -= p * std::log2(p);
        }
    }
    return entropy;
}

// Predictor logic
int predict(const int mode, const int W, const int N, const int NW) {
    switch (mode) {
        case 1:
            return W;
        case 2:
            return N;
        case 3:
            return NW;
        case 4:
            return N + W - NW;
        case 5:
            return N + (W - NW) / 2;
        case 6:
            return W + (N - NW) / 2;
        case 7:
            return (N + W) / 2;
        case 8: 
            // JPEG-LS (MED / LOCO-I)
            if (NW >= std::max(W, N)) return std::min(W, N);
            if (NW <= std::min(W, N)) return std::max(W, N);
            return W + N - NW;
        default:
            return 0;
    }
}

// Returns method name with the formula in parentheses
std::string getMethodName(const int mode) {
    switch (mode) {
        case 1:
            return "Predictor 1 (W)";
        case 2:
            return "Predictor 2 (N)";
        case 3:
            return "Predictor 3 (NW)";
        case 4:
            return "Predictor 4 (N+W-NW)";
        case 5:
            return "Predictor 5 (N+(W-NW)/2)";
        case 6:
            return "Predictor 6 (W+(N-NW)/2)";
        case 7:
            return "Predictor 7 ((N+W)/2)";
        case 8:
            return "New Std (JPEG-LS/MED)";
        default:
            return "Unknown";
    }
}

// --- MAIN ---

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc < 2) {
        std::cerr << "Error: No input file provided." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename.tga>" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];

    try {
        const Image image = loadTGA(filename);
        const long long pixelCount = static_cast<long long>(image.width) * image.height;
        const long long totalSamples = pixelCount * 3;

        std::cout << "File analysis: " << filename << std::endl;
        std::cout << "Dimensions: " << image.width << "x" << image.height << std::endl;
        std::cout << "----------------------------------------------------------------------------------" << std::endl;

        // 1. Original Entropy
        std::vector<long long> histogramTotal(256, 0), histogramRed(256, 0), histogramGreen(256, 0),
            histogramBlue(256, 0);

        for (const auto& pixel : image.data) {
            histogramRed[pixel.r]++;
            histogramGreen[pixel.g]++;
            histogramBlue[pixel.b]++;
            histogramTotal[pixel.r]++;
            histogramTotal[pixel.g]++;
            histogramTotal[pixel.b]++;
        }

        Result originalResult;
        originalResult.methodName = "Original (No Prediction)";
        originalResult.entropyRed = calculateShannonEntropy(histogramRed, pixelCount);
        originalResult.entropyGreen = calculateShannonEntropy(histogramGreen, pixelCount);
        originalResult.entropyBlue = calculateShannonEntropy(histogramBlue, pixelCount);
        originalResult.entropyTotal = calculateShannonEntropy(histogramTotal, totalSamples);

        // 2. Calculate entropy for predictors
        std::vector<Result> results;

        for (int mode = 1; mode <= 8; ++mode) {
            std::vector<long long> predictorHistogramTotal(256, 0), predictorHistogramRed(256, 0),
                predictorHistogramGreen(256, 0), predictorHistogramBlue(256, 0);

            for (int y = 0; y < image.height; ++y) {
                for (int x = 0; x < image.width; ++x) {
                    const Pixel currentPixel = image.getPixel(x, y);
                    const Pixel westPixel = image.getPixel(x - 1, y);
                    const Pixel northPixel = image.getPixel(x, y - 1);
                    const Pixel northWestPixel = image.getPixel(x - 1, y - 1);

                    // Calculate prediction error modulo 256
                    auto calculateDifference = [&](int value, int prediction) -> uint8_t {
                        return static_cast<uint8_t>((value - prediction) & 0xFF);
                    };

                    const uint8_t differenceRed =
                        calculateDifference(currentPixel.r, predict(mode, westPixel.r, northPixel.r, northWestPixel.r));
                    const uint8_t differenceGreen =
                        calculateDifference(currentPixel.g, predict(mode, westPixel.g, northPixel.g, northWestPixel.g));
                    const uint8_t differenceBlue =
                        calculateDifference(currentPixel.b, predict(mode, westPixel.b, northPixel.b, northWestPixel.b));

                    predictorHistogramRed[differenceRed]++;
                    predictorHistogramGreen[differenceGreen]++;
                    predictorHistogramBlue[differenceBlue]++;
                    predictorHistogramTotal[differenceRed]++;
                    predictorHistogramTotal[differenceGreen]++;
                    predictorHistogramTotal[differenceBlue]++;
                }
            }

            Result predictorResult;
            predictorResult.methodName = getMethodName(mode);
            predictorResult.entropyRed = calculateShannonEntropy(predictorHistogramRed, pixelCount);
            predictorResult.entropyGreen = calculateShannonEntropy(predictorHistogramGreen, pixelCount);
            predictorResult.entropyBlue = calculateShannonEntropy(predictorHistogramBlue, pixelCount);
            predictorResult.entropyTotal = calculateShannonEntropy(predictorHistogramTotal, totalSamples);
            results.push_back(predictorResult);
        }

        // 3. Print table
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Entropy Results:" << std::endl;
        std::cout << std::left << std::setw(35) << "Method" << std::setw(12) << "TotalImage" << std::setw(12) << "Red"
                  << std::setw(12) << "Green" << std::setw(12) << "Blue" << std::endl;
        std::cout << std::string(85, '-') << std::endl;

        std::cout << std::left << std::setw(35) << originalResult.methodName << std::setw(12)
                  << originalResult.entropyTotal << std::setw(12) << originalResult.entropyRed << std::setw(12)
                  << originalResult.entropyGreen << std::setw(12) << originalResult.entropyBlue << std::endl;

        for (const auto& predictorResult : results) {
            std::cout << std::left << std::setw(35) << predictorResult.methodName << std::setw(12)
                      << predictorResult.entropyTotal << std::setw(12) << predictorResult.entropyRed << std::setw(12)
                      << predictorResult.entropyGreen << std::setw(12) << predictorResult.entropyBlue << std::endl;
        }
        std::cout << std::string(85, '-') << std::endl;

        // 4. Find optimal methods
        // Use pointer to member to generalize the search
        typedef double Result::*MemberPtr;

        auto findBest = [&](MemberPtr member) {
            double minimumValue = 1e9;
            std::string bestMethodName = "";
            for (const auto& predictorResult : results) {
                if ((predictorResult.*member) < minimumValue) {
                    minimumValue = (predictorResult.*member);
                    bestMethodName = predictorResult.methodName;
                }
            }
            return std::make_pair(bestMethodName, minimumValue);
        };

        const auto bestTotal = findBest(&Result::entropyTotal);
        const auto bestRed = findBest(&Result::entropyRed);
        const auto bestGreen = findBest(&Result::entropyGreen);
        const auto bestBlue = findBest(&Result::entropyBlue);

        std::cout << "SUMMARY - OPTIMAL METHODS (Min. Entropy):" << std::endl;
        std::cout << "Total Image:  " << bestTotal.first << " [" << bestTotal.second << "]" << std::endl;
        std::cout << "Red Channel:  " << bestRed.first << " [" << bestRed.second << "]" << std::endl;
        std::cout << "Green Channel:" << bestGreen.first << " [" << bestGreen.second << "]" << std::endl;
        std::cout << "Blue Channel: " << bestBlue.first << " [" << bestBlue.second << "]" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Program Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
