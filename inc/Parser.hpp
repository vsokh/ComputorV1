#pragma once
#include "TokenDefs.hpp"
#include "Lexer.hpp"

namespace Translator
{

class ParseTree
{

};

class Parser {
	public:
		Parser(const std::string& sexpr);
		ParseTree parse();

	private:
		Lexer _lexer;
};
} // Translator
