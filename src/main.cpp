#include <string>
#include <iostream>

#include <variant>
#include <optional>

#include <utility>

#include <unordered_map>
#include <vector>

#include <regex>

enum class TokenKind : uint8_t {
    Add, Sub, Mul, Unknown, Equality, Num, End
};

using TokenValue = std::optional<double>;

struct Token {
    bool operator==(const TokenKind& rhs) const;
    bool operator!=(const TokenKind& rhs) const;

    bool operator==(const Token& rhs) const;
    bool operator!=(const Token& rhs) const;

    friend std::ostream& operator<<(std::ostream &o, const Token& rhs);

    TokenKind kind;
    TokenValue value;
};

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

    const auto& tokenToString = tokenToStringMap.find(rhs.kind)->second;
    o << tokenToString;
    return o;
}

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

class Lexer {
public:
    explicit Lexer(const std::string& str);
    Token getNextToken();

private:
    using StringConstIt = typename std::string::const_iterator;

    static TokenValue retrieveTokenValue(const TokenKind& kind,
                                         StringConstIt leftIt,
                                         StringConstIt rightIt,
                                         StringConstIt endIt);

    static std::string removeWhiteSpaces(std::string str);

private:
    std::string _str;

    StringConstIt _posLeft;
    StringConstIt _posRight;
};

Lexer::Lexer(const std::string& str)
    : _str{removeWhiteSpaces(str)}
    , _posLeft{_str.begin()}
    , _posRight{_str.begin()}
{}

std::string Lexer::removeWhiteSpaces(std::string str)
{
    static const std::string whitespaces = " \n\r\t\f\v";
    str.erase(
            std::remove_if(
                str.begin(),
                str.end(),
                [](char ch)
                {
                    return std::any_of(
                            whitespaces.begin(),
                            whitespaces.end(),
                            [&ch](char whitespace)
                            {
                                return ch == whitespace;
                            });
                }),
            str.end());
    return str;
}

TokenValue Lexer::retrieveTokenValue(const TokenKind& kind,
                                     StringConstIt leftIt,
                                     StringConstIt rightIt,
                                     StringConstIt endIt)
{

    if (static const std::vector<TokenKind> noValueTokens = {
                TokenKind::Add,
                TokenKind::Sub,
                TokenKind::Mul,
                TokenKind::Equality,
                TokenKind::End,
        }; std::find(noValueTokens.begin(),
                  noValueTokens.end(), kind) != noValueTokens.end())
    {
        return std::nullopt;
    }

    if (kind == TokenKind::Unknown)
    {
        while (leftIt != rightIt &&
               leftIt != endIt &&
               (*leftIt < '0' || '9' < *leftIt))
        {
            ++leftIt;
        }
    }

    return std::stod(std::string{leftIt, rightIt});
}

Token Lexer::getNextToken()
{
    static const std::unordered_map<std::string, TokenKind>
        lexemeToTokenMap =
    {
            {"\\+", TokenKind::Add},
            {"-", TokenKind::Sub},
            {"\\*", TokenKind::Mul},
            {"X\\^[0-2]", TokenKind::Unknown},
            {"=", TokenKind::Equality},
            {"[0-9]+(?!\\.)", TokenKind::Num}, // TODO: Fix leading zeros
            {"[0-9]+\\.[0-9]+", TokenKind::Num}, // TODO: Fix leading zeros
    };

    // TODO: refactor
    auto isToken = [&lexemeToTokenMap](StringConstIt leftIt, StringConstIt rightIt)
    {
        return std::any_of(lexemeToTokenMap.begin(),
                           lexemeToTokenMap.end(),
                           [&leftIt, &rightIt](const std::pair<std::string, TokenKind>& pair)
                           {
                                return std::regex_match(leftIt, rightIt, std::regex{pair.first});
                           });
    };

    while (_posLeft != _str.end())
    {
        for (const auto& [lexeme, tokenKind] : lexemeToTokenMap)
        {
            if (std::regex_match(_posLeft,
                                 _posRight,
                                 std::regex{lexeme}))
            {
                // TODO: refactor
                // If we in the context of a number and
                // the next character is neither a token nor the end of the string,
                // we continue the match.
                // This helps us to distinguish between whole and fractionl tokens.
                if (tokenKind == TokenKind::Num &&
                    _posRight != _str.end() &&
                    !isToken(_posRight,
                             _posRight + 1))
                {
                    break;
                }

                auto posLeft = _posLeft;
                auto posRight = _posRight;
                _posLeft = _posRight;

                if (_posRight != _str.end())
                {
                    ++_posRight;
                }

                return
                {
                    tokenKind,
                    retrieveTokenValue(tokenKind, posLeft, posRight, _str.end())
                };
            }
        }
        ++_posRight;
    }
    return {TokenKind::End, std::nullopt};
}

int main()
{
    auto lexer = Lexer{"5.0 + 5 = 5.0 + 5"};
// TODO: make range-based loop
//    for (const auto& tokenIt : lexer.tokens())
//    {
//        std::cout << *tokenIt << std::endl;
//    }
    for (auto token = lexer.getNextToken();
         token != TokenKind::End; token = lexer.getNextToken())
    {
        std::cout << token << std::endl;
    }
    return 0;
}
