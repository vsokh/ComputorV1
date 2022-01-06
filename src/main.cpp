#include <string>
#include <iostream>

#include <stdexcept>

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

    const auto& tokenKindToString = tokenToStringMap.find(rhs.kind)->second;
    o << tokenKindToString;
    if (rhs.value.has_value())
    {
        o << ": " << rhs.value.value();
    }

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

using StringConstIt = typename std::string::const_iterator;
using StringIt = typename std::string::iterator;

class Lexer {
public:
    explicit Lexer(const std::string& str);
    Token getNextToken();

private:

    static std::string removeWhiteSpaces(std::string str);

private:
    std::string _str;

    StringIt _it;
    StringConstIt _end;
};

Lexer::Lexer(const std::string& str)
    : _str{removeWhiteSpaces(str)}
    , _it{_str.begin()}
    , _end{_str.end()}
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

class TokenExtractor
{
public:
    virtual Token extract(StringIt& it, StringConstIt end) = 0;
    virtual ~TokenExtractor() = default;
};

class UnknownTokenExtractor : public TokenExtractor
{
public:
    virtual Token extract(StringIt& it, StringConstIt end) override;
};

Token UnknownTokenExtractor::extract(StringIt& it, StringConstIt end)
{
    static const std::string str = "X^";
    auto strIt = str.begin();
    while (it != end && strIt != str.end() && *it == *strIt)
    {
        ++it;
        ++strIt;
    }
    if (it == end || strIt != str.end())
    {
        throw std::logic_error("Wrong unknown term");
    }
    while (*it < '0' || '2' < *it ||
          ((it + 1) != end && *(it + 1) >= '0' && *(it + 1) <= '9'))
    {
        throw std::logic_error("Wrong unknown term");
    }

    ++it;
    return {TokenKind::Unknown, std::nullopt};
}

class OperationTokenExtractor : public TokenExtractor
{
public:
    Token extract(StringIt& it, StringConstIt end) override;
};

Token OperationTokenExtractor::extract(StringIt& it, StringConstIt end)
{
    if (it == end)
    {
        throw std::logic_error("Wrong operation term");
    }

    static const std::unordered_map<char, Token>
        charToTokenMap = {
            {'+', {TokenKind::Add, std::nullopt}},
            {'-', {TokenKind::Sub, std::nullopt}},
            {'*', {TokenKind::Mul, std::nullopt}},
            {'=', {TokenKind::Equality, std::nullopt}},
    };
    return charToTokenMap.find(*it++)->second;
}

class NumberTokenExtractor : public TokenExtractor
{
public:
    Token extract(StringIt& it, StringConstIt end) override;
};

Token NumberTokenExtractor::extract(StringIt& it, StringConstIt end)
{
    auto beg = it;
    while (it != end && '0' <= *it && *it <= '9')
    {
        ++it;
    }
    if (it == end || *it != '.')
    {
        return {TokenKind::Num, std::stod(std::string{beg, it})};
    }
    ++it;
    while (it != end && '0' <= *it && *it <= '9')
    {
        ++it;
    }
    return {TokenKind::Num, std::stod(std::string{beg, it})};
}

std::unique_ptr<TokenExtractor>
    createTokenExtractor(char ch)
{
    std::unique_ptr<TokenExtractor> extractor{nullptr};

    if (ch == 'X')
    {
        extractor.reset(new UnknownTokenExtractor{});
    }
    else if (ch == '=' || ch == '-' || ch == '*' || ch == '+')
    {
        extractor.reset(new OperationTokenExtractor{});
    }
    else if ('0' <= ch && ch <= '9')
    {
        extractor.reset(new NumberTokenExtractor{});
    }

    return extractor;
}

Token Lexer::getNextToken()
{
    while (_it != _end)
    {
        if (auto extractor = createTokenExtractor(*_it))
        {
            return extractor->extract(_it, _end);
        }
        else
        {
            throw std::logic_error{"Unrecognized term"};
        }
    }
    return {TokenKind::End, std::nullopt};
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    /* if (argc <= 1) */
    /* { */
    /*     return 1; */
    /* } */

    auto lexer = Lexer{"9 * X^0 - 21 * X^2 + 16 * X^1 = 86 * X^1 + 49 * X^0"};
    try
    {
        for (auto token = lexer.getNextToken();
             token != TokenKind::End;
             token = lexer.getNextToken())
        {
            std::cout << token << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
