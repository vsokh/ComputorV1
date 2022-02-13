#include "Lexer.h"
#include "TokenExtractor.h"

Lexer::Lexer(const std::string& str)
    : _str{removeWhiteSpaces(str)}
    , _it{_str.begin()}
    , _begin{_str.begin()}
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

Token Lexer::getNextToken()
{
    if (_it == _end)
    {
        return {TokenKind::End, std::nullopt};
    }

    if (_it == _begin)
    {
        if (*_it != '-' && (*_it < '0' || *_it > '9'))
        {
            throw std::logic_error{
                "Wrong token at the beginning of the expression"
            };
        }
    }

    auto extractor = createTokenExtractor(*_it);
    return extractor->extract(_it, _end);
}

