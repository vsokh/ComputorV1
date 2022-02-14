#include "Parser.h"
#include "Lexer.h"

Tokens Parser::toTokens(const std::string& expr)
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

Terms Parser::toTerms(const Tokens& tokens)
{
    Terms terms;

    /* bool unknownIsNext = false; */
    Term term;
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
                term.coef += *token.value * sign * wasEq;
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
                term.deg = *token.value;
                terms.push_back(term);

                sign = 1;
                /* unknownIsNext = false; */
                term = Term{};
                break;
            }
        }
    }
    return terms;
}

Expression Parser::parse(const std::string& expr)
{
    const auto& tokens = toTokens(expr);
    auto terms = toTerms(tokens);

    // Reducer
    std::sort(terms.begin(),
              terms.end(),
              [](const Term& lhs, const Term& rhs)
              {
                  return lhs.deg < rhs.deg;
              });
    Expression expression;
    for (auto term : terms)
    {
        if (term.deg == 0) expression.x0.coef += term.coef;
        if (term.deg == 1) expression.x1.coef += term.coef;
        if (term.deg == 2) expression.x2.coef += term.coef;
    }
    return expression;
}

