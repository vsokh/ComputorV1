#include "Exceptions.hpp"

Exception::Exception(std::string msg)
    : _msg(std::move(msg))
{
}

const char* Exception::what() const noexcept
{
    return _msg.c_str();
}

InvalidTerm::InvalidTerm(std::string term)
    : Exception{"Invalid term: " + std::move(term)}
{
}

InvalidExpression::InvalidExpression(std::string expression)
    : Exception{"Invalid expression: " + std::move(expression)}
{
}
