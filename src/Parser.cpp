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

void Parser::parseExpression(const Tokens& tokens, Expression& expression)
{
    Tokens tmp = tokens;
    while (!tmp.empty())
    {
        const auto& op = find_if(tmp.begin(), tmp.end(), isOperation);
        const auto& term = parseTerm(tmp.begin(), op);
        expression.update(term);
        tmp.erase(op+1);
    }
}

Parser::Parser(const std::string& sexpr)
    : _lexer(Lexer(sexpr))
{
}

Expression Parser::parse()
{
    Expression expression;
    const auto& lhs = parseLHS();
    parseExpression(lhs, expression);

    const auto& rhs = parseRHS();
    parseExpression(rhs, expression);
    return expression;
}
