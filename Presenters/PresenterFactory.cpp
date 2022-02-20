#include "PresenterFactory.h"

#include "CLIPolynomialPresenter.h"
#include "CLISolutionPresenter.h"

std::unique_ptr<Presenter> PresenterFactory::createPresenter(const Solution& solution)
{
    return std::make_unique<CLISolutionPresenter>(solution);
}

std::unique_ptr<Presenter> PresenterFactory::createPresenter(const Polynomial& polynomial)
{
    return std::make_unique<CLIPolynomialPresenter>(polynomial);
}
