#pragma once
#include "Term.hpp"

struct Expression
{
    double x0{0.0}, x1{0.0}, x2{0.0};
    int discriminant;

    void update(const Term& term)
    {
        if (term.exp == 0)
            x0 += term.coef;
        else if (term.exp == 1)
            x1 += term.coef;
        else
            x2 += term.coef;
    }
};
