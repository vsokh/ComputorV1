#include <iostream>
#include <exception>
#include <vector>

#include "Lexer.hpp"
#include "Parser.hpp"

using namespace Translator;

class Expression
{
	public:
		Expression() = default;
		Expression(const Tokens& tokens)
			: _tokens(tokens)
		{}

	private:
		Tokens _tokens;
};

class Solution {};

class ExpressionTranslator
{
	public:
		Expression translate(const std::string& sexpr)
		{
			Lexer lexer(sexpr);
			Parser parser(lexer);
			const auto& parseTree = parser.parse();
			(void)parseTree;
			return {};
		}
};

class Computor
{
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
	if (argc < 2)
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
