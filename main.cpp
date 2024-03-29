#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <algorithm>

// Showing full statistics in beautiful table xD
void printFullStats(const std::map<uint8_t, unsigned long> &byteFrequency, unsigned long totalBytes) {
    std::cout << "________________________________________________________________________" << std::endl;
    std::cout << "| Byte | Char | Frequency      | Count     |" << std::endl;
    std::cout << "|------|------|----------------|-----------|" << std::endl;
    for (const auto &[byte, count]: byteFrequency) {
        float frequency = static_cast<float>(count) / totalBytes;
        std::cout << "| " << std::setw(4) << std::hex << std::uppercase << static_cast<int>(byte)
                  << " | " << std::setw(4) << (isprint(byte) ? static_cast<char>(byte) : '.')
                  << " | " << std::setw(14) << std::fixed << std::setprecision(2) << frequency * 100 << "%"
                  << " | " << std::setw(9) << count << " |" << std::endl;
    }
    std::cout << "|______|______|________________|___________|" << std::endl << std::endl;
}

// work please!
void printHistogram(const std::map<uint8_t, unsigned long> &byteFrequency, unsigned long maxCount, float threshold) {
    std::cout << "[HISTOGRAM]" << std::endl;
    for (const auto &[byte, count]: byteFrequency) {
        float relativeFrequency = static_cast<float>(count) / maxCount;


        if (relativeFrequency > threshold) {
            std::cout << "\x1b[31m";
        }

        std::cout << std::hex << std::uppercase << static_cast<int>(byte) << ": ";
        int stars = static_cast<int>(relativeFrequency * 50); // 50 - max stars
        for (int i = 0; i < stars; ++i) {
            std::cout << "*";
        }

        std::cout << "\x1b[0m" << std::endl;
    }
}

void analyzeFile(const std::string &filename, float threshold) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error happened while opening file: " << filename << std::endl;
        return;
    }

    std::map<uint8_t, unsigned long> byteFrequency;
    unsigned long totalBytes = 0, maxCount = 0;


    uint8_t byte;
    while (file.read(reinterpret_cast<char *>(&byte), sizeof(byte))) {
        byteFrequency[byte]++;
        totalBytes++;
        maxCount = std::max(maxCount, byteFrequency[byte]);
    }

    printFullStats(byteFrequency, totalBytes);
    printHistogram(byteFrequency, maxCount, threshold);
}

int main(int argc, char *argv[]) {
    if (argc != 4 || std::string(argv[2]) != "-tr") {
        std::cerr << "Usage: " << argv[0] << " <filename> -tr <threshold>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    float threshold = std::stof(argv[3]);
    analyzeFile(filename, threshold);
    return 0;
}
