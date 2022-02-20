#pragma once

#include <memory>

#include "EquationSolver.h"

class Polynomial;

class EquationSolverFactory final
{
public:
    static std::unique_ptr<EquationSolver> create(Polynomial polynomial);
};