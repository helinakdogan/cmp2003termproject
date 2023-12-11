#include <iostream>
#include <fstream>
#include <sstream>
#include "hashtable.h"

int main() {
    // Create an instance of your hash table
    hashT myHashTable;

    // Open the log file
    std::ifstream logFile("access_log");

    if (!logFile.is_open()) {
        std::cerr << "Error: Unable to open the log file." << std::endl;
        return 1;
    }

    // Read each line from the log file and process it
    std::string line;
    while (std::getline(logFile, line)) {
        // Assuming each line in the log file has the format: "GET filename HTTP/1.0"
        std::istringstream iss(line);
        std::string requestType, filename, httpVersion;

        iss >> requestType >> filename >> httpVersion;

        // Extract filename from the request
        size_t pos = filename.find_last_of("/");
        if (pos != std::string::npos) {
            filename = filename.substr(pos + 1);
        }

        // Insert the filename into the hash table using filename as the key
        myHashTable.insert(std::hash<std::string>{}(filename), filename);
    }

    // Print the top pages
    myHashTable.printTopPages();

    return 0;
}
