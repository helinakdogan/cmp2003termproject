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
    size_t index = hashFunction(filename);

    auto it = std::find_if(table[index].begin(), table[index].end(),
                           [&](const KeyValue &item) { return item.key == filename; });

    if (it != table[index].end()) {
        it->numOfItems += visits;
    } else {
        table[index].push_back({filename, visits});
    }
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

    std::partial_sort(allPages.begin(), allPages.begin() + 10, allPages.end(), compare);

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

        iss.ignore(256, '"');
        iss >> requestType;

        getline(iss >> std::ws, filename, '"');

        hashTable.insert(filename, 1);
    }
}
