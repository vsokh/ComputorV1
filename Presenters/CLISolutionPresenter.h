#pragma once

#include "Presenter.h"
#include "../Domain/Solution.h"

class CLISolutionPresenter : public Presenter
{
public:
    explicit CLISolutionPresenter(Solution solution);

    void present() const override;

private:
    Solution _solution;
};