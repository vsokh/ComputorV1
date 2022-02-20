#include "EquationSolverFor1DegreePolynomial.h"

#include "../Domain/Solution.h"

EquationSolverFor1DegreePolynomial::EquationSolverFor1DegreePolynomial(Polynomial polynomial)
        : EquationSolver(std::move(polynomial))
{
}

Solution EquationSolverFor1DegreePolynomial::solve()
{
    const auto& x0 = _polynomial.getMonomial(0);
    const auto& x1 = _polynomial.getMonomial(1);

    Solution solution;
    solution.root1 = -1*x0.coefficient / x1.coefficient;
    solution.hasRoots = true;
    solution.hasInfRoots = x1.coefficient == 0.0;
    return solution;
}
