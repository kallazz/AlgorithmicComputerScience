#include "compression.hpp"
#include "codes.hpp"
#include "lzw.hpp"
#include "entropy.hpp"
#include "fileUtils.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

uint8_t getCodeTypeId(const std::string& codeType) {
    if (codeType == "omega") return 1;
    if (codeType == "gamma") return 2;
    if (codeType == "delta") return 3;
    if (codeType == "fib") return 4;
    return 0;
}

std::string getCodeTypeName(uint8_t codeTypeId) {
    switch (codeTypeId) {
        case 1:
            return "omega";
        case 2:
            return "gamma";
        case 3:
            return "delta";
        case 4:
            return "fib";
        default:
            return "";
    }
}

std::string encodeValue(uint64_t value, const std::string& codeType) {
    if (codeType == "omega") return eliasOmegaEncode(value);
    if (codeType == "gamma") return eliasGammaEncode(value);
    if (codeType == "delta") return eliasDeltaEncode(value);
    if (codeType == "fib") return fibonacciEncode(value);

    throw std::runtime_error("Unknown code type: " + codeType);
}

uint64_t decodeValue(const std::string& bitString, size_t& position, const std::string& codeType) {
    if (codeType == "omega") return eliasOmegaDecode(bitString, position);
    if (codeType == "gamma") return eliasGammaDecode(bitString, position);
    if (codeType == "delta") return eliasDeltaDecode(bitString, position);
    if (codeType == "fib") return fibonacciDecode(bitString, position);

    throw std::runtime_error("Unknown code type: " + codeType);
}

void encodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& codeType) {
    // Read input file
    std::vector<unsigned char> inputData = readBinaryFile(inputFile);

    if (inputData.empty()) {
        std::cerr << "Warning: empty input file\n";
    }

    // Perform LZW compression
    auto lzwCodes = lzwEncode(inputData);

    // Encode LZW codes using universal code
    std::string encodedBits;
    for (uint64_t code : lzwCodes) {
        uint64_t adjustedValue = code + 1;  // Adjust for 1-based indexing
        encodedBits += encodeValue(adjustedValue, codeType);
    }

    // Calculate statistics
    double inputEntropy = calculateInputEntropy(inputData);
    double codeEntropy = calculateCodeEntropy(encodedBits);

    // Convert bits to bytes
    uint8_t paddingBits;
    std::string outputBytes = bitStringToBytes(encodedBits, paddingBits);

    // Write output file with metadata
    std::ofstream output(outputFile, std::ios::binary);
    if (!output) {
        throw std::runtime_error("Cannot open output file: " + outputFile);
    }

    uint8_t codeTypeId = getCodeTypeId(codeType);
    output.put(codeTypeId);
    output.put(paddingBits);
    output.write(outputBytes.data(), outputBytes.size());

    // Print statistics
    std::cout << "Original bytes: " << inputData.size() << '\n';
    std::cout << "Output bytes: " << (2 + outputBytes.size()) << '\n';
    std::cout << "Compression ratio: " << (8.0 * inputData.size()) / encodedBits.size() << '\n';
    std::cout << "Input entropy (bits/byte): " << inputEntropy << '\n';
    std::cout << "Code entropy (bits/bit): " << codeEntropy << '\n';
}

void decodeFile(const std::string& inputFile, const std::string& outputFile, const std::string& codeType) {
    // Read input file
    std::ifstream input(inputFile, std::ios::binary);
    if (!input) {
        throw std::runtime_error("Cannot open input file: " + inputFile);
    }

    // Read metadata
    uint8_t codeTypeId, paddingBits;
    input.read((char*)&codeTypeId, 1);
    input.read((char*)&paddingBits, 1);

    std::string detectedCodeType = getCodeTypeName(codeTypeId);
    if (detectedCodeType.empty()) {
        throw std::runtime_error("Unknown code type in file");
    }

    // Validate code type matches
    if (codeType != detectedCodeType) {
        std::cerr << "Error: File was encoded with '" << detectedCodeType << "' but you specified '" << codeType
                  << "'\n";
        std::cerr << "Cannot decode with mismatched codes.\n";
        throw std::runtime_error("Code type mismatch");
    }

    // Read compressed data
    std::vector<unsigned char> compressedBytes((std::istreambuf_iterator<char>(input)),
                                               std::istreambuf_iterator<char>());

    // Convert bytes to bit string
    std::string bitString = bytesToBitString(compressedBytes, paddingBits);

    // Decode universal codes
    std::vector<uint64_t> lzwCodes;
    size_t position = 0;

    while (position < bitString.size()) {
        uint64_t decodedValue = decodeValue(bitString, position, codeType);

        if (decodedValue > 0) {
            lzwCodes.push_back(decodedValue - 1);  // Adjust back from 1-based indexing
        }
    }

    // Perform LZW decompression
    auto decodedData = lzwDecode(lzwCodes);

    // Write output file
    writeBinaryFile(outputFile, decodedData);

    std::cout << "Decoded " << decodedData.size() << " bytes\n";
}
