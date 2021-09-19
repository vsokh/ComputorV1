#include "Parser.hpp"
#include <iostream>

using namespace Translator;

Parser::Parser(const Lexer& lexer)
	: _lexer(lexer)
{
}

ParseTree Parser::parse()
{
	std::cout << "BEGIN\n";
	while (const auto& token = _lexer.nextToken())
	{
		std::cout << token << std::endl;
	}
	std::cout << "END\n\n";
	return {};
}
