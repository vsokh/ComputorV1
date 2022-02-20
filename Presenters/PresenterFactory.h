#pragma once
#include <memory>
#include "Presenter.h"

class Polynomial;
struct Solution;

class PresenterFactory final
{
public:
    static std::unique_ptr<Presenter> createPresenter(const Solution& solution);
    static std::unique_ptr<Presenter> createPresenter(const Polynomial& polynomial);
};
