#include "Token.h"

#include <unordered_map>

bool Token::operator==(const TokenKind& rhs) const
{
    return this->kind == rhs;
}

bool Token::operator!=(const TokenKind& rhs) const
{
    return !(*this == rhs);
}

bool Token::operator==(const Token& rhs) const
{
    return *this == rhs.kind;
}

bool Token::operator!=(const Token& rhs) const
{
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream &o, const Token& rhs)
{
    static const std::unordered_map<const TokenKind, std::string>
        tokenToStringMap = {
            {TokenKind::Add, "Add"},
            {TokenKind::Sub, "Sub"},
            {TokenKind::Mul, "Mul"},
            {TokenKind::Unknown, "Unknown"},
            {TokenKind::Equality, "Equality"},
            {TokenKind::Num, "Num"},
            {TokenKind::End, "End"}
    };

    const auto& tokenKindToString = tokenToStringMap.find(rhs.kind)->second;
    o << tokenKindToString;
    if (rhs.value.has_value())
    {
        o << ": " << rhs.value.value();
    }

    return o;
}
