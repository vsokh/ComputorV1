#include "EquationSolver.h"

EquationSolver::EquationSolver(Polynomial polynomial)
    : _polynomial(std::move(polynomial))
{
}

