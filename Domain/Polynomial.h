#pragma once

#include "Monomial.h"

#include <unordered_map>
#include <optional>

class Polynomial
{
public:
    void addMonomial(Monomial monomial);
    [[nodiscard]] std::optional<Monomial> getMonomial(Degree degree) const;
    [[nodiscard]] Degree getDegree() const;
    [[nodiscard]] Monomials getMonomials() const;

private:
    void adjustDegree(const Monomial& monomial);

private:
    std::unordered_map<Degree, Monomial> _monomials;
    Degree _degree;
};
