#include <iostream>
#include <vector>
#include <variant>
#include <string_view>

struct Term
{
	double coeficient;
	int exponent;
};

enum class Operation
{
	Add = 0, Sub, Equal
};

class Expression
{
public:
	void addTerm(const Term& term)
	{
	}

	void addOperation(const Operation& op)
	{
	}

	void getReducedForm()
	{
	}

private:
	bool wasEqualitySign{false};

	std::vector<std::variant<Term, Operation>> lhs;
	std::vector<std::variant<Term, Operation>> rhs;
};

class Parser
{
	private:
		using Token = std::variant<Term, Operation>;
		using Tokens = std::vector<Token>;

public:
	Expression parse(std::string_view expression)
	{
		Expression result;
		for (const auto& token : parseTokens(expression))
		{
			std::visit(overloaded {
				[&result](Term& t) {
					result.addTerm(t);
				},
				[&result](const Operation& op) {
					result.addOperation();
				},
			}, token);
		}
		return result;
	}

private:
	Tokens parseTokens(std::string_view term)
	{
		for (str : strs)
		{
			if (match term pattern)
				parseTerm(str);
			else if (match op pattern)
				parserOperation();
			else
				throw an error
		}
	}

	Term parseTerm(std::string_view term)
	{
		Term term;
		term.coeficient = parseCoeficient();
		term.exponent = parseExponent();
		return term;
	}

	double parseCoeficient(std::string_view num)
	{
		// parse coef by pattern
	}

	int parseExponent(std::string_view exponent)
	{
		// parse exponent by pattern
	}

	Operation parseOperation(std::string_view op)
	{
		// parse exponent by patterns
	}
};

int main()
{
	auto parser = Parser{};
	auto expression = parser.parse("4 * X^15 + 79 * X^5 = 11 * X^17 - 89 * X^11");
	return 0;
}

