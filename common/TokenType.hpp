#ifndef TOKEN_TYPE_HPP_
#define TOKEN_TYPE_HPP_

#include <map>
#include <string>


class TokenType{
public: 
    enum Value{
        // Single character tokens
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // one or two chars
        BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

        // literals
        IDENTIFIER, STRING, NUMBER,

        // keywords
        AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

        TOKEN_EOF
    };

    inline static std::map<Value, std::string> lut {
        {Value::LEFT_PAREN, "left_paren"},
        {Value::RIGHT_PAREN, "right_paren"},
        {Value::LEFT_BRACE, "left_brace"},
        {Value::RIGHT_BRACE, "right_brace"},
        {Value::COMMA, "comma"},
        {Value::DOT, "dot"},
        {Value::MINUS, "minus"},
        {Value::PLUS, "plus"},
        {Value::SEMICOLON, "semicolon"},
        {Value::SLASH, "slash"},
        {Value::STAR, "star"},
        {Value::BANG, "bang"},
        {Value::BANG_EQUAL, "bang_equal"},
        {Value::EQUAL, "equal"},
        {Value::EQUAL_EQUAL, "equal_euqal"},
        {Value::GREATER, "greater"},
        {Value::GREATER_EQUAL, "greater_equal"},
        {Value::LESS, "less"},
        {Value::LESS_EQUAL, "less_equal"},
        {Value::AND, "and"},
        {Value::CLASS, "class"},
        {Value::ELSE, "else"},
        {Value::FALSE, "false"},
        {Value::FUN, "fun"},
        {Value::FOR, "for"},
        {Value::IF, "if"},
        {Value::NIL, "nil"},
        {Value::OR, "or"},
        {Value::PRINT, "print"},
        {Value::RETURN, "return"},
        {Value::SUPER, "super"},
        {Value::THIS, "this"},
        {Value::TRUE, "true"},
        {Value::VAR, "var"},
        {Value::WHILE, "while"},
        {Value::TOKEN_EOF, "eof"}
    };


};

#endif