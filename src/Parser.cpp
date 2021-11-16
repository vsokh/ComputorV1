#include "Parser.hpp"
#include "TokenDefs.hpp"

#include <optional>
#include <unordered_set>

using namespace Translator;

namespace
{
bool isOperation(const Token& token)
{
    static const std::unordered_set<TokenKind> ops =
    {
        TokenKind::Add,
        TokenKind::Sub
    };

    return ops.find(token.kind) != ops.end();
};
}

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
        const auto& op = find_if(tokens.begin(), tokens.end(), isOperation);
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

