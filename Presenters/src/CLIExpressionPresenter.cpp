#include "CLIExpressionPresenter.h"
#include "Expression.h"
#include <iostream>

void CLIExpressionPresenter::present(const Expression& expression) const
{
    auto x0 = expression.x0;
    auto x1 = expression.x1;
    auto x2 = expression.x2;

    std::cout << "Reduced form: ";
    if (x0.coef < 0.0)      std::cout << "- " << (-1*x0.coef) << " * X^0";
    else if (x0.coef > 0.0) std::cout << x0.coef << " * X^0";

    if (x1.coef < 0.0)      std::cout << " - " << (-1*x1.coef) << " * X^1";
    else if (x1.coef > 0.0) std::cout << " + " << x1.coef << " * X^1";

    if (x2.coef < 0.0)      std::cout << " - " << (-1*x2.coef) << " * X^2";
    else if (x2.coef > 0.0) std::cout << " + " << x2.coef << " * X^2";
    std::cout << " = 0" << std::endl;
}
