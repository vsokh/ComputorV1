#include "Domain/Polynomial.h"
#include "Domain/Solution.h"

#include "DomainServices/PolynomialParser.h"
#include "DomainServices/EquationSolverFactory.h"

#include "Presenters/PresenterFactory.h"

#include <iostream>

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        return 1;
    }
    try
    {
        const auto &polynomial = PolynomialParser::parse(argv[1]);
        const auto &polPresenter = PresenterFactory::createPresenter(polynomial);
        polPresenter->present();

        const auto &equationSolver = EquationSolverFactory::create(polynomial);
        const auto &solution = equationSolver->solve();
        const auto &solPresenter = PresenterFactory::createPresenter(solution);
        solPresenter->present();
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
