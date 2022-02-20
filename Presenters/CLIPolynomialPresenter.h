#pragma once

#include "Presenter.h"
#include "../Domain/Polynomial.h"

class CLIPolynomialPresenter : public Presenter
{
public:
    explicit CLIPolynomialPresenter(Polynomial polynomial);

    void present() const override;

private:
    Polynomial _polynomial;
};
