#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "HashTableH.h"
#include "HashTable.cpp"

void processLogFileWithUnorderedMap(const std::string &filename, std::unordered_map<std::string, int> &unorderedMap) {
    std::ifstream logFile(filename);
    std::string line;
    while (std::getline(logFile, line)) {
        std::istringstream iss(line);
        std::string requestType, filename, httpVersion;

        // Log girişlerinin gereksiz kısımlarını atlayın
        iss.ignore(256, '"');
        iss >> requestType; // İstek tipini atla

        // Geri kalan kısmı birleştirerek dosya adını elde et
        getline(iss >> std::ws, filename, '"');

        unorderedMap[filename] += 1;
    }
}


void printTopPagesWithUnorderedMap(const std::unordered_map<std::string, int> &unorderedMap) {
    std::vector<KeyValue> allPages;

    for (const auto &item : unorderedMap) {
        allPages.push_back({item.first, item.second});
    }

    auto compare = [](const KeyValue &a, const KeyValue &b) {
        return a.numOfItems > b.numOfItems;
    };

    std::sort(allPages.begin(), allPages.end(), compare);

    std::cout << "Top 10 Pages using std::unordered_map:\n";
    for (size_t i = 0; i < std::min(allPages.size(), static_cast<size_t>(10)); ++i) {
        std::cout << "Filename: " << allPages[i].key << ", Visits: " << allPages[i].numOfItems << '\n';
    }
}

int main() {
    std::string filename = "access_log.txt"; // Access log dosyanızın adını buraya ekleyin

    // Task 1: Using Custom HashTable
    HashTable myHashTable(100); // HashTable size, adjust as needed

    auto startHashTable = std::chrono::high_resolution_clock::now();
    processLogFileWithHashTable(filename, myHashTable);
    myHashTable.printTopPages();
    auto stopHashTable = std::chrono::high_resolution_clock::now();
    auto durationHashTable = std::chrono::duration_cast<std::chrono::microseconds>(stopHashTable - startHashTable);

    std::cout << "Total Elapsed Time (HashTable): " << durationHashTable.count() << " microseconds\n";

    // Task 2: Using std::unordered_map
    std::unordered_map<std::string, int> unorderedMap;
    
    auto startUnorderedMap = std::chrono::high_resolution_clock::now();
    processLogFileWithUnorderedMap(filename, unorderedMap);
    printTopPagesWithUnorderedMap(unorderedMap);
    auto stopUnorderedMap = std::chrono::high_resolution_clock::now();
    auto durationUnorderedMap = std::chrono::duration_cast<std::chrono::microseconds>(stopUnorderedMap - startUnorderedMap);

    std::cout << "Total Elapsed Time (std::unordered_map): " << durationUnorderedMap.count() << " microseconds\n";

    return 0;
}
