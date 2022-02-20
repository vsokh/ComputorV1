#pragma once

#include "EquationSolver.h"

struct Solution;

class EquationSolverFor1DegreePolynomial : public EquationSolver
{
public:
    explicit EquationSolverFor1DegreePolynomial(Polynomial polynomial);
    Solution solve() override;
};
