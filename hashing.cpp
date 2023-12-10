//
//  hashing.cpp
//  hashT
//
//  Created by Selin Güler on 10.12.2023.
//

#include <iostream>
#include <string>
#include "hashingH.h"

hashT::hashT()
{
    this->numOfItems = 0;
    this->tableSize = 101;
    this->hashTable = new KeyValue* [this->tableSize];
}

int hashT::hash(const int& key) const
{
    return key % tableSize;
}


bool hashT::search(int key, string value)
{
    bool found = false;
    
    int index = hash(key);
    
    KeyValue* temp = hashTable[index];
    
    while (!found) {
        if (temp->value == value) {
            found = true;
        }
        temp = temp->next;
    }
    delete temp;
    return found;
}

void hashT::insert(int key, std::string value)
{
    if (numOfItems/tableSize > 0.8) {
        rehashing();
    }
    
    int index = hash(key);
    
    if (search(key, value)) {
        cout<<"eklenmez";
    }
    
    else if (this->hashTable[key] == NULL) // when there is no linked list at bucket
    {
        KeyValue *newPair = new KeyValue(key, value);
        hashTable[index] = newPair;
        numOfItems++;
    }
    else // adding at the head of current linked list
    {
        KeyValue *newPair = new KeyValue(key, value);
        newPair->next = this->hashTable[index];
        this->hashTable[index] = newPair;
        numOfItems++;
    }
}


void hashT::rehashing()
{
    int oldTableSize = tableSize;
    KeyValue **temp = this->hashTable;
    
    this->tableSize = oldTableSize*2;
    this->hashTable = new KeyValue *[this->tableSize]; // points to new array of doubled size
    
    for (int i = 0; i < this->tableSize; i++)
    {
        hashTable[i] = NULL;
    }
    for (int i = 0; i < oldTableSize; i++) // copying all the previous values in new array
    {
        KeyValue *currBucketHead = temp[i];
        while (currBucketHead != NULL) // copying whole linked list
        {
            this->insert(currBucketHead->key, currBucketHead->value); // insert function have now updated hash function as capacity is doubled
            currBucketHead = currBucketHead->next;
        }
    }
    delete[] temp; // deleting old array from heap memory
    return;
    
}






/*


template <typename TKey, typename TValue, size_t TableSize>
class HashTable {
private:
    struct Node {
        TKey key;
        TValue value;
        Node* next;
        Node(const TKey& k, const TValue& v) : key(k), value(v), next(nullptr) {}
    };

    Node* table[TableSize];

    size_t Hash(const TKey& key) const {
        // Replace this with your own hash function
        std::hash<TKey> hashFunction;
        return hashFunction(key) % TableSize;
    }

public:
    HashTable() {
        // Initialize the table
        for (size_t i = 0; i < TableSize; ++i) {
            table[i] = nullptr;
        }
    }

    TValue& operator[](const TKey& key) {
        size_t index = Hash(key);

        // Check if the key already exists in the list at the index
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        // Key not found, create a new node and insert at the beginning of the list
        Node* newNode = new Node(key, TValue());
        newNode->next = table[index];
        table[index] = newNode;

        return newNode->value;
    }

    ~HashTable() {
        // Clean up memory
        for (size_t i = 0; i < TableSize; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

int main() {
    HashTable<std::string, int, 4> myHashTable;

    // Example usage
    myHashTable["key1"] = 42;
    myHashTable["key2"] = 73;

    // Access elements
    std::cout << "Value at key1: " << myHashTable["key1"] << std::endl;
    std::cout << "Value at key2: " << myHashTable["key2"] << std::endl;

    return 0;
}
*/
