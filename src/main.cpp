#include <iostream>
#include <tuple>

#include "Lexer.h"
#include "Token.h"

struct Term {
    double coef;
    std::uint8_t deg;
};

class TermParser {
public:
    Term parse(const std::string& term);

private:
    Lexer _lexer;
};

struct Expression {
    // x0, x1, x2
    std::tuple<double, double, double> terms;
};

class ExpressionParser {
public:
    ExpressionParser(std::string&& str);
    Expression get();

private:
    TermParser _termParser;
};

class ExpressionWhiteSpaceCleaner {
public:
    explicit ExpressionWhiteSpaceCleaner(std::string&& str);
    std::string get();

private:
    std::string _str;
};

class ExpressionSplitter {
public:
    explicit ExpressionSplitter(std::string&& str);
    std::string get();

private:
    std::string _str;
};

int main(int argc, char **argv)
{
    auto expr = creator.create();

    (void)argc; (void)argv;

    /* auto lexer = Lexer{argv[1]}; */
    /* t0 = 9 - 49 = -40 */
    /* t1 = 16 - 86 = -70 */
    /* t2 = -21 */

    // reducedForm: - 40 * X^0 - 70 * X^1 - 21 X^2 = 0
    // firstTerm := sub num mul unknown | num mul unknown
    // otherTerms := sub or add num unknown
    // Parser - The purpose is to sum up all unknowns into 3 possible buckets: x0, x1, x2.
        // 1 iteration creates a sequence of terms
        // 2 iteration puts all terms into the buckets
    try
    {
        auto parser = Parser{" 9 * X^0 - 21 * X^2 + 16 * X^1 = 86 * X^1 + 49 * X^0"};
        auto expression = parser.parse();
        (void)expression;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
