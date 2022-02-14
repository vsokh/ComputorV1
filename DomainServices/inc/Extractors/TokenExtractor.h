#pragma once

#include "Token.h"
#include <string>

class TokenExtractor
{
public:
    virtual Token extract(typename std::string::iterator& it,
                          typename std::string::const_iterator end) = 0;
    virtual ~TokenExtractor() = default;
};
