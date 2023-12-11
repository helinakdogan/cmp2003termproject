#include "HashTableH.h"
#include <algorithm>
#include <fstream>
#include <sstream>

// HashTable class implementation
HashTable::HashTable(int size) : tableSize(size), table(size) {}

HashTable::~HashTable() {
    // Destructor implementation
}

void HashTable::insert(const std::string &filename, int visits) {
    int index = hashFunction(filename);
    table[index].push_back({filename, visits});
}

void HashTable::printTopPages() const {
    std::vector<KeyValue> allPages;

    for (const auto &list : table) {
        for (const auto &item : list) {
            allPages.push_back(item);
        }
    }

    auto compare = [](const KeyValue &a, const KeyValue &b) {
        return a.numOfItems > b.numOfItems;
    };

    std::sort(allPages.begin(), allPages.end(), compare);

    std::cout << "Top 10 Pages using HashTable:\n";
    for (size_t i = 0; i < std::min(allPages.size(), static_cast<size_t>(10)); ++i) {
        std::cout << "Filename: " << allPages[i].key << ", Visits: " << allPages[i].numOfItems << '\n';
    }
}

size_t HashTable::hashFunction(const std::string &str) const {
    return std::hash<std::string>{}(str) % tableSize;
}

void processLogFileWithHashTable(const std::string &filename, HashTable &hashTable) {
    std::ifstream logFile(filename);
    std::string line;
    while (std::getline(logFile, line)) {
        std::istringstream iss(line);
        std::string requestType, filename, httpVersion;
        iss >> requestType >> filename >> httpVersion;
        hashTable.insert(filename, 1); // Assuming each line represents one visit
    }
}
