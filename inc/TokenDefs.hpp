#pragma once

#include <vector>
#include <optional>
#include <string>
#include <unordered_map>

namespace Translator
{

enum class TokenKind : uint_least8_t
{
	Number = 0,
	Fraction,
	Add,
	Sub,
	Mul,
	Assign,
	Unknown,
	End
};

struct Token
{
	TokenKind kind;
	double value;


    std::string toStr() const
    {
        std::unordered_map<TokenKind, std::string> um =
        {
            {TokenKind::Number, "Number"},
            {TokenKind::Fraction, "Fraction"},
            {TokenKind::Add, "Add"},
            {TokenKind::Sub, "Sub"},
            {TokenKind::Mul, "Mul"},
            {TokenKind::Assign, "Assign"},
            {TokenKind::Unknown, "Unknown"},
            {TokenKind::End, "End"}
        };
        return um[kind];
    };
};

class BadToken : public std::logic_error
{
public:
    explicit BadToken(const std::string &err)
    : std::logic_error(err)
    {}
};

using TokenOpt = std::optional<Token>;
using Tokens = std::vector<Token>;
} // Translator
