#pragma once

#include <vector>

struct Term {
    double coef;
    double degree;
};

using Terms = std::vector<Term>;

struct Expression {
    Terms terms;
};
