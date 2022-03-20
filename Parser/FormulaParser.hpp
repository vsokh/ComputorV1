#pragma once

#include "Expression.hpp"

#include <string>

class FormulaToStandardFormPolynomialParser {
public:
    static Expression parse(std::string formulaStr);
};
