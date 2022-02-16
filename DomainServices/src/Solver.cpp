#include "Solver.h"
#include "Solution.h"
#include "Expression.h"

#include <cmath>

int Solver::getDegree(const Expression& expression) const
{
    int degree = 0;
    degree = expression.x1.coefficient != 0.0 ? expression.x1.degree : degree;
    degree = expression.x2.coefficient != 0.0 ? expression.x2.degree : degree;
    return degree;
}

Unknowns Solver::getUnknowns(const Expression& expression) const
{
    return Unknowns{expression.x0, expression.x1, expression.x2};
}

Solution Solver::solve(const Expression& expression)
{
    const auto& degree = getDegree(expression);
    const auto& [x0, x1, x2] = getUnknowns(expression);

    auto result = Solution{};
    switch (degree)
    {
        case 0: {
            return result;
        }
        case 1: {
            result.root1 = -1*x0.coefficient / x1.coefficient;
        }
        case 2: {
            const auto& a = x2.coefficient;
            const auto& b = x1.coefficient;
            const auto& c = x0.coefficient;

            const double Discriminant = b*b - 4*a*c;

            result.root1 = (-1*b - std::sqrt(Discriminant))/(2*a);
            result.root2 = (-1*b + std::sqrt(Discriminant))/(2*a);
            result.Discriminant = Discriminant;
        }
    }
    return result;
}
