#pragma once

#include "Monomial.h"

class Polynomial
{
public:
    void addMonomial(Monomial monomial);
    [[nodiscard]] Monomial getMonomial(Degree degree) const;
    [[nodiscard]] Degree getDegree() const;

private:
    void adjustDegree(const Monomial& monomial);

private:
    Monomials _monomials;
    Degree _degree;
};
