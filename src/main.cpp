#include <iostream>
#include <tuple>
#include <vector>

#include "Lexer.h"
#include "Token.h"

struct Term
{
    double coef;
    int deg;
};

std::vector<Term> toTerms(std::vector<Token> tokens)
{
    std::vector<Term> terms;

    /* bool unknownIsNext = false; */
    Term term;
    double sign = 1;
    double wasEq = 1;

    for (auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        switch (it->kind)
        {
            case TokenKind::End:
            {
                return terms;
            }
            case TokenKind::Equality:
            {
                wasEq = -1;
                break;
            }
            case TokenKind::Num:
            {
                term.coef += *it->value * sign * wasEq;
                break;
            }
            case TokenKind::Mul:
            {
                /* unknownIsNext = true; */
                break;
            }
            case TokenKind::Sub:
            {
                sign *= sign > 0 ? -1 : 1;
                break;
            }
            case TokenKind::Add:
            {
                sign *= sign < 0 ? -1 : 1;
                break;
            }
            case TokenKind::Unknown:
            {
                term.deg = *it->value;
                terms.push_back(term);

                sign = 1;
                /* unknownIsNext = false; */
                term = Term{};
                break;
            }
        }
    }
    return terms;
}

int main(int argc, char **argv)
{
    // TODO: check on sematic mistakes:
    // 1. No equality sign
    // 2. A term which doesn't follow the form - a*X^p
    // 3. etc
    // TODO: Support higher term's degree
    (void)argv;
    if (argc <= 1)
    {
        return 1;
    }

    std::string expr = argv[1];
    /* 1 roots */
    /* std::string expr = "5 * X^0 + 4 * X^1 = 4 * X^0"; */
    /* 2 roots */
    /* std::string expr = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"; */


    // ------------- string to tokens --------------
    auto lexer = Lexer{expr};
    auto token = lexer.getNextToken();
    std::vector<Token> tokens;
    while (token != TokenKind::End)
    {
        tokens.push_back(token);
        token = lexer.getNextToken();
    }
    // ---------------------------------------------


    // ----------- tokens to expression ------------
    auto terms = toTerms(tokens);
    std::sort(terms.begin(),
              terms.end(),
              [](const Term& lhs, const Term& rhs)
              {
                  return lhs.deg < rhs.deg;
              });

    Term x0{0, 0}, x1{0, 1}, x2{0, 2};
    for (auto term : terms)
    {
        if (term.deg == 0) x0.coef += term.coef;
        if (term.deg == 1) x1.coef += term.coef;
        if (term.deg == 2) x2.coef += term.coef;
    }
    // --------------------------------------------


    // ------------ show reduced form -------------
    std::cout << "Reduced form: ";
    if (x0.coef < 0.0)      std::cout << "- " << (-1*x0.coef) << " * X^0";
    else if (x0.coef > 0.0) std::cout << x0.coef << " * X^0";

    if (x1.coef < 0.0)      std::cout << " - " << (-1*x1.coef) << " * X^1";
    else if (x1.coef > 0.0) std::cout << " + " << x1.coef << " * X^1";

    if (x2.coef < 0.0)      std::cout << " - " << (-1*x2.coef) << " * X^2";
    else if (x2.coef > 0.0) std::cout << " + " << x2.coef << " * X^2";
    std::cout << " = 0" << std::endl;
    // --------------------------------------------


    // --------- exrepssion to a solution ---------
    auto degree = 0;
    degree = x1.coef != 0.0 ? x1.deg : degree;
    degree = x2.coef != 0.0 ? x2.deg : degree;
    std::cout << "Polynomial degree: " << degree << std::endl;
    std::cout << "The solution is:\n";
    if (degree == 0)
    {
    }
    else if (degree == 1)
    {
        std::cout << -1*x0.coef / x1.coef << std::endl;
    }
    else if (degree == 2)
    {
        double a = x2.coef;
        double b = x1.coef;
        double c = x0.coef;
        double D = b*b - 4*a*c;
        double r1 = (-1*b - std::sqrt(D))/(2*a);
        double r2 = (-1*b + std::sqrt(D))/(2*a);
        std::cout << r1 << std::endl;
        std::cout << r2 << std::endl;
    }
    // ---------------------------------------------
    return 0;
}
