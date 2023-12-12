#ifndef HASHTABLEH_H
#define HASHTABLEH_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

struct KeyValue
{
    std::string key;
    int numOfItems;
};

class HashTable
{
public:
    HashTable(int size);
    ~HashTable();
    void insert(const std::string &filename, int visits);
    void printTopPages() const;

private:
    int tableSize;
    std::vector<std::vector<KeyValue>> table;
    size_t hashFunction(const std::string &str) const;
};

void processLogFileWithHashTable(const std::string &filename, HashTable &hashTable);

#endif
