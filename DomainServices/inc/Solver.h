#pragma once

#include "Solution.h"
#include <array>

struct Expression;
struct Term;

constexpr size_t UnknownsNum = 3;
using Unknowns = std::array<Term, UnknownsNum>;

class Solver
{
public:
    Solution solve(const Expression& expression);

private:
    int getDegree(const Expression& expression) const;

    Unknowns getUnknowns(const Expression& expression) const;
};
