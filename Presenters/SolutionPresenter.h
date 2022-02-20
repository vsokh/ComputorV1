#pragma once

struct Solution;

class SolutionPresenter
{
public:
    virtual void present(const Solution& solution) = 0;
    virtual ~SolutionPresenter() = default;
};