#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#include "../common/Token.hpp"
#include "../common/TokenType.hpp"
#include "../frontend/scanner.hpp"


class Lox{
public:
    bool hadError = false;

    // Constructor
    Lox() = default;

    void run(std::string source){
        Scanner scanner(source);
        std::vector<Token> tokens = scanner.scan_tokens();

        for(auto token : scanner.tokens){
            std::cout << token << std::endl;
        }
    }


    void runFile(std::string path){
        if(std::ifstream ifs {path}){
            // read file to str
            std::string file_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            run(file_str);
        } else {
            throw std::runtime_error("Failed to open file");
        }

        if(hadError){
            throw std::runtime_error("Error in parsed file!");
        }
    }

    void runPrompt(){
        std::string line;

        for(;;){
            std::cout << "> ";
            std::getline(std::cin, line);
            if(!std::cin){
                break;
            }
            run(line);
            hadError = false;
        }
    }

    void report(int line, std::string where, std::string message){
        std::cout << "[line " << line <<  "] Error" << where << ": " << message;
        hadError = true;
    }

    void error(int line, std::string message){
        report(line, "", message);
    }
};



int main(int argc, char** argv){

    if (argc > 2){
        std::cout << "Usage: cpplox [script]" << std::endl;
        return -1;
    } else if (argc == 2) {
        Lox lox_runner;
        lox_runner.runFile(argv[0]);
    } else {
        Lox lox_runner;
        lox_runner.runPrompt();
    }

    return 0;
}