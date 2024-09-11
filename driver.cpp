#include <iostream>
#include <string>
#include <sstream>
#include "tokenize.h"

int main(){
    Tokenize tokenizer;
    std::string command;

    while (std::cin >> command){
        if (command == "create"){
            int size;
            std::cin >> size;
            tokenizer.create(size);
        } else if(command == "insert"){
            std::string word;
            std::cin >> word;
            if(tokenizer.insert(word)){
                std::cout<<"success"<<std::endl;
            } else{
                std::cout<<"failure"<<std::endl;
            }

        }else if (command == "load"){
            std::string filename;
            std::cin >> filename;
            tokenizer.load(filename);


        } else if (command == "tok"){
            std::string word;
            std::cin >> word;
            int token = tokenizer.tok(word);
            std::cout << token << std::endl;
        } else if (command == "ret"){
            int token;
            std::cin >> token;
            std::string word = tokenizer.ret(token);
            std::cout << word << std::endl;
        } else if (command == "tok_all"){
            std::string input;
            std::getline(std::cin >> std::ws, input); // Read entire line including spaces
            std::vector<int> tokens = tokenizer.tok_all(input);
            for (int token : tokens) {
                std::cout << token << " ";
            }
            std::cout << std::endl;
        } else if (command == "ret_all") {
            std::string input;
            std::getline(std::cin >> std::ws, input); // Read entire line including spaces
            std::istringstream iss(input);
            std::vector<int> tokens;
            int token;
            while (iss >> token) {
                if (token == -1) {
                    break;
                }
                tokens.push_back(token);
            }
            std::vector<std::string> words = tokenizer.ret_all(tokens);
            for (const std::string& word : words){
                std::cout << word << " ";
            }
            std::cout << std::endl;
            
        } else if (command == "print") {
            int k;
            std::cin >> k;
            tokenizer.print(k);
        } else if (command == "exit"){
            break;
        }
    }

    return 0;
}