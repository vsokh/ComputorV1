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

Polynomial toPolynomial(Tokens&& tokens)
{
    Polynomial polynomial;

    /* bool unknownIsNext = false; */
    Monomial tmpMonomial;
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
                tmpMonomial.coefficient += *token.value * sign * wasEq;
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
                tmpMonomial.degree = static_cast<Degree>(*token.value);
                polynomial.addMonomial(tmpMonomial);

                sign = 1;
                /* unknownIsNext = false; */
                tmpMonomial = Monomial{};
                break;
            }
        }
    }
    return polynomial;
}

Polynomial PolynomialParser::parse(const std::string& expr)
{
    auto tokens = toTokens(expr);
    return toPolynomial(std::move(tokens));
}
