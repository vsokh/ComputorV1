#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    explicit Exception(std::string msg);
    const char* what() const noexcept override;

protected:
    std::string _msg;
};

class InvalidTerm : public Exception {
public:
    explicit InvalidTerm(std::string term);
};

class InvalidExpression : public Exception {
public:
    explicit InvalidExpression(std::string expression);
};
