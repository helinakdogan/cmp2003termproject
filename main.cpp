#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTableH.h"

int main() {
    hashT hashTable(100); // You can adjust the size as needed
    unorderedMapT unorderedMap;

    std::ifstream file("access_log.txt");

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string requestType, filename;

        // Parse the log entry to extract the filename
        for (int i = 0; i < 5; ++i) {
            iss >> requestType;
        }
        iss >> filename;

        // Assuming filename is in the format "GET filename HTTP/1.0"
        if (filename.size() >= 4 && filename.substr(0, 4) == "GET") {
            filename = filename.substr(4);
            // Remove leading '/' if present
            filename = (filename[0] == '/') ? filename.substr(1) : filename;

            // Assuming filename is terminated by a space
            size_t pos = filename.find(' ');
            if (pos != std::string::npos) {
                filename = filename.substr(0, pos);
            }

            hashTable.insert(1, filename);
            unorderedMap.insert(1, filename);
        }
    }

    file.close();

    hashTable.printTopPages();
    unorderedMap.printTopPages();

    return 0;
}