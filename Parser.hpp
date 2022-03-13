#pragma once
#include <string>
#include "Expression.hpp"

using Tokens = std::vector<std::string>;

class Parser {
public:
    static Expression parse(std::string exprStr);

private:
    static void removeWhitespaces(std::string& str);
    static Tokens toTokens(std::string expr);
    static Terms toTerms(Tokens tokens);
    static Expression toExpression(std::string expr);
    static Expression combine(const Expression& lhs, const Expression& rhs);
};
