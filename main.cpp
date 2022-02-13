#include "DomainServices/Public/inc/Parser.h"
#include "DomainServices/Public/inc/Solver.h"

#include "Presenters/ExpressionPresenter.h"
#include "Presenters/CLIExpressionPresenter.h"

#include <memory>

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

    (void)argv;
    if (argc <= 1)
    {
        return 1;
    }

    const auto& expr = std::string{"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"};
    const auto& expression = Parser{}.parse(expr);

    const auto& exprPresenter = createExpressionPresenter();
    exprPresenter->present(expression);

    const auto& solution = Solver{}.solve(expression);
    (void)solution;
    return 0;
}
