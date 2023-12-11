// hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

class KeyValue {
public:
    int key;
    std::string value;
    int numOfItems; // Added to keep track of the number of visits
    KeyValue* next;

    KeyValue(int k, const std::string& v) : key(k), value(v), numOfItems(1), next(nullptr) {}
    ~KeyValue() {
        KeyValue* head = this;
        while (head != nullptr) {
            KeyValue* currKeyValue = head;
            head = head->next;
            delete currKeyValue;
        }
    }
};

class hashT {
public:
    void insert(int key, const std::string& value);
    void rehashing();
    bool search(int key, const std::string& value) const;
    int hash(const int& key) const;
    void printTopPages() const;
    hashT();
    ~hashT();

private:
    int numOfItems, tableSize;
    KeyValue** hashTable;
};

#endif /* HASHTABLE_H */
