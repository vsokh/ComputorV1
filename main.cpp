#include "Domain/Polynomial.h"
#include "Domain/Solution.h"

#include "DomainServices/PolynomialParser.h"
#include "DomainServices/EquationSolverFactory.h"

#include "Presenters/PresenterFactory.h"

int main(int argc, char **argv)
{
    // TODO: Support higher term's degree
    // TODO: error handling:

    // 1. No equality sign
    // 2. A term which doesn't follow the form - a*X^p
    // 3. etc

    if (argc <= 1)
    {
        return 1;
    }

    const auto& polynomial = PolynomialParser::parse(argv[1]);
    const auto& polPresenter = PresenterFactory::createPresenter(polynomial);
    polPresenter->present();

    const auto& equationSolver = EquationSolverFactory::create(polynomial);
    const auto& solution = equationSolver->solve();
    const auto& solPresenter = PresenterFactory::createPresenter(solution);
    solPresenter->present();

    return 0;
}
