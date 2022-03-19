#pragma once

#include <iostream>

namespace Utils
{

template<typename Sequence, typename Predicate>
void cleanSequence(Sequence &seq, const Predicate &pred)
{
    seq.erase(std::remove_if(seq.begin(), seq.end(), pred), seq.end());
}

template<typename Sequence, typename Predicate>
decltype(auto) splitSequence(Sequence seq, const Predicate& pred)
{
    std::vector<Sequence> result;
    do {
        auto it = std::find_if(seq.begin() + 1, seq.end(), pred);
        result.emplace_back(Sequence{seq.begin(), it});

        seq.erase(seq.begin(), it);
    } while (!seq.empty());
    return result;
}

} // Utils