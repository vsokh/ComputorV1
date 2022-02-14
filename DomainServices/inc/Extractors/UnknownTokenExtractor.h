#pragma once

#include "TokenExtractor.h"

class UnknownTokenExtractor : public TokenExtractor
{
public:
    Token extract(typename std::string::iterator& it,
                  typename std::string::const_iterator end) override;
};
