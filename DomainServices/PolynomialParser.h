#pragma once

#include <string>

class Polynomial;

class PolynomialParser
{
public:
    static Polynomial parse(const std::string& expr);
};
