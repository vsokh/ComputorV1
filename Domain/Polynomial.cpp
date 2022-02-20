#include "Polynomial.h"

void Polynomial::adjustDegree(const Monomial& monomial)
{
    _degree = _degree < monomial.degree ? monomial.degree : _degree;
}

void Polynomial::addMonomial(Monomial monomial)
{
    if (auto monomialIt = _monomials.find(monomial.degree);
             monomialIt != _monomials.end())
    {
        _monomials[monomial.degree] += monomial;
    }
    else
    {
        _monomials[monomial.degree] = monomial;
    }

    adjustDegree(monomial);
}

Monomial Polynomial::getMonomial(Degree degree) const
{
    return _monomials.at(degree);
}

Degree Polynomial::getDegree() const
{
    return _degree;
}
