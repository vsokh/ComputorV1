#include "Parser.hpp"
#include "Exceptions.hpp"
#include "SequenceUtils.hpp"

#include <regex>
#include <unordered_map>

static const char* termPattern = "([-+]{0,1}0{1}|[-+]{0,1}[0-9]+|[-+]{0,1}[0-9]+\\.[0-9]+)\\*X\\^(0{1}|[1-9]+)";

namespace {

void removeWhitespaces(std::string &str)
{
    Utils::cleanSequence(str,
                         [](char ch) {
                             return ch == '\n' ||
                                    ch == '\r' ||
                                    ch == '\t' ||
                                    ch == '\f' ||
                                    ch == '\v' ||
                                    ch == ' ';
                         });
}
} // namespace

ExpressionParser::ExpressionParser(std::string exprStr)
    : _exprStr{std::move(exprStr)}
{
}


Expression ExpressionParser::parse()
{
    Expression result;
    std::smatch base_match;
    std::regex rgx{termPattern};

    const auto& tokens = Utils::splitSequence(std::move(_exprStr),
                                         [](char ch) { return ch == '-' || ch == '+'; });
    for (auto token : tokens)
    {
        if (std::regex_match(token, base_match, rgx))
        {
            Term term;
            bool hasCoef{false};
            bool hasDegree{false};
            for (size_t i = 1; i < base_match.size(); ++i)
            {
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
            throw InvalidTerm(std::move(token));
        }
    }
    return result;
}

ExpressionCombiner::ExpressionCombiner(const Expression& lhs, const Expression& rhs)
    : _lhs{lhs}, _rhs{rhs}
{
}

Expression ExpressionCombiner::combine()
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

    for (auto term : _lhs) {
        update(term);
    }

    for (auto term : _rhs) {
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

ExpressionSplitter::ExpressionSplitter(std::string exprStr)
        : _exprStr(std::move(exprStr))
{
}

std::tuple<Expression, Expression> ExpressionSplitter::split()
{
    auto it = std::find_if(_exprStr.begin(), _exprStr.end(), [](char ch){ return ch == '='; });
    if (it == _exprStr.end()) {
        throw InvalidExpression(std::move(_exprStr));
    }

    auto lhs = ExpressionParser{std::string{_exprStr.begin(), it}}.parse();
    auto rhs = ExpressionParser{std::string{it + 1, _exprStr.end()}}.parse();
    return {lhs, rhs};
}

FormulaParser::FormulaParser(std::string formulaStr)
        : _formulaStr(std::move(formulaStr))
{
}

Expression FormulaParser::parse()
{
    auto& frml = _formulaStr;
    removeWhitespaces(frml);

    auto splitter = ExpressionSplitter{std::move(_formulaStr)};
    auto [lhs, rhs] = splitter.split();
    return ExpressionCombiner{lhs, rhs}.combine();
}
