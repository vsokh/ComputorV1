#include "CLISolutionPresenter.h"

#include <iostream>

CLISolutionPresenter::CLISolutionPresenter(Solution solution)
        : _solution(std::move(solution))
{
}

void CLISolutionPresenter::present() const
{
    std::cout << __FUNCTION__ << std::endl;
}