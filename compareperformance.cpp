#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "HashTableH.h" // İlk hash tablosu implementasyonu (hashT)
#include <unordered_map> // İkinci hash tablosu implementasyonu (std::unordered_map)

// Fonksiyon prototipleri
void measurePerformanceHashT(const std::string& filename);
void measurePerformanceUnorderedMap(const std::string& filename);

int main() {
    // Dosyanın adı
    std::string filename = "access_log"; // Değiştirmeyi unutmayın

    // İlk hash tablosu performansını ölç
    measurePerformanceHashT(filename);

    // İkinci hash tablosu (std::unordered_map) performansını ölç
    measurePerformanceUnorderedMap(filename);

    return 0;
}

// hashT performansını ölçen fonksiyon
void measurePerformanceHashT(const std::string& filename) {
    // hashT nesnesi oluştur
    hashT myHashTable(100);

    // Zaman ölçümü başlat
    auto start = std::chrono::high_resolution_clock::now();

    // Log dosyasını işle
    std::ifstream logFile(filename);
    std::string line;
    while (std::getline(logFile, line)) {
        std::istringstream iss(line);
        std::string requestType, filename, httpVersion;

        iss >> requestType >> filename >> httpVersion;

        size_t pos = filename.find_last_of("/");
        if (pos != std::string::npos) {
            filename = filename.substr(pos + 1);
        }

        myHashTable.insert(1, filename); // You need to replace 1 with the actual key (maybe a hash of filename)
    }

    // Performansı yazdır
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Performance of hashT: " << duration.count() << " microseconds\n";
}

// std::unordered_map performansını ölçen fonksiyon
void measurePerformanceUnorderedMap(const std::string& filename) {
    // std::unordered_map nesnesi oluştur
    std::unordered_map<int, std::string> myUnorderedMap;

    // Zaman ölçümü başlat
    auto start = std::chrono::high_resolution_clock::now();

    // Log dosyasını işle
    std::ifstream logFile(filename);
    std::string line;
    while (std::getline(logFile, line)) {
        std::istringstream iss(line);
        std::string requestType, filename, httpVersion;

        iss >> requestType >> filename >> httpVersion;

        size_t pos = filename.find_last_of("/");
        if (pos != std::string::npos) {
            filename = filename.substr(pos + 1);
        }

        myUnorderedMap[1] = filename; // You need to replace 1 with the actual key (maybe a hash of filename)
    }

    // Performansı yazdır
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Performance of std::unordered_map: " << duration.count() << " microseconds\n";
}
