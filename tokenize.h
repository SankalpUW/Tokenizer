#include <iostream>
#include <forward_list>
#include <string>
#include <vector>
#include <fstream>

class Tokenize{
    private:
        class Entry{
            public:
                std::string word;
                int token;
        };

        std::vector<Entry> tokenToWordArray;
        std::forward_list<Entry>* wordToTokenTable; 
        unsigned int tableSize;


        unsigned int hash(const std::string& str);  //this is the provided hash function

public:
    Tokenize();  //constuctor
    ~Tokenize(); // destructor

    // member functions
    void create(int size);
    bool insert(const std::string& word);
    void load(const std::string& filename);
    int tok(const std::string& word);
    std::string ret(int token);
    std::vector<int> tok_all(const std::string& input);
    std::vector<std::string> ret_all(const std::vector<int>& tokens);
    void print(int k);
};