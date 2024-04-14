#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "../common/Token.hpp"
#include "../common/TokenType.hpp"

class Scanner{
public:
    std::string source;
    std::vector<Token> tokens;

    Scanner(std::string source) : source(source)
    { };

    std::vector<Token> scan_tokens(){
        while(!is_at_end()){
            start = current;
            scan_token();
        }

        auto tmp = Token( TokenType::Value::TOKEN_EOF, "", 0, line);

        tokens.emplace_back(tmp);
        return tokens;
    };

private:
    int start = 0;
    int current = 0;
    int line = 1;

    inline static std::map<std::string, TokenType::Value> keywords {
        {"and", TokenType::Value::AND},
        {"class", TokenType::Value::CLASS},
        {"else", TokenType::Value::ELSE},
        {"false", TokenType::Value::FALSE},
        {"for", TokenType::Value::FOR},
        {"fun", TokenType::Value::FUN},
        {"if", TokenType::Value::IF},
        {"nil", TokenType::Value::NIL},
        {"or", TokenType::Value::OR},
        {"print", TokenType::Value::PRINT},
        {"return", TokenType::Value::RETURN},
        {"super", TokenType::Value::SUPER},
        {"this", TokenType::Value::THIS},
        {"true", TokenType::Value::TRUE},
        {"var", TokenType::Value::VAR},
        {"while", TokenType::Value::WHILE},
    };

    bool is_at_end(){
        return current >= source.length();
    }

    void scan_token(){
        char c = advance();
        switch (c) {
            case '(': add_token(TokenType::Value::LEFT_PAREN); break;
            case ')': add_token(TokenType::Value::RIGHT_PAREN); break;
            case '{': add_token(TokenType::Value::LEFT_BRACE); break;
            case '}': add_token(TokenType::Value::RIGHT_BRACE); break;
            case ',': add_token(TokenType::Value::COMMA); break;
            case '.': add_token(TokenType::Value::DOT); break;
            case '-': add_token(TokenType::Value::MINUS); break;
            case '+': add_token(TokenType::Value::PLUS); break;
            case ';': add_token(TokenType::Value::SEMICOLON); break;
            case '*': add_token(TokenType::Value::STAR); break;
            case '!':
                add_token(match('=') ? TokenType::Value::BANG_EQUAL : TokenType::Value::BANG); break;
                break;
            case '=':
                add_token(match('=') ? TokenType::Value::EQUAL_EQUAL : TokenType::Value::EQUAL); break;
                break;
            case '<':
                add_token(match('=') ? TokenType::Value::LESS_EQUAL : TokenType::Value::LESS); break;
                break;
            case '>':
                add_token(match('=') ? TokenType::Value::GREATER_EQUAL : TokenType::Value::GREATER); break;
                break;
            case '/':
            {
                if(match('/')){
                    //comment runs until end of the line
                    while(peek() != '\n' && !is_at_end()){
                        advance();
                    }
                } else {
                    add_token(TokenType::Value::SLASH);
                }
                break;
            }
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
            {
                line++;
                break;
            }
            case '"':
                string(); break;

            default:
            {
                if(is_digit(c)){
                    number();
                } else if (is_alpha(c)) {
                    identifier();
                } else {
                  throw std::runtime_error("Error scanning"); //TODO
                }
            }
        }
    }

    char advance(){
        return source.at(current++);
    }

    void add_token(TokenType::Value type){
        add_token(type, nullptr);
    }

    void add_token(TokenType::Value type, void* literal){
        std::string text = source.substr(start, current-start);
        auto tmp = Token(type, text, literal, line);

        tokens.emplace_back(tmp);
    }

    bool match(char expected){
        if(is_at_end()){
            return false;
        }
        if (source.at(current) != expected) {
            return false;
        }

        current++;
        return true;
    }

    char peek(){
        if (is_at_end()) {
            return '\0';
        }
        return source.at(current);
    }

    char peek_next(){
        if(current + 1 >= source.length()){
            return '\0';
        }
        return source.at(current + 1);
    }


    void string(){
        while(peek() != '"' && !is_at_end()){
            if(peek() == '\n') {
                line++;
            }
            advance();
        }

        if (is_at_end()) {
            throw std::runtime_error("Unterminated string");
        }

        advance(); //the closing "

        std::string text = source.substr(start+1, current-start-2); // trim "" from string
        add_token(TokenType::STRING, nullptr); //(void*) text
        
    }

    bool is_digit(char c){
        return c >= '0' && c <= '9';
    }

    bool is_alpha(char c){
        return (c >=  'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                (c == '_');
    }

    bool is_alphanumeric(char c){
        return is_alpha(c) || is_digit(c);
    }

    void number(){
        while(is_digit(peek())){
            advance();
        }

        if (peek() == '.' && is_digit(peek_next())) {
            advance();
            while(is_digit(peek())){
                advance();
            }
        }

        add_token(TokenType::NUMBER,  nullptr);//std::stof(source.substr(start, current))
    }

    void identifier(){
        while (is_alpha(peek())) {
            advance();
        }
        
        std::string text = source.substr(start, current-start);
        TokenType::Value type = TokenType::Value::IDENTIFIER; 
        
        // Check if this is a keyword
        auto search = keywords.find(text);
        if (search != keywords.end()) {
            type = search->second;
        }

        add_token(type);
    }
};

#endif