#include "Lexer.hpp"
#include <iostream>
#include <optional>

using namespace Translator;

Lexer::Lexer(std::string sexpr, std::string delim)
    : _sexpr(std::move(sexpr))
    , _delim(delim)
{
}

Token Lexer::nextToken()
{
    const auto& pos = _sexpr.find(_delim);
    if (pos != std::string::npos)
    {
        const auto& str = _sexpr.substr(0, pos);
        const auto& token = identifyToken(str, getRules());
        _sexpr.erase(0, str.length() + _delim.length());
        return token;
    }

    const auto& token = identifyToken(_sexpr, getRules());
    _sexpr.erase(0, _sexpr.length());
    return token;
}

std::vector<std::string> Lexer::split(std::string str, std::string delim)
{
    std::vector<std::string> result;
    std::string token;
    std::size_t pos = 0;
    while ((pos = str.find(delim)) != std::string::npos)
    {
        const auto& sstr = str.substr(0, pos);
        if (!sstr.empty() && delim != sstr)
        {
            result.emplace_back(sstr);
        }
        str.erase(0, pos + delim.length());
    }
    if (!str.empty())
        result.emplace_back(str);
    return result;
}

Token Lexer::identifyToken(const std::string& lexeme, const Rules& rules)
{
    if (lexeme.empty())
    {
        return {TokenKind::End, 0.0};
    }

    double coef = 1.0;
    std::regex pattern;
    std::optional<Token> token;
    for (const auto& rule : rules)
    {
        pattern = rule.first;
        if (!std::regex_match(lexeme, pattern))
            continue;

        TokenKind kind = TokenKind::End;
        double value = 0.0;
        switch (rule.second)
        {
            case TokenKind::Number:
            case TokenKind::Fraction:
            {
                value = std::stod(lexeme) * coef;
                coef = coef < coef ? -coef : coef;
                break;
            }
            case TokenKind::Sub:
            {
                coef = -coef;
                kind = TokenKind::Add;
                break;
            }
            case TokenKind::Unknown:
            {
                value = std::stod(split(lexeme, "^")[1]);
            }
            case TokenKind::Add:
            case TokenKind::End:
            case TokenKind::Mul:
            case TokenKind::Assign:
                break;
        }
        token = Token{kind, value};
    }

    if (!token)
        throw std::logic_error("Unknown token type.");
    return *token;
}

std::ostream& operator<<(std::ostream &o, const TokenKind& token)
{
    std::unordered_map<TokenKind, std::string> um =
    {
        {TokenKind::Number, "Number"},
        {TokenKind::Add, "Add"},
        {TokenKind::Sub, "Sub"},
        {TokenKind::Mul, "Mul"},
        {TokenKind::Assign, "Assign"},
        {TokenKind::Unknown, "Unknown"},
        {TokenKind::Fraction, "Fraction"},
        {TokenKind::End, "End"},
    };
    o << um[token];
    return o;
}

std::ostream& operator<<(std::ostream &o, const TokenOpt& token)
{
    if (token)
        o << token->kind << " " << token->value;
    return o;
}
