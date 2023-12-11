#include "HashTableH.h"

// hashT sınıfının üye fonksiyonlarını tanımla
hashT::hashT(int size) : tableSize(size), table(size) {}

hashT::~hashT() {}

void hashT::insert(int num, const std::string &str) {
    int index = hashFunction(str) % tableSize;
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
    // Basit bir örnek hash fonksiyonu; gerçek bir uygulama için daha karmaşık bir şey kullanmalısınız
    size_t hash = 0;
    for (char ch : str) {
        hash = hash * 31 + ch;
    }
    return hash;
}

// unorderedMapT sınıfının üye fonksiyonlarını tanımla
void unorderedMapT::insert(int num, const std::string &str) {
    data[str] += num;
}

void unorderedMapT::printTopPages() const {
    std::vector<KeyValue> allPages;

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
