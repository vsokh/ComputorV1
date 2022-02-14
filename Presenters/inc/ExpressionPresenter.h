#pragma once

struct Expression;
class ExpressionPresenter
{
public:
    virtual void present(const Expression& expression) const = 0;
    virtual ~ExpressionPresenter() = default;
};

