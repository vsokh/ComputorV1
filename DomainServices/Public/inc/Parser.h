#pragma once

#include "Expression.h"
#include "Token.h"

class Parser
{
public:
    Expression parse(const std::string& expr);

private:
    Tokens toTokens(const std::string& expr);
    Terms toTerms(const Tokens& tokens);
};

