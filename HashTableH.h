#ifndef HASHTABLEH_H
#define HASHTABLEH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

struct KeyValue {
    std::string key;
    int numOfItems;
};

class hashT {
public:
    hashT(int size);
    ~hashT();
    void insert(int num, const std::string &str);
    void printTopPages() const;

private:
    int tableSize;
    std::vector<std::vector<KeyValue>> table;
    size_t hashFunction(const std::string &str) const;
};

class unorderedMapT {
public:
    void insert(int num, const std::string &str);
    void printTopPages() const;

private:
    std::unordered_map<std::string, int> data;
};

// Implement the member functions of hashT class
hashT::hashT(int size) : tableSize(size), table(size) {}

hashT::~hashT() {
    // Destructor implementation
}

void hashT::insert(int num, const std::string &str) {
    int index = hashFunction(str);
    table[index].push_back({str, num});
}

void hashT::printTopPages() const {
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

    std::cout << "Top 10 Pages using Hashtable:\n";
    for (size_t i = 0; i < std::min(allPages.size(), static_cast<size_t>(10)); ++i) {
        std::cout << "Filename: " << allPages[i].key << ", Visits: " << allPages[i].numOfItems << '\n';
    }
}

size_t hashT::hashFunction(const std::string &str) const {
    return std::hash<std::string>{}(str) % tableSize;
}

// Implement the member functions of unorderedMapT class
void unorderedMapT::insert(int num, const std::string &str) {
    data[str] += num;
}

void unorderedMapT::printTopPages() const {
    std::vector<KeyValue> allPages;

    #include <algorithm>

        for (const auto &item : data) {
            allPages.push_back({item.first, item.second});
        }

        auto compare = [](const KeyValue &a, const KeyValue &b) {
            return a.numOfItems > b.numOfItems;
        };

        std::sort(allPages.begin(), allPages.end(), compare);

        std::cout << "Top 10 Pages using Unordered Map:\n";
        for (size_t i = 0; i < std::min(allPages.size(), static_cast<size_t>(10)); ++i) {
            std::cout << "Filename: " << allPages[i].key << ", Visits: " << allPages[i].numOfItems << '\n';
        }
}

#endif
