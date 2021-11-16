#include <iostream>
#include <exception>

#include "Parser.hpp"
#include "Expression.hpp"
#include "Term.hpp"

using namespace Translator;

class Computor
{
public:
    Computor(const std::string& expression)
        : _expr(Parser{expression}.parse())
    {
    }

private:
    Expression _expr;
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
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}

