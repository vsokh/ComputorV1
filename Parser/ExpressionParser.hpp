#pragma once

#include "Expression.hpp"
#include <string>

class ExpressionParser {
public:
    static Expression parse(std::string exprStr);
};