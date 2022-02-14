#pragma once

#include "TokenExtractor.h"

class NumberTokenExtractor : public TokenExtractor
{
public:
    Token extract(typename std::string::iterator& it,
                  typename std::string::const_iterator end) override;
};
