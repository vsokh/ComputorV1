#include "CLIPolynomialPresenter.h"

#include <iostream>

CLIPolynomialPresenter::CLIPolynomialPresenter(Polynomial polynomial)
    : _polynomial(std::move(polynomial))
{
}

void CLIPolynomialPresenter::present() const
{
    std::cout << __FUNCTION__ << std::endl;
    auto x0 = _polynomial.getMonomial(0);
    auto x1 = _polynomial.getMonomial(1);
    auto x2 = _polynomial.getMonomial(2);

    std::cout << "Reduced form: ";
    if (x0.coefficient < 0.0)      std::cout << "- " << (-1*x0.coefficient) << " * X^0";
    else if (x0.coefficient > 0.0) std::cout << x0.coefficient << " * X^0";

    if (x1.coefficient < 0.0)      std::cout << " - " << (-1*x1.coefficient) << " * X^1";
    else if (x1.coefficient > 0.0) std::cout << " + " << x1.coefficient << " * X^1";

    if (x2.coefficient < 0.0)      std::cout << " - " << (-1*x2.coefficient) << " * X^2";
    else if (x2.coefficient > 0.0) std::cout << " + " << x2.coefficient << " * X^2";
    std::cout << " = 0" << std::endl;
}
