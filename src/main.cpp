#include <iostream>

#include "Lexer.h"
#include "Token.h"

int main(int argc, char **argv)
{
    (void)argc; (void)argv;

    /* auto lexer = Lexer{"9 * X^0 - 21 * X^2 + 16 * X^1 = 86 * X^1 + 49 * X^0"}; */
    auto lexer = Lexer{argv[1]};
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
