// hashtable.cpp

#include "hashtable.h"
#include <iostream>
#include <algorithm>
#include <vector>

hashT::hashT() : numOfItems(0), tableSize(101) {
    hashTable = new KeyValue*[tableSize]();

    for (size_t i = 0; i < tableSize; ++i) {
        hashTable[i] = nullptr;
    }
}

int hashT::hash(const int& key) const {
    return key % tableSize;
}

bool hashT::search(int key, const std::string& value) const {
    int index = hash(key);
    KeyValue* temp = hashTable[index];

    while (temp != nullptr) {
        if (temp->value == value) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

void hashT::insert(int key, const std::string& value) {
    if (numOfItems / tableSize > 0.8) {
        rehashing();
    }

    int index = hash(key);

    if (search(key, value)) {
        std::cout << "Eklenmez\n";
        return;
    }

    KeyValue* newPair = new KeyValue(key, value);
    newPair->next = hashTable[index];
    hashTable[index] = newPair;
    numOfItems++;
}

void hashT::rehashing() {
    size_t oldTableSize = tableSize;
    KeyValue** temp = hashTable;

    tableSize = oldTableSize * 2;
    hashTable = new KeyValue*[tableSize]();

    for (size_t i = 0; i < tableSize; ++i) {
        hashTable[i] = nullptr;
    }

    for (size_t i = 0; i < oldTableSize; ++i) {
        KeyValue* currBucketHead = temp[i];
        while (currBucketHead != nullptr) {
            insert(currBucketHead->key, currBucketHead->value);
            KeyValue* next = currBucketHead->next;
            delete currBucketHead;
            currBucketHead = next;
        }
    }

    delete[] temp;
}

void hashT::printTopPages() const {
    std::vector<KeyValue> allPages;

    for (size_t i = 0; i < tableSize; ++i) {
        KeyValue* current = hashTable[i];
        while (current != nullptr) {
            allPages.push_back(*current);
            current = current->next;
        }
    }

    std::sort(allPages.begin(), allPages.end(),
              [](const KeyValue& a, const KeyValue& b) {
                  return a.numOfItems > b.numOfItems;
              });

    std::cout << "Top 10 Visited Pages:\n";
    for (size_t i = 0; i < std::min(allPages.size(), size_t(10)); ++i) {
        std::cout << "Filename: " << allPages[i].value << ", Visits: " << allPages[i].numOfItems << '\n';
    }
}

hashT::~hashT() {
    for (size_t i = 0; i < tableSize; ++i) {
        KeyValue* current = hashTable[i];
        while (current != nullptr) {
            KeyValue* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] hashTable;
}
