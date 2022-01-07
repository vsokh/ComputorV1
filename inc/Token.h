#pragma once

#include <optional>
#include <ostream>

enum class TokenKind : uint8_t
{
    Add,
    Sub,
    Mul,
    Unknown,
    Equality,
    Num,
    End
};

using TokenValue = std::optional<double>;

struct Token
{
    bool operator==(const TokenKind& rhs) const;
    bool operator!=(const TokenKind& rhs) const;

    bool operator==(const Token& rhs) const;
    bool operator!=(const Token& rhs) const;

    TokenKind kind;
    TokenValue value;
};

std::ostream& operator<<(std::ostream &o, const Token& rhs);
