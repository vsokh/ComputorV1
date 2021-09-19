#include "Lexer.hpp"
#include <iostream>

using namespace Translator;

Lexer::Lexer(std::string sexpr, std::string delim)
	: _sexpr(std::move(sexpr))
	, _delim(delim)
{
}

TokenOpt Lexer::nextToken()
{
	TokenOpt token;
	const auto& pos = _sexpr.find(_delim);
	if (pos != std::string::npos)
	{
		const auto& str = _sexpr.substr(0, pos);
		token = identifyToken(str, getRules());
		_sexpr.erase(0, str.length() + _delim.length());
	}
	else
	{
		token = identifyToken(_sexpr, getRules());
		_sexpr.erase(0, _sexpr.length());
	}
	return token;
}

std::vector<std::string> Lexer::split(std::string str, std::string delim)
{
	std::vector<std::string> result;
	std::string token;
	std::size_t pos = 0;
	while ((pos = str.find(delim)) != std::string::npos)
	{
		const auto& sstr = str.substr(0, pos);
		if (!sstr.empty() && delim != sstr)
		{
			result.emplace_back(sstr);
		}
		str.erase(0, pos + delim.length());
	}
	if (!str.empty())
		result.emplace_back(str);
	return result;
}

TokenOpt Lexer::identifyToken(const std::string& lexeme, const Rules& rules)
{
	if (lexeme.empty())
	{
		return std::nullopt;
	}

	std::regex pattern;
	for (const auto& rule : rules)
	{
		pattern = rule.second;
		if (std::regex_match(lexeme, pattern))
		{
			Token token;
			token.kind = rule.first;
			switch (token.kind)
			{
				case TokenKind::Number:
				{
					token.value = std::stod(lexeme);
					break;
				}
				case TokenKind::Fraction:
				{
					token.value = std::stod(lexeme);
					break;
				}
				case TokenKind::Add:
				case TokenKind::Sub:
				case TokenKind::Mul:
				case TokenKind::Assign:
					break;
				case TokenKind::Unknown:
				{
					token.value = std::stod(split(lexeme, "^")[1]);
				}
			}
			return token;
		}
	}
	return std::nullopt;
}

std::ostream& operator<<(std::ostream &o, const TokenKind& token)
{
	std::unordered_map<TokenKind, std::string> um =
	{
		{TokenKind::Number, "Number"},
		{TokenKind::Add, "Add"},
		{TokenKind::Sub, "Sub"},
		{TokenKind::Mul, "Mul"},
		{TokenKind::Assign, "Assign"},
		{TokenKind::Unknown, "Unknown"},
		{TokenKind::Fraction, "Fraction"},
	};
	o << um[token];
	return o;
}

std::ostream& operator<<(std::ostream &o, const TokenOpt& token)
{
	if (token)
		o << token->kind << " " << token->value;
	return o;
}
