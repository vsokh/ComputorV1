#include "EquationSolverFor0DegreePolynomial.h"

#include "../Domain/Solution.h"

EquationSolverFor0DegreePolynomial::EquationSolverFor0DegreePolynomial(Polynomial polynomial)
    : EquationSolver(std::move(polynomial))
{
}

Solution EquationSolverFor0DegreePolynomial::solve()
{
    return Solution{};
}
