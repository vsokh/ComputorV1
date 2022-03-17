#include "Parser.hpp"
#include "Exceptions.hpp"

#include <regex>
#include <unordered_map>

static const char* termPattern = "([-+]{0,1}0{1}|[-+]{0,1}[0-9]+|[-+]{0,1}[0-9]+\\.[0-9]+)\\*X\\^(0{1}|[1-9]+)";

Expression Parser::parse(std::string exprStr)
{
    removeWhitespaces(exprStr);

    auto eq = std::find(exprStr.begin(), exprStr.end(), '=');
    if (eq == exprStr.end()) {
        throw InvalidExpression(std::move(exprStr));
    }
    auto lhsStr = std::string{exprStr.begin(), eq};
    auto rhsStr = std::string{eq+1, exprStr.end()};
    if (lhsStr.empty() || rhsStr.empty()) {
        throw InvalidExpression(std::move(exprStr));
    }

    auto lhs = toExpression(std::move(lhsStr));
    auto rhs = toExpression(std::move(rhsStr));

    return combine(lhs, rhs);
}

void Parser::removeWhitespaces(std::string& str)
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

Tokens Parser::toTokens(std::string expr)
{
    Tokens result;
    do {
        auto op = std::find_if(expr.begin()+1, expr.end(), [](char ch){ return ch == '-' || ch == '+'; });
        result.emplace_back(std::string{expr.begin(), op});

        expr.erase(expr.begin(), op);
    } while (!expr.empty());

    return result;
}

Expression Parser::toExpression(std::string expr)
{
    Expression result;
    std::smatch base_match;
    std::regex rgx{termPattern};
    const auto& tokens = toTokens(std::move(expr));
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
            throw InvalidTerm(std::move(str));
        }
    }
    return result;
}

Expression Parser::combine(const Expression& lhs, const Expression& rhs)
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

    Expression result;
    for (auto& [_, term] : degreeToTerm) {
        result.push_back(term);
    }

    std::sort(result.begin(), result.end(),
              [](const Term& a, const Term& b){ return a.degree < b.degree; });

    return Expression{std::move(result)};
}
