#pragma once

#include <string>

struct Token;

class Lexer {
public:
    explicit Lexer(const std::string& str);
    Token getNextToken();

private:

    static std::string removeWhiteSpaces(std::string str);

private:
    std::string _str;

    typename std::string::iterator _it;
    typename std::string::const_iterator _begin;
    typename std::string::const_iterator _end;
};
