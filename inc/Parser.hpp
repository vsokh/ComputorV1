#pragma once

#include <string>
#include "Expression.hpp"

using Tokens = std::vector<std::string>;
using OperationPredicate = std::function<bool(char ch)>;

class Parser {
public:
    static Expression parse(std::string exprStr);

private:
    // string utils
    static void removeWhitespaces(std::string& str);

    static Expression toExpression(std::string expr);

    // isn't a parser
    static Expression combine(const Expression& lhs, const Expression& rhs);

private:
    std::string _expression;
};
