#include <iostream>

#include <algorithm>

#include <regex>

#include <exception>

#include <vector>

class Expression
{
};

class Lexer
{
public:
	Expression tokenize(std::vector<std::string> const& seq)
	{
		(void)seq;
		return Expression{};
	}
};

class Parser
{
public:
	std::vector<std::string> parse(std::string const& sexpr)
	{
		(void)sexpr;
		return {};
	}
};

class ExpressionTranslator
{
public:
	Expression translate(std::string const& sexpr)
	{
		Parser parser;
		auto seq = parser.parse(sexpr);

		Lexer lexer;
		return lexer.tokenize(seq);
	}
};

class Solution
{
};

class Computor
{
// Incapsulates: Parser & Lexer
public:
	Computor(const std::string& expression)
		: _expr(ExpressionTranslator{}.translate(expression))
	{
	}

	Solution compute()
	{
		return Solution{};
	}

private:
	Expression _expr;
};

class Presenter
{
public:
	Presenter(const Solution& sol)
	{
		(void)sol;
	}
	void present()
	{
	}
};

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage" << std::endl;
		return 0;
	}

	try
	{
		Computor c(argv[1]);
		const auto& solution = c.compute();

		Presenter p(solution);
		p.present();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
