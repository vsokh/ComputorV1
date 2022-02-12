#pragma once

#include "Solution.h"
struct Expression;

class Solver
{
public:
    Solution solve(const Expression& expression);
};
