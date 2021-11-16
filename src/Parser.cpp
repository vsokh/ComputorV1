#include "Parser.hpp"
#include "TokenDefs.hpp"

#include <optional>
#include <unordered_set>

using namespace Translator;

Token Parser::nextToken()
{
    return _lexer.nextToken();
}

Tokens Parser::parseLHS()
{
    Tokens result;
    auto token = nextToken();
    while (token.kind != TokenKind::Assign && token.kind != TokenKind::End)
    {
        result.push_back(token);
        token = nextToken();
    }
    if (token.kind == TokenKind::End || result.empty())
        throw std::logic_error("Incomplete expression!");

    return result;
}

Tokens Parser::parseRHS()
{
    Tokens result;
    auto token = nextToken();
    while (token.kind != TokenKind::End)
    {
        result.push_back(token);
        token = nextToken();
    }
    if (result.empty())
        throw std::logic_error("Incomplete expression!");

    return result;
}

void Parser::parseExpression(Tokens& tokens, Expression& expression, bool toNegate)
{
    while (!tokens.empty())
    {
        const auto& op = find_if(tokens.begin(), tokens.end(),
                [](const Token& token)
                {
                    return token.kind == TokenKind::Add ||
                           token.kind == TokenKind::Sub;
                });
        auto term = parseTerm(tokens.begin(), op);
        if (toNegate)
        {
            term.coef = -term.coef;
        }
        expression.update(term);

        if (op == tokens.end())
            tokens.clear();
        else
            tokens.erase(op);
    }
}

Parser::Parser(const std::string& sexpr)
    : _lexer(Lexer(sexpr))
{
}

Expression Parser::parse()
{
    Expression expression;
    auto lhs = parseLHS();
    parseExpression(lhs, expression, false);

    auto rhs = parseRHS();
    parseExpression(rhs, expression, true);
    return expression;
}

