/* ADSA Assignment 3 - Hash table with linear probing */
/* Sam Kirk, 1851921                                  */


#include <iostream>
#include <vector>
#include <string>

// Parses the input into tokens i.e. Aapple, Dpear 
std::vector<std::string> getInput(){

    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> words;
    int index = 0;

    for (int i = 0 ; i < input.size() ; i++){
        if (input.at(i) == ' '){
            std::string new_word = input.substr(index, i-index);
            words.push_back(new_word);
            index = i+1;
        }
    }
    // last word 
    if (index < input.size()) {
        words.push_back(input.substr(index));
    }

    return words;
}

// Hash function which uses the last charcter of a key 
int hash(std::string key){
    char last_char = key.back();
    return last_char - 'a'; // a maps to 0, z maps to 26 
}

// Searches the contents of a hash table for a key 
// Returns -1 if not the key is not found or the index in the hash table with the key if the key is found 
int search(std::string key, std::vector<std::string>& hash_table, std::vector<std::string>& status_table ){

    int index = hash(key);
    std::string word = key.substr(1,key.size()-1);

    if (status_table.at(index) == "occupied"){

        if (hash_table.at(index) == word){
            return index; // the word is in the hash table 
        }
        // need to keep searching 
        while (status_table.at(index) == "occupied" || status_table.at(index) == "tombstone"){
            if (status_table.at(index) == "tombstone"){ // dont check the hash table of a tombstone status
                // increase index 
                index = (index + 1) % 26;
                continue;
            }
            else if (hash_table.at(index) == word){
                return index; // the word is in the hash table 
            }
            // increase index 
            index = (index + 1) % 26;
        }
        return -1; // word is definetley not in hash table. 
    }

    else if (status_table.at(index) == "never used"){
        return -1; // word is definetley not in hash table. 
    }

    else if (status_table.at(index) == "tombstone"){
        // need to keep searching 
        index = (index + 1) % 26;
         while (status_table.at(index) == "occupied" || status_table.at(index) == "tombstone"){
            if (status_table.at(index) == "tombstone"){ // dont check the hash table of a tombstone status
                // increase index 
                index = (index + 1) % 26;
                continue;
            }
            else if (hash_table.at(index) == word){
                return index; // the word is in the hash table 
            }
            // increase index 
            index = (index + 1) % 26;
        }
        return -1; // word is definetley not in hash table. 
    }
    std::cout << "Error in searching" << std::endl;
    return -1;
}

// similar to search method , but we want to return the index of where the word we want to insert should go 
int available_index(std::string key, std::vector<std::string>& hash_table, std::vector<std::string>& status_table ){
    int index = hash(key);

    while (status_table.at(index) == "occupied"){
        index = (index + 1) % 26;
    }

    return index;
}

// Main method 
int main(void){
    // get the keys from the input 
    std::vector<std::string> keys = getInput();

    // initialise empty hash table and status table
    std::vector<std::string> hash_table(26, "null");
    std::vector<std::string> status_table(26, "never used");

    // go through each key 
    std::string key;
    for (int i = 0 ; i < keys.size() ; i++){
        key = keys.at(i);
        int index = search(key, hash_table, status_table);

        if (key.at(0) == 'A'){ // insert case 
            if (index == -1){ // key is not in the table so we need to add
                // TODO: CHANGE INDEX BECAUSE ITS -1 
                int new_index = available_index(key, hash_table, status_table);
                hash_table.at(new_index) = key.substr(1,key.size()-1);
                status_table.at(new_index) = "occupied";
                continue;
            }
            else { // key is already in the table so do nothing                  
                continue;
            }
        }

        else if (key.at(0) == 'D'){ // delete case 
            if (index == -1){ // key is not in the map so we do nothing 
                continue;
            }
            else {
                status_table.at(index) = "tombstone";
                continue;
            }
        }

        else { // invalid input 
            std::cout << "Invalid Input. Each word should start with A or D" << std::endl;
            return -1;
        }
    }

    // Print everything in the table. 
    for (int i = 0 ; i < hash_table.size() ; i++){
        if (hash_table.at(i) != "null" && status_table.at(i) != "tombstone"){
            std::cout << hash_table.at(i) << " ";
        }
    
    }
    std::cout << std::endl;


    return 0;
}