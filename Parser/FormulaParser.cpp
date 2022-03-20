#include "FormulaParser.hpp"
#include "ExpressionParser.hpp"
#include "Exceptions.hpp"

#include <unordered_map>

namespace
{

void removeWhitespaces(std::string &str)
{
    auto isWhitespace = [](char ch) {
        return ch == '\n' || ch == '\r' || ch == '\t' ||
               ch == '\f' || ch == '\v' || ch == ' ';
    };
    str.erase(std::remove_if(str.begin(), str.end(), isWhitespace), str.end());
}

}

std::tuple<Expression, Expression> splitOnSides(const std::string &formulaStr)
{
    auto it =
            std::find_if(formulaStr.begin(), formulaStr.end(),
                         [](char ch) { return ch == '='; });
    if (it == formulaStr.end()) {
        throw InvalidExpression(std::move(formulaStr));
    }

    return {ExpressionParser::parse(std::string{formulaStr.begin(), it}),
            ExpressionParser::parse(std::string{it + 1, formulaStr.end()})};
}

Expression shiftToOneSide(const Expression& lhs, const Expression& rhs)
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

Expression FormulaToStandardFormPolynomialParser::parse(std::string formulaStr)
{
    removeWhitespaces(formulaStr);
    auto [lhs, rhs] = splitOnSides(formulaStr);
    return shiftToOneSide(lhs, rhs);
}
