//
//  main.cpp
//  text
//
//  Created by Selin Coskun on 8.12.2023.
//

#include <iostream>
#include <fstream>
using namespace std;


class HashTable {
private:
    struct Node {
            std::string key;
            int value;
            Node* next;
        };
    
public:
    void insert(string key, int value){
        cout<<key<<' '<<value<<endl;
        
    }
};



int main() {
    HashTable hashTable;
    ifstream infile;
    string line;
    infile.open("access_log");
    
    
    
    
    
    for(int i=0; i<100;i++){
        
        getline(infile,line);
        const int maxWords = 20; // Maximum number of words in the array
            std::string words[maxWords]; // Array to store the words
            int wordCount = 0;

            size_t pos = 0;
            while ((pos = line.find(' ')) != std::string::npos) {
                words[wordCount++] = line.substr(0, pos);
                line.erase(0, pos + 1);
            }
            
            // Store the last word (or the only word if there are no spaces left)
            words[wordCount++] = line;
        string filename=words[6];
        int statusCode=stoi(words[8]);
        int reply;
        if(words[9]=="-"){
           reply=0;}
        else{
            reply=stoi(words[9]);};
        if(statusCode==200){
            hashTable.insert(filename,reply);
        }

            // Display the elements in the array
            
        //cout<<filename<<' '<<statusCode<<' '<<reply<<endl;
        
       
        
    }
    return 0;
}





