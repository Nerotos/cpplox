#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include "TokenType.hpp"
#include <ostream>
#include <string>

using str=std::string;

class Token{
public:
    TokenType::Value type;
    str lexeme;
    void* literal;
    int line;

    Token(TokenType::Value type_, str lexeme_, void* literal_, int line_) :
        type(type_),
        lexeme(lexeme_),
        literal(literal_),
        line(line_)
    {};

    str to_string(){
        str val = TokenType::lut[type] + " " + lexeme + " "; // +literal
        return val;
    }

    friend std::ostream & operator<<(std::ostream& os, const Token token){
        return os << TokenType::lut[token.type] << " " << token.lexeme << " ";
    }


};

#endif