#include "Monomial.h"

Monomial& Monomial::operator+(const Monomial& rhs)
{
    if (this == &rhs || degree != rhs.degree)
    {
        return *this;
    }
    else
    {
        coefficient += rhs.coefficient;
    }
    return *this;
}

Monomial& Monomial::operator+=(const Monomial& rhs)
{
    return *this + rhs;
}

