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
                term.coefficient += *token.value * sign * wasEq;
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
                term.degree = *token.value;
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

Expression Parser::reduceTerms(const Terms& terms)
{
    Expression expression;
    for (const auto& term : terms)
    {
        if (term.degree == 0) expression.x0.coefficient += term.coefficient;
        if (term.degree == 1) expression.x1.coefficient += term.coefficient;
        if (term.degree == 2) expression.x2.coefficient += term.coefficient;
    }
    return expression;
}

void Parser::sortTerms(Terms& terms)
{
    std::sort(terms.begin(),
              terms.end(),
              [](const Term& lhs, const Term& rhs)
              {
                  return lhs.degree < rhs.degree;
              });
}

Expression Parser::parse(const std::string& expr)
{
    const auto& tokens = toTokens(expr);
    auto terms = toTerms(tokens);

    sortTerms(terms);
    return reduceTerms(terms);
}
