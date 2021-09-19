#pragma once

#include "TokenDefs.hpp"
#include <unordered_map>
#include <string>
#include <regex>

namespace Translator
{
using Rules = std::unordered_map<TokenKind, std::string>;

class Lexer
{
public:
	Lexer(std::string sexpr, std::string delim = " ");
	Tokens tokenize(const std::string& sexpr);
	std::vector<std::string> split(std::string str, std::string delim);

	TokenOpt nextToken();
	TokenOpt identifyToken(const std::string& lexeme, const Rules& rules);

	const static Rules& getRules()
	{
		const static Rules rules =
		{
			{TokenKind::Number,    "[0-9]+"},
			{TokenKind::Fraction,  "[0-9]+\\.[0-9]+"},
			{TokenKind::Add,       "\\+"},
			{TokenKind::Sub,       "-"},
			{TokenKind::Mul,       "\\*"},
			{TokenKind::Assign,    "="},
			{TokenKind::Unknown,   "X\\^[0-9]+"}
		};
		return rules;
	}
private:
	std::string _sexpr;
	std::string _delim;
};
} // Translator
std::ostream& operator<<(std::ostream &o, const Translator::TokenKind& token);
std::ostream& operator<<(std::ostream &o, const Translator::TokenOpt& token);
