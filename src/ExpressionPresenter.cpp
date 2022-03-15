#include "ExpressionPresenter.hpp"
#include <iostream>

#include "Expression.hpp"

void ExpressionPresenter::present(const Expression& expression)
{
    std::cout << "Reduced form:";
    auto presentTerm = [](const Term& term, bool isFirst)
    {
        auto sign = term.coef < 0.0 ? -1 : 1;
        if (sign < 0)
        {
            std::cout << " - ";
        }
        else
        {
            std::cout << (isFirst ? " " : " + ");
        }
        std::cout << sign * term.coef << " * X^" << term.degree;
    };

    bool isFirst = true;
    for (const auto& term : expression.terms)
    {
        presentTerm(term, isFirst);
        isFirst = false;
    }

    std::cout << " = 0\n";
}
