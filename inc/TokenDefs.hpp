#pragma once

#include <vector>
#include <optional>

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
	Unknown
};

struct Token
{
	TokenKind kind;
	double value;
};

using TokenOpt = std::optional<Token>;
using Tokens = std::vector<TokenOpt>;
} // Translator
