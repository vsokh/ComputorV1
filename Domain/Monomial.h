#pragma once

#include <unordered_map>

using Degree = int;
using Coefficient = double;

struct Monomial
{
    Monomial& operator+(const Monomial& rhs);
    Monomial& operator+=(const Monomial& rhs);

    Coefficient coefficient{};
    Degree degree{};
};

using Monomials = std::unordered_map<Degree, Monomial>;
