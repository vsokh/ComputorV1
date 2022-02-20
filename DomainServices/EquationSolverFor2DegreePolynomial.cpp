#include "EquationSolverFor2DegreePolynomial.h"

#include "../Domain/Solution.h"

#include <array>

EquationSolverFor2DegreePolynomial::EquationSolverFor2DegreePolynomial(Polynomial polynomial)
        : EquationSolver(std::move(polynomial))
{
}

Solution EquationSolverFor2DegreePolynomial::solve()
{
    const auto& x0 = _polynomial.getMonomial(0);
    const auto& x1 = _polynomial.getMonomial(1);
    const auto& x2 = _polynomial.getMonomial(2);

    const auto& a = x2->coefficient;
    const auto& b = x1 ? x1->coefficient : 0;
    const auto& c = x0 ? x0->coefficient : 0;

    const auto discriminant = b*b - 4*a*c;

    if (discriminant < 0)
    {
        return Solution{};
    }

    Solution solution;
    solution.root1 = (-1*b - std::sqrt(discriminant))/(2*a);
    solution.root2 = (-1*b + std::sqrt(discriminant))/(2*a);
    solution.hasRoots = true;
    solution.hasInfRoots = a == 0.0 && b == 0.0;
    return solution;
}
