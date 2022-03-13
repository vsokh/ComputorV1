#include <exception>
#include <iostream>
#include <regex>
#include <unordered_map>

struct Term {
    double coef;
    double degree;
};

using Tokens = std::vector<std::string>;
using Terms = std::vector<Term>;

void removeWhitespaces(std::string& str)
{
    static const std::string whitespaces = " \n\r\t\f\v";
    str.erase(std::remove_if(str.begin(), str.end(),
                             [](char ch)
                             {
                                 return std::any_of(whitespaces.begin(), whitespaces.end(),
                                                    [&ch](char whitespace)
                                                    {
                                                        return ch == whitespace;
                                                    });
                             }), str.end());
}

Tokens toTokens(std::string expr)
{
    Tokens result;
    do {
        auto op = std::find_if(expr.begin()+1, expr.end(), [](char ch){ return ch == '-' || ch == '+'; });
        result.emplace_back(std::string{expr.begin(), op});

        expr.erase(expr.begin(), op);
    } while (!expr.empty());

    return result;
}

Terms toTerms(Tokens tokens)
{
    Terms result;

    std::smatch base_match;
    std::regex rgx{"([-+]{0,1}0{1}|[-+]{0,1}[1-9]+|[-+]{0,1}[1-9]+\\.[0-9]+)\\*X\\^(0{1}|[1-9]+)"};
    for (auto str : tokens) {
        if (std::regex_match(str, base_match, rgx)) {
            Term term;
            bool hasCoef{false};
            bool hasDegree{false};
            for (size_t i = 1; i < base_match.size(); ++i) {
                auto tkn = base_match[i].str();
                if (!hasCoef) {
                    hasCoef=true;
                    term.coef = std::stod(tkn);
                }
                else if (!hasDegree) {
                    hasDegree=true;
                    term.degree = std::stod(tkn);
                }
            }
            result.push_back(term);
        }
        else {
            std::cout << "Wrong term: "<< str << "\n";
        }
    }
    return result;
}

Terms toExpression(std::string expr)
{
    auto tokens = toTokens(std::move(expr));
    auto terms = toTerms(std::move(tokens));
    return terms;
}

Terms combine(const Terms& lhs, const Terms& rhs)
{
    std::unordered_map<double, Term> degreeToTerm;
    auto update = [&degreeToTerm](Term term, double multiplier=1.0) {
        if (auto it = degreeToTerm.find(term.degree);
                it != degreeToTerm.end()) {
            it->second.coef += multiplier*term.coef;
        }
        else {
            degreeToTerm.insert({term.degree, term});
        }
    };

    for (auto term : lhs) {
        update(term);
    }

    for (auto term : rhs) {
        update(term, -1);
    }

    Terms result;
    for (auto& [_, term] : degreeToTerm) {
        result.push_back(term);
    }

    return result;
}

int main()
{
    std::string exprStr = "-2.0*X^4 - 1.0*X^3 + 1*X0.0 - 1*X^0 = 1*X^0";
    std::cout << "expr: " << exprStr << std::endl;
    removeWhitespaces(exprStr);

    auto eq = std::find(exprStr.begin(), exprStr.end(), '=');
    if (eq == exprStr.end()) {
        std::cout << "Expression is invalid" << std::endl;
        return 1;
    }
    auto lhsStr = std::string{exprStr.begin(), eq};
    auto rhsStr = std::string{eq+1, exprStr.end()};
    if (lhsStr.empty() || rhsStr.empty()) {
        std::cout << "Expression is invalid" << std::endl;
        return 1;
    }

    auto lhs = toExpression(std::move(lhsStr));
    auto rhs = toExpression(std::move(rhsStr));

    auto expr = combine(lhs, rhs);
    for (auto term : expr) {
        std::cout << term.coef << ", " << term.degree << std::endl;
    }

    return 0;
}
