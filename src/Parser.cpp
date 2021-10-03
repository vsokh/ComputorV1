#include "Parser.hpp"
#include <iostream>
#include <stack>

using namespace Translator;

Parser::Parser(const std::string& sexpr)
	: _lexer(Lexer(sexpr))
{
}

ParseTree Parser::parse()
{
	std::cout << "BEGIN\n";

	ParseTree tree;
	/* stack of tokens - current state */
	/* current token */
	/* 5 * X^0 + 2 = 0 */
	/**
	 Grammar:
		Number: * | + | - | =
		X: * | + | - | =
		*: Number | X
		+: Number | X
		-: Number | X
		=: Number | X
	**/

	/*
	 */
	std::stack<Token> stack;
	while (const auto& currTkn = _lexer.nextToken())
	{
		const auto& prevTkn = stack.top();

		std::cout << token << std::endl;
	}

	std::cout << "END\n\n";
	return {};
}
