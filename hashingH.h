//
//  hashingH.h
//  hashT
//
//  Created by Selin Güler on 10.12.2023.
//

#ifndef hashingH_h
#define hashingH_h

using namespace std;

class KeyValue
{
public:
    int key;
    string value;
    KeyValue* next;
    KeyValue(int key, string value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
    ~KeyValue()
    {
        KeyValue *head = this;
                while (head != NULL)
                {
                    KeyValue *currKeyValue = head;
                    head = head->next;
                    delete currKeyValue;
                }
    }
};

class hashT{
public:
    void insert(int key, std::string value);
    void rehashing();
    bool search(int key, string value);
    int hash(const int& key) const;
    hashT();
    //~hashT();
private:
 
    int numOfItems, tableSize;
    KeyValue** hashTable; //hashTable is an array of pointers.
    //Each element in the array (*) is a pointer to the head of a linked list.
    //Each linked list node (*) holds a key-value pair (K, V).

};


#endif /* hashingH_h */
