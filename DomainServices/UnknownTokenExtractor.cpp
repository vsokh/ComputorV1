#include "TokenExtractor.h"

#include "UnknownTokenExtractor.h"

#include "../Domain/Token.h"

#include <exception>

Token UnknownTokenExtractor::extract(
        typename std::string::iterator& it,
        typename std::string::const_iterator end) {
    static const std::string str = "X^";
    auto strIt = str.begin();
    while (it != end && strIt != str.end() && *it == *strIt)
    {
        ++it;
        ++strIt;
    }
    if (it == end || strIt != str.end()) {
        throw std::logic_error("Wrong unknown term");
    }
    auto isNum = [](auto& it) {
        return '0' <= *it && *it <= '9';
    };
    auto numberBegin = it;
    while (it != end && isNum(it))
    {
        ++it;
    }
    auto numberStr = std::string{numberBegin, it};
    return {TokenKind::Unknown, std::stod(numberStr)};
}
