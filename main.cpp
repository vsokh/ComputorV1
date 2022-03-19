#include "Parser.hpp"
#include "Solver.hpp"

#include "ExpressionPresenter.hpp"
#include "SolutionPresenter.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc <= 1) {
        std::cout << "Usage: computor <expression>\n";
        return 1;
    }
    try {
        auto expression = FormulaParser{argv[1]}.parse();
        ExpressionPresenter::present(expression);

        auto solution = Solver::solve(std::move(expression));
        SolutionPresenter::present(std::move(solution));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
