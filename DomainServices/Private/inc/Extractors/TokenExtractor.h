#pragma once

#include "Token.h"

#include <string>
#include <memory>

class TokenExtractor
{
public:
    virtual Token extract(typename std::string::iterator& it,
                          typename std::string::const_iterator end) = 0;
    virtual ~TokenExtractor() = default;
};

std::unique_ptr<TokenExtractor> createTokenExtractor(char ch);
