#include "Parser.hpp"
#include "Solver.hpp"

#include "ExpressionPresenter.hpp"
#include "SolutionPresenter.hpp"

#include <iostream>

int main()
{
    // TODO: Solver tests.
    // TODO: Manage dependencies; refactor.

    std::string exprStr = "1 * X^2 + 0 * X^1 + 0 * X^0 = 1 * X^2";
//    std::string exprStr = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0";
//    std::string exprStr = "5 * X^0 + 4 * X^1 = 4 * X^0";
//    std::string exprStr = "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0";
    try {
        auto expression = Parser::parse(exprStr);
        ExpressionPresenter::present(expression);

        auto solution = Solver::solve(std::move(expression));
        SolutionPresenter::present(std::move(solution));

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
