#include <iostream>

#include "Parser.hpp"
#include "Exceptions.hpp"

void test(std::string testName, std::string expr)
{
    std::cout << testName << ": ";
    try {
        Parser::parse(expr);
    }
    catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}

struct TestCase {
    std::string testName;
    std::string expr;
};

const static std::vector<TestCase> redTestCases = {
        {"No left side", "= 1*X^1"},
        {"No right side", "1*X^1 ="},
        {"Two equality signs", "1*X^1 == 1*X^1"},
        {"Minus sign before equality sign", "1*X^1 - = 1*X^1"},
        {"Wrong monomial form - 0 at the left side", "0 = 1*X^1"},
        {"Wrong monomial form - 0 at the right side", "1*X^1 = 0"},
        {"No coefficient", "*X^1 = 1*X^1"},
        {"Double mul sign", "1**X^1 = 1*X^1"},
        {"Double X sign", "1*XX^1 = 1*X^1"},
        {"Double ^ sign", "1*X^^1 = 1*X^1"},
        {"Unknown symbol", "1*X$^1 = 1*X^1"},
};

int main()
{
    std::for_each(redTestCases.begin(), redTestCases.end(),
                  [](const TestCase &testCase) { test(testCase.testName, testCase.expr); });
    return 0;
}