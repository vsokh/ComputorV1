#pragma once

#include "EquationSolver.h"

struct Solution;

class EquationSolverFor0DegreePolynomial : public EquationSolver
{
public:
    explicit EquationSolverFor0DegreePolynomial(Polynomial polynomial);
    Solution solve() override;
};
