#pragma once

#include <vector>

using Degree = int;
using Coefficient = double;

struct Monomial
{
    Monomial& operator+(const Monomial& rhs);
    Monomial& operator+=(const Monomial& rhs);

    Coefficient coefficient{};
    Degree degree{};
};

using Monomials = std::vector<Monomial>;
