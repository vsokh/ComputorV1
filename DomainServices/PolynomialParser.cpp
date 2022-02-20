#include "PolynomialParser.h"
#include "Lexer.h"

#include "../Domain/Token.h"
#include "../Domain/Polynomial.h"

#include <unordered_map>

Tokens toTokens(const std::string& expr)
{
    Tokens tokens;

    auto lexer = Lexer{expr};
    for (auto token = lexer.getNextToken();
              token != TokenKind::End;
              token = lexer.getNextToken())
    {
        tokens.push_back(token);
    }
    return tokens;
}

Monomials toMonomials(Tokens&& tokens)
{
    Monomials monomials;

    /* bool unknownIsNext = false; */
    Monomial monomial;
    double sign = 1;
    double wasEq = 1;

    for (const auto& token : tokens)
    {
        switch (token.kind)
        {
            case TokenKind::End:
            {
                break;
            }
            case TokenKind::Equality:
            {
                wasEq = -1;
                break;
            }
            case TokenKind::Num:
            {
                monomial.coefficient += *token.value * sign * wasEq;
                break;
            }
            case TokenKind::Mul:
            {
                /* unknownIsNext = true; */
                break;
            }
            case TokenKind::Sub:
            {
                sign *= sign > 0 ? -1 : 1;
                break;
            }
            case TokenKind::Add:
            {
                sign *= sign < 0 ? -1 : 1;
                break;
            }
            case TokenKind::Unknown:
            {
                monomial.degree = static_cast<Degree>(*token.value);
                monomials[monomial.degree] += monomial;

                sign = 1;
                /* unknownIsNext = false; */
                monomial = Monomial{};
                break;
            }
        }
    }
    return monomials;
}

Polynomial toPolynomial(Monomials&& monomials)
{
    std::unordered_map<Degree, Monomial> degreeToMonomialMap;
    for (const auto& [degree, monomial] : monomials)
    {
        degreeToMonomialMap[degree] = monomial;
    }

    for (const auto& [degree, monomial] : monomials)
    {
        degreeToMonomialMap[degree] += monomial;
    }

    Polynomial polynomial;
    for (const auto& [_, monomial] : degreeToMonomialMap)
    {
        polynomial.addMonomial(monomial);
    }
    return polynomial;
}

Polynomial PolynomialParser::parse(const std::string& expr)
{
    auto tokens = toTokens(expr);
    auto monomials = toMonomials(std::move(tokens));
    auto polynomial = toPolynomial(std::move(monomials));
    return polynomial;
}
