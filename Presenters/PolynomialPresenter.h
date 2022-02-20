#pragma once

#include "Presenter.h"
#include "../Domain/Polynomial.h"

class Polynomial;

class PolynomialPresenter : public Presenter
{
public:
    explicit PolynomialPresenter(Polynomial polynomial);

    virtual void present() const = 0;
    ~PolynomialPresenter() override = default;

private:
    Polynomial _polynomial;
};

