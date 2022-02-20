#include "CLIPolynomialPresenter.h"

#include <iostream>

CLIPolynomialPresenter::CLIPolynomialPresenter(Polynomial polynomial)
    : _polynomial(std::move(polynomial))
{
}

void CLIPolynomialPresenter::present() const
{
    presentPolynomialEquation();
    presentPolynomialDegree();
}

void CLIPolynomialPresenter::presentPolynomialEquation() const
{
    std::cout << "Reduced form:";
    auto presentMonomial = [](const Monomial& monomial, bool isFirst)
    {
        auto sign = monomial.coefficient < 0.0 ? -1 : 1;
        if (sign < 0)
        {
            std::cout << " - ";
        }
        else
        {
            std::cout << (isFirst ? " " : " + ");
        }
        std::cout << sign * monomial.coefficient << " * X^" << monomial.degree;
    };

    bool isFirst = true;
    for (const auto& monomial : _polynomial.getMonomials())
    {
        presentMonomial(monomial, isFirst);
        isFirst = false;
    }

    std::cout << " = 0\n";
}

void CLIPolynomialPresenter::presentPolynomialDegree() const
{
    std::cout << "Polynomial degree: " << _polynomial.getDegree() << "\n";
}
