#pragma once

#include "Expression.hpp"
#include "Solution.hpp"
#include <optional>

class Solver {
public:
    static Solution solve(Expression expr);

private:
    static Solution solveForSecondDegree(const Expression& expr);
    static Solution solveForFirstDegree(const Expression& expr);
    static Solution solveForZeroDegree(const Expression& expr);
    static std::optional<Term> findTermByDegree(const Expression& expr, double degree);
};

