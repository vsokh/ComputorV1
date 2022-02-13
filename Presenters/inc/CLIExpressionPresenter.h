#pragma once

#include "ExpressionPresenter.h"

class CLIExpressionPresenter : public ExpressionPresenter
{
public:
    void present(const Expression& expression) const override;
};
