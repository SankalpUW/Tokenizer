#include "tokenize.h"
#include <sstream>

Tokenize::Tokenize(){
    tableSize = 0;
    wordToTokenTable = nullptr;
}

Tokenize::~Tokenize(){
    delete[] wordToTokenTable;
}

unsigned int Tokenize::hash(const std::string& str){  //provided hash function
    unsigned int ans = 0;
    for (auto it= str.begin(); it != str.end(); it++){
        ans = ans * 29 + *it;
    }
    return ans%tableSize;
}

void Tokenize::create(int size){  //creates the hash table with size of size.
    
    if (wordToTokenTable != nullptr){  //deletes pre-existing word to token hash table for new one
        delete[] wordToTokenTable;
    }
    wordToTokenTable= new std::forward_list<Entry>[size]; // create the new hash table
    tableSize = size;

    std::cout<< "success" << std::endl;
}

bool Tokenize::insert(const std::string& word){
    bool isAlphabetic = true;   
    for (char c : word){   // checking if the word is entirely alphabetic
        if (!std::isalpha(c)){
            isAlphabetic = false;
            break;
        }
    }

    if(!isAlphabetic){
        return false;
    }

    unsigned int hashValue= hash(word);
    for(const auto& entry : wordToTokenTable[hashValue]) {
        if (entry.word == word){   // checking if the word to insert already exists.
            return false;
        }
    }

    Entry newEntry;
    newEntry.word = word;
    newEntry.token = tokenToWordArray.size() + 1; // since were using 1based indexing
    tokenToWordArray.push_back(newEntry);  // each word is sequentially pushed back into the array
    wordToTokenTable[hashValue].push_front(newEntry);

    return true;
    }

void Tokenize::load(const std::string& filename){
    std::fstream file;
    std::string word,t,q;
    file.open(filename.c_str());
    int count_words = 0; // to check whether any word was inserted successfully from the text file.

    if (file.is_open()){
        while(file >> word){  // go over all the words in the textfile
            // insert(word);
            if(insert(word)){
                count_words++;
            }
        }
        // inserted_word = true;
        file.close();
    } 
    if(count_words>0){
        std::cout<<"success"<<std::endl;
    }

    if(count_words==0){
        std::cout<<"failure"<<std::endl;
    }
}

int Tokenize::tok(const std::string& word){
    unsigned int hashValue = hash(word);
    for (const auto& entry : wordToTokenTable[hashValue]) {
        if (entry.word == word){
            return entry.token;  // returns the numeric token associated with word
        }
    }
    return -1;
}

std::string Tokenize::ret(int token){
    if ((token >= 1) && (token<= static_cast<int>(tokenToWordArray.size()))){ // check if the token is greater than 1 and is lesser than the size of the table
        return tokenToWordArray[token - 1].word;
    }
    else{
        return "N/A";
    }
}

std::vector<int> Tokenize::tok_all(const std::string& input){
    std::vector<int> tokens;
    std::string word;
    std::istringstream iss(input);
    while (iss >> word){
        int token= tok(word); // tokenizes the word 
        if (token!= -1){
            tokens.push_back(token); 
        }
        else{
            tokens.push_back(-1); // non-existing word
        }
    }
    return tokens;
}

std::vector<std::string> Tokenize::ret_all(const std::vector<int>& tokens){
    std::vector<std::string> words;
    for (int token : tokens){
        if((token >= 1) && (token <= static_cast<int>(tokenToWordArray.size()))){ // check if the token passed is greater than 0 and less than the size of table
            words.push_back(tokenToWordArray[token - 1].word);
        }
        else {
            words.push_back("N/A");
        }
    }
    return words;
}

void Tokenize::print(int k){
    bool newline = false; // boolean for checking whether we have an empty chain
    if (k < 0 || static_cast<unsigned int>(k) >= tableSize){  // checking if index k is valid
        return;
    }

    for (const auto& entry : wordToTokenTable[k]) {
        std::cout << entry.word << " ";
        newline = true;
    }
    if(newline){
        std::cout<<std::endl;
    }
}

