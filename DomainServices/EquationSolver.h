#pragma once

#include "../Domain/Polynomial.h"

struct Solution;

class EquationSolver
{
public:
    explicit EquationSolver(Polynomial polynomial);

    virtual ~EquationSolver() = default;
    virtual Solution solve() = 0;

protected:
    Polynomial _polynomial;
};
