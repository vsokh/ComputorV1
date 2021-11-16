#pragma once

#include "Lexer.hpp"
#include "Expression.hpp"
#include "Term.hpp"

namespace Translator
{

class Parser
{
public:
    explicit Parser(const std::string& sexpr);
    Expression parse();

private:
    Token nextToken();
    Tokens parseLHS();
    Tokens parseRHS();
    void parseExpression(const Tokens& tokens, Expression& expression);

    template<typename Iterator>
    Term parseTerm(Iterator start, Iterator end) const
    {
        Term result;
        for (auto it = start; it != end; ++it)
        {
            const auto& kind = it->kind;
            const auto& val = it->value;

            switch (kind)
            {
                case TokenKind::Number:
                case TokenKind::Fraction:
                {
                    result.coef = val;
                    break;
                }
                case TokenKind::Unknown:
                {
                    result.exp = val;
                    result.isX = true;
                    break;
                }

                default:
                    break;
            }
        }
        return result;
    }

private:
    Lexer _lexer;
};
} // Translator
