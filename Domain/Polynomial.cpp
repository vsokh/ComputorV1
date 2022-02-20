#include "Polynomial.h"

void Polynomial::addMonomial(Monomial monomial)
{
    if (monomial.coefficient == 0.0)
    {
        return;
    }

    if (auto monomialOpt = getMonomial(monomial.degree))
    {
        auto& tmpMonomial = _monomials[monomial.degree];
        tmpMonomial += monomial;
        if (tmpMonomial.coefficient == 0.0)
        {
            _monomials.erase(monomial.degree);
        }
    }
    else
    {
        _monomials[monomial.degree] = monomial;
    }
}

std::optional<Monomial> Polynomial::getMonomial(Degree degree) const
{
    if (auto monomialIt = _monomials.find(degree);
            monomialIt != _monomials.end())
    {
        return _monomials.at(degree);
    }
    return std::nullopt;
}

Monomials Polynomial::getMonomials() const
{
    std::vector<Monomial> monomials;
    for (const auto& [_, monomial] : _monomials)
    {
        monomials.push_back(monomial);
    }
    std::sort(monomials.begin(),
              monomials.end(),
              [](const Monomial& lhs, const Monomial& rhs)
              {
                    return lhs.degree < rhs.degree;
              });
    return monomials;
}

Degree Polynomial::getDegree() const
{
    Degree maxDegree{};
    for (auto& [degree, _] : _monomials)
    {
        maxDegree = std::max(maxDegree, degree);
    }
    return maxDegree;
}
