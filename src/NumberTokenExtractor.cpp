#include "TokenExtractor.h"
#include "NumberTokenExtractor.h"

Token NumberTokenExtractor::extract(
        typename std::string::iterator& it,
        typename std::string::const_iterator end)
{
    auto beg = it;
    while (it != end && '0' <= *it && *it <= '9')
    {
        ++it;
    }
    if (it == end || *it != '.')
    {
        return {TokenKind::Num, std::stod(std::string{beg, it})};
    }
    ++it;
    while (it != end && '0' <= *it && *it <= '9')
    {
        ++it;
    }
    return {TokenKind::Num, std::stod(std::string{beg, it})};
}
