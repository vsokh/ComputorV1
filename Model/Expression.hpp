#pragma once

#include <vector>

struct Term {
    double coef;
    double degree;
};

using Expression = std::vector<Term>;
