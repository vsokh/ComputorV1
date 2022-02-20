#include "CLISolutionPresenter.h"

#include <iostream>

CLISolutionPresenter::CLISolutionPresenter(Solution solution)
        : _solution(std::move(solution))
{
}

void CLISolutionPresenter::present() const
{
    if (_solution.discriminant > 0.0)
    {
        std::cout << "Discriminant is strictly positive, the two solutions are: " << std::endl;
    }

    std::cout << _solution.root1 << std::endl;
    std::cout << _solution.root2 << std::endl;
}