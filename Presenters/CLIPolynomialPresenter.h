#pragma once

#include "Presenter.h"
#include "../Domain/Polynomial.h"

class CLIPolynomialPresenter : public Presenter
{
public:
    explicit CLIPolynomialPresenter(Polynomial polynomial);

    void present() const override;

private:
    void presentPolynomialEquation() const;
    void presentPolynomialDegree() const;

private:
    Polynomial _polynomial;
};
