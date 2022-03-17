#include "Solver.hpp"

#include <cmath>
#include <iostream>

std::optional<Term> Solver::findTermByDegree(const Expression& expr, double degree)
{
    if (auto termIt = std::find_if(expr.begin(), expr.end(),
                                   [&degree](const Term& term)
                                   {
                                       return term.degree == degree;
                                   });
            termIt != expr.end())
    {
        return *termIt;
    }
    return std::nullopt;
}

Solution Solver::solveForSecondDegree(const Expression& expr)
{
    Solution solution{};

    constexpr static double SecondDegree = 2;
    constexpr static double FirstDegree = 1;
    constexpr static double ZeroDegree = 0;

    auto x2 = findTermByDegree(expr, SecondDegree);

    auto x1 = findTermByDegree(expr, FirstDegree);
    if (!x1) {
        x1 = Term{};
    }

    auto x0 = findTermByDegree(expr, ZeroDegree);
    if (!x0) {
        x0 = Term{};
    }

    const auto& a = x2->coef;
    const auto& b = x1->coef;
    const auto& c = x0->coef;
    const auto& D = b*b - 4*a*c;

    if (D == 0.0) {
        solution.roots.emplace_back(0.0);
    } else if (D > 0.0) {
        const auto root1 = (-b - std::sqrt(D))/(2*a);
        const auto root2 = (-b + std::sqrt(D))/(2*a);
        solution.roots.push_back(root1);
        solution.roots.push_back(root2);
    } else {
        solution.isNoRoots = true;
    }
    return solution;
}

Solution Solver::solveForFirstDegree(const Expression& expr)
{
    Solution solution{};
    constexpr static double FirstDegree = 1;
    constexpr static double ZeroDegree = 0;
    auto x1 = findTermByDegree(expr, FirstDegree);
    auto x0 = findTermByDegree(expr, ZeroDegree);
    if (!x0) {
        solution.roots.emplace_back(0.0);
    } else {
        const auto& b = x1->coef;
        const auto& c = x0->coef;
        solution.roots.emplace_back(-c/b);
    }
    return solution;
}

Solution Solver::solveForZeroDegree(const Expression& expr)
{
    Solution solution;
    constexpr static double ZeroDegree = 0;
    auto x0 = findTermByDegree(expr, ZeroDegree);
    if (!x0) {
        solution.isInfRoots = true;
    } else {
        solution.roots.emplace_back(0.0);
    }
    return solution;
}

Solution Solver::solve(Expression expr)
{
    constexpr static double SecondDegree = 2;
    constexpr static double FirstDegree = 1;

    expr.erase(std::remove_if(expr.begin(), expr.end(),
                              [](const Term& term){ return term.coef == 0.0; }), expr.end());

    auto termIt = std::max_element(expr.begin(), expr.end(),
                                   [](const Term& a, const Term& b){ return a.degree < b.degree; });

    auto degree = termIt->degree;
    std::cout << "Polynomial degree: " << degree << std::endl;
    if (degree > SecondDegree) {
        throw std::logic_error{"The polynomial degree is strictly greater than 2, I can't solve."};
    }
    if (degree == SecondDegree) {
        return solveForSecondDegree(std::move(expr));
    }
    if (degree == FirstDegree) {
        return solveForFirstDegree(std::move(expr));
    }
    return solveForZeroDegree(std::move(expr));
}
