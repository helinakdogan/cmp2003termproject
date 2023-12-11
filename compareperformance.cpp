// #include <iostream>
// #include <chrono>
// #include "HashTableH.h"

// int main() {
//     std::string filename = "access_log"; // Access log dosyanızın adını buraya ekleyin

//     // Measure performance with HashTable
//     HashTable myHashTable(100); // HashTable boyutunu ihtiyaca göre ayarlayın
//     auto startHashTable = std::chrono::high_resolution_clock::now();
//     processLogFileWithHashTable(filename, myHashTable);
//     myHashTable.printTopPages();
//     auto stopHashTable = std::chrono::high_resolution_clock::now();
//     auto durationHashTable = std::chrono::duration_cast<std::chrono::microseconds>(stopHashTable - startHashTable);
//     std::cout << "Total Elapsed Time (HashTable): " << durationHashTable.count() << " microseconds\n";

//     // Measure performance with std::unordered_map
//     std::unordered_map<std::string, int> unorderedMap;
//     auto startUnorderedMap = std::chrono::high_resolution_clock::now();
//     processLogFileWithUnorderedMap(filename, unorderedMap);
//     printTopPagesWithUnorderedMap(unorderedMap);
//     auto stopUnorderedMap = std::chrono::high_resolution_clock::now();
//     auto durationUnorderedMap = std::chrono::duration_cast<std::chrono::microseconds>(stopUnorderedMap - startUnorderedMap);
//     std::cout << "Total Elapsed Time (std::unordered_map): " << durationUnorderedMap.count() << " microseconds\n";

//     return 0;
// }
