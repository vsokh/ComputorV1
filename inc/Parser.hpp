#pragma once

#include <string>
#include "Expression.hpp"

class ExpressionParser {
public:
    explicit ExpressionParser(std::string exprStr);
    Expression parse();

private:
    std::string _exprStr;
};

class ExpressionCombiner
{
public:
    ExpressionCombiner(const Expression& lhs, const Expression& rhs);
    Expression combine();

private:
    const Expression& _lhs;
    const Expression& _rhs;
};

class ExpressionSplitter {
public:
    explicit ExpressionSplitter(std::string exprStr);
    std::tuple<Expression, Expression> split();

private:
    std::string _exprStr;
};
