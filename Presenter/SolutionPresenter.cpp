#include "SolutionPresenter.hpp"
#include <iostream>

void SolutionPresenter::present(const Solution& solution)
{
    if (solution.isInfRoots) {
        std::cout << "The solution set covers all real numbers:\n";
        std::cout << "-Inf\n";
        std::cout << "Inf\n";
        return ;
    }

    const auto rootsNum = solution.roots.size();
    if (rootsNum == 0) {
        std::cout << "There are no solutions.\n";
        return;
    }

    if (rootsNum == 2) {
        std::cout << "Discriminant is strictly positive, the two solutions are:\n";
    } else {
        std::cout << "The solution is:\n";
    }

    for (auto root : solution.roots) {
        std::cout << root << "\n";
    }
}

