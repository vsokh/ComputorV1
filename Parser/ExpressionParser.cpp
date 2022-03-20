#include "ExpressionParser.hpp"
#include "Exceptions.hpp"

#include <regex>

std::vector<std::string> splitOnTerms(std::string str)
{
    auto isOperation = [](char ch) { return ch == '-' || ch == '+'; };
    std::vector<std::string> result;
    do {
        auto it = std::find_if(str.begin() + 1, str.end(), isOperation);
        result.emplace_back(std::string{str.begin(), it});

        str.erase(str.begin(), it);
    } while (!str.empty());
    return result;
}

Expression ExpressionParser::parse(std::string exprStr)
{
    static const char* termPattern = "([-+]{0,1}0{1}|[-+]{0,1}[0-9]+|[-+]{0,1}[0-9]+\\.[0-9]+)\\*X\\^(0{1}|[1-9]+)";
    Expression result;
    std::smatch base_match;
    std::regex rgx{termPattern};

    const auto& termsStr = splitOnTerms(std::move(exprStr));
    for (auto termStr : termsStr) {
        if (!std::regex_match(termStr, base_match, rgx)) {
            throw InvalidTerm(std::move(termStr));
        }

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
    return result;
}
