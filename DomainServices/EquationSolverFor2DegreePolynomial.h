#pragma once

#include "EquationSolver.h"

struct Solution;

class EquationSolverFor2DegreePolynomial : public EquationSolver
{
public:
    explicit EquationSolverFor2DegreePolynomial(Polynomial polynomial);
    Solution solve() override;
};
