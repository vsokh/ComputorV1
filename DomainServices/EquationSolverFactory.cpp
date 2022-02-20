#include "EquationSolverFactory.h"

#include "EquationSolverFor0DegreePolynomial.h"
#include "EquationSolverFor1DegreePolynomial.h"
#include "EquationSolverFor2DegreePolynomial.h"

std::unique_ptr<EquationSolver> EquationSolverFactory::create(Polynomial polynomial)
{
    const auto& degree = polynomial.getDegree();
    switch (degree)
    {
        case 0: {
            return std::make_unique<EquationSolverFor0DegreePolynomial>(std::move(polynomial));
        }
        case 1: {
            return std::make_unique<EquationSolverFor1DegreePolynomial>(std::move(polynomial));
        }
        case 2: {
            return std::make_unique<EquationSolverFor2DegreePolynomial>(std::move(polynomial));
        }
    }
    throw std::logic_error("The polynomial degree is strictly greater than 2, I can't solve.");
    return nullptr;
}
