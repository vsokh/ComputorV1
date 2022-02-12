#include "Solver.h"
#include "Solution.h"
#include "Expression.h"

Solution Solver::solve(const Expression& expression)
{
    const auto& x0 = expression.x0;
    const auto& x1 = expression.x1;
    const auto& x2 = expression.x2;

    auto degree = 0;
    degree = x1.coef != 0.0 ? x1.deg : degree;
    degree = x2.coef != 0.0 ? x2.deg : degree;
    /* std::cout << "Polynomial degree: " << degree << std::endl; */
    /* std::cout << "The solution is:\n"; */

    Solution result;
    if (degree == 0)
    {
        return result;
    }

    if (degree == 1)
    {
        result.root1 = -1*x0.coef / x1.coef;
    }
    else if (degree == 2)
    {
        const auto a = x2.coef;
        const auto b = x1.coef;
        const auto c = x0.coef;

        const double D = b*b - 4*a*c;

        result.root1 = (-1*b - std::sqrt(D))/(2*a);
        result.root2 = (-1*b + std::sqrt(D))/(2*a);
        result.Discriminant = D;
    }
    return result;
}
