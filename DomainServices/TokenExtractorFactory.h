#pragma once

#include "TokenExtractor.h"

#include <memory>

class TokenExtractorFactory
{
public:
    static std::unique_ptr<TokenExtractor> create(char ch);
};
