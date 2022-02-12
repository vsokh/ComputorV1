#include "TokenExtractor.h"
#include "UnknownTokenExtractor.h"
#include "OperationTokenExtractor.h"
#include "NumberTokenExtractor.h"

std::unique_ptr<TokenExtractor> createTokenExtractor(char ch)
{
    if (ch == 'X')
    {
        return std::make_unique<UnknownTokenExtractor>();
    }
    else if (ch == '=' || ch == '-' || ch == '*' || ch == '+')
    {
        return std::make_unique<OperationTokenExtractor>();
    }
    else if ('0' <= ch && ch <= '9')
    {
        return std::make_unique<NumberTokenExtractor>();
    }
    else
    {
        throw std::logic_error{"Unrecognized term"};
    }

    return nullptr;
}
