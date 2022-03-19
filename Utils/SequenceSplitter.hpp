#pragma once

#include <vector>

namespace Utils
{

template<typename Sequence, typename Predicate>
class SequenceSplitter
{
public:
    SequenceSplitter(Sequence seq, const Predicate &pred)
            : _pred(std::move(pred)), _seq(std::move(seq)) {}

    decltype(auto) split()
    {
        std::vector<Sequence> result;
        do {
            auto it = std::find_if(_seq.begin() + 1, _seq.end(), _pred);
            result.emplace_back(std::string{_seq.begin(), it});

            _seq.erase(_seq.begin(), it);
        } while (!_seq.empty());
        return result;
    }

private:
    const Predicate &_pred;
    Sequence _seq;
};

} // Utils