#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
public:
    PmergeMe(int argc, char* argv[]);
    ~PmergeMe();

    void printOriginal() const;
    const std::vector<int>& getVector() const;
    const std::deque<int>& getDeque() const;

private:
    std::vector<int> _vec;
    std::deque<int> _deq;
};

#endif // PMERGEME_HPP 