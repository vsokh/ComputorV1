#include <exception>

#include "TokenExtractor.h"
#include "UnknownTokenExtractor.h"

Token UnknownTokenExtractor::extract(
        typename std::string::iterator& it,
        typename std::string::const_iterator end)
{
    static const std::string str = "X^";
    auto strIt = str.begin();
    while (it != end && strIt != str.end() && *it == *strIt)
    {
        ++it;
        ++strIt;
    }
    if (it == end || strIt != str.end())
    {
        throw std::logic_error("Wrong unknown term");
    }
    if (*it < '0' || '2' < *it ||
       ((it + 1) != end &&
        *(it + 1) >= '0' &&
        *(it + 1) <= '9'))
    {
        throw std::logic_error("Wrong unknown term");
    }
    return {TokenKind::Unknown, std::stod(std::string{*it++})};
}
