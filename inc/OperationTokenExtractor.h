#pragma once

#include <string>

class TokenExtractor;
struct Token;

class OperationTokenExtractor : public TokenExtractor
{
public:
    Token extract(typename std::string::iterator& it,
                  typename std::string::const_iterator end) override;
};