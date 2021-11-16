#include "../inc/Lexer.hpp"
#include "../inc/TokenDefs.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace Translator;

void splitTest()
{
	const std::vector<std::pair<std::string, std::vector<std::string>>> testParams =
	{
		{"5 * X^0 = 0", {"5", "*", "X^0", "=", "0"}},
		{"5", {"5"}},
		{"5          ", {"5"}},
		{"              5", {"5"}},
	};

	for (const auto& param : testParams)
	{
		const auto& tokens = Translator::Lexer{param.first}.split(param.first, " ");
		for (const auto& t : tokens)
			std::cout << t << std::endl;
	}
}

void idenitfyTokenTest()
{
	struct TestData final
	{
		const std::string expression;
		const std::vector<std::pair<std::string, TokenKind>> termsLexemesPairs;
	};
	const std::vector<TestData> testData =
	{
		{"5 * X^0 = 0.1",
		{{"00005", TokenKind::Number},
		{"*", TokenKind::Mul},
		{"X^00000", TokenKind::Unknown},
		{"=", TokenKind::Assign},
		{"00000.1", TokenKind::Fraction}}},
	};
	for (const auto& test : testData)
	{
		for (const auto& pair : test.termsLexemesPairs)
		{
			const auto& token = Lexer(pair.first).identifyToken(pair.first, Lexer::getRules());
			if (token->kind != pair.second)
			{
				std::cout << token << " isn't equal to " << pair.second << std::endl;
			}
		}
	}
}

void nextTokenTest()
{
	std::string str = "5 * X^0 = 0.1";
	Lexer lexer(str);
	while (const auto& tkn = lexer.nextToken())
	{
		std::cout << tkn << std::endl;
	}
}

void regexTest()
{
	{
	const std::regex num("[0-9]+");
	const std::string str = "123";
	std::cout << std::regex_match(str, num) << std::endl;
	}

	{
	const std::regex op("[-*+=]");
	const std::string str = "*";
	std::cout << std::regex_match(str, op) << std::endl;
	}

	{
	const std::regex frac("([0-9]+\\.[0-9]+)");
	const std::string str = "0000005";
	std::cout << std::regex_match(str, frac) << std::endl;
	}

	{
	const std::regex x("X\\^[0-9]+");
	const std::string str = "X^10";
	std::cout << std::regex_match(str, x) << std::endl;
	}
}

int main()
{
	/* splitTest(); */
	nextTokenTest();
	/* idenitfyTokenTest(); */

	return 0;
}
