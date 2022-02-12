#pragma once
#include <vector>

struct Term
{
    double coef;
    int deg;
};

struct Expression
{
    Term x0{0, 0}, x1{0, 1}, x2{0, 2};
};

using Terms = std::vector<Term>;
