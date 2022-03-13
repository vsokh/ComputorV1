#include <exception>
#include <iostream>

#include "Parser.hpp"

int main()
{
    // TODO: Parser tests
    // TODO: Expression presenter
    // TODO: Solver
    // TODO: Solver tests
    // TODO: Solution presenter

    std::string exprStr = "-2.0*X^4 - 1.0*X^3 + 1*X0.0 - 1*X^0 = 1*X^0";
    std::cout << "expr: " << exprStr << std::endl;
    try {
        auto expr = Parser::parse(exprStr);
        for (auto term : expr.terms) {
            std::cout << term.coef << ", " << term.degree << std::endl;
        }

        auto highestDegreeTerm = std::max_element(expr.terms.begin(), expr.terms.end(),
                                                  [](const Term& a, const Term& b)
                                                  { return a.degree < b.degree; });
        if (highestDegreeTerm->degree > 2) {
            std::cout << "Higher than 2, can't solve, blah-blah-blah..." << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}