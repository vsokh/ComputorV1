#pragma once

#include "TokenExtractor.h"
#include <memory>

class TokenExtractorFactory
{
public:
    std::unique_ptr<TokenExtractor> create(char ch);
};
