#include "Parser.h"
#include "Solver.h"

#include "ExpressionPresenter.h"
#include "CLIExpressionPresenter.h"

#include <memory>
#include <iostream>

// TODO: add factory
std::unique_ptr<ExpressionPresenter> createExpressionPresenter()
{
    return std::make_unique<CLIExpressionPresenter>();
}

int main(int argc, char **argv)
{
    // TODO: error handling:
    // 1. No equality sign
    // 2. A term which doesn't follow the form - a*X^p
    // 3. etc
    // TODO: Support higher term's degree

    if (argc <= 1)
    {
        return 1;
    }

    const auto& expression = Parser{}.parse(argv[1]);
    const auto& exprPresenter = createExpressionPresenter();
    exprPresenter->present(expression);

    const auto& solution = Solver{}.solve(expression);
    (void)solution;
    return 0;
}
