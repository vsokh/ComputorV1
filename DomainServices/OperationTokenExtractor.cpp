#include "OperationTokenExtractor.h"

#include "../Domain/Token.h"

#include <unordered_map>
#include <exception>

Token OperationTokenExtractor::extract(
        typename std::string::iterator& it,
        typename std::string::const_iterator end)
{
    if (it == end)
    {
        throw std::logic_error("Wrong operation term");
    }

    static const std::unordered_map<char, Token>
        charToTokenMap = {
            {'+', {TokenKind::Add, std::nullopt}},
            {'-', {TokenKind::Sub, std::nullopt}},
            {'*', {TokenKind::Mul, std::nullopt}},
            {'=', {TokenKind::Equality, std::nullopt}},
    };
    return charToTokenMap.find(*it++)->second;
}
