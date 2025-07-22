#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

PmergeMe::PmergeMe(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        std::istringstream iss(arg);
        int value;
        if (!(iss >> value) || value < 0 || !iss.eof()) {
            throw std::runtime_error("Error");
        }
        _vec.push_back(value);
        _deq.push_back(value);
    }
}

PmergeMe::~PmergeMe() {}

void PmergeMe::printOriginal() const {
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); ++i) {
        std::cout << " " << _vec[i];
    }
    std::cout << std::endl;
}

void PmergeMe::sortAndPrint() {
    std::vector<int> vecSorted = fordJohnsonVector(_vec);
    std::deque<int> deqSorted = fordJohnsonDeque(_deq);
    std::cout << "After:";
    for (size_t i = 0; i < vecSorted.size(); ++i) {
        std::cout << " " << vecSorted[i];
    }
    std::cout << std::endl;
}

void PmergeMe::sortAndTime() {
    std::vector<int> vecSorted;
    std::deque<int> deqSorted;
    clock_t start, end;
    double vecTime, deqTime;

    start = clock();
    vecSorted = fordJohnsonVector(_vec);
    end = clock();
    vecTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    start = clock();
    deqSorted = fordJohnsonDeque(_deq);
    end = clock();
    deqTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << deqTime << " us" << std::endl;
}

const std::vector<int>& PmergeMe::getVector() const { return _vec; }
const std::deque<int>& PmergeMe::getDeque() const { return _deq; }

// Génère la suite de Jacobsthal jusqu'à n (exclu)
static std::vector<size_t> jacobsthalSequence(size_t n) {
    std::vector<size_t> seq;
    if (n == 0) return seq;
    seq.push_back(1); // J(1)
    size_t j1 = 1, j2 = 0;
    while (seq.size() < n) {
        size_t next = j1 + 2 * j2;
        if (next > n) break;
        seq.push_back(next);
        j2 = j1;
        j1 = next;
    }
    // Compléter avec les indices manquants
    for (size_t i = 1; i <= n; ++i) {
        if (std::find(seq.begin(), seq.end(), i) == seq.end())
            seq.push_back(i);
    }
    return seq;
}

std::vector<int> PmergeMe::fordJohnsonVector(const std::vector<int>& input) {
    if (input.size() <= 1)
        return input;
    std::vector<int> main_chain;
    std::vector<int> pending;
    size_t i = 0;
    for (; i + 1 < input.size(); i += 2) {
        int a = input[i];
        int b = input[i + 1];
        if (a < b) {
            pending.push_back(a);
            main_chain.push_back(b);
        } else {
            pending.push_back(b);
            main_chain.push_back(a);
        }
    }
    int last = -1;
    bool has_last = false;
    if (i < input.size()) {
        last = input[i];
        has_last = true;
    }
    main_chain = fordJohnsonVector(main_chain);
    std::vector<size_t> jacob = jacobsthalSequence(pending.size());
    std::vector<bool> inserted(pending.size(), false);
    for (size_t k = 0; k < jacob.size(); ++k) {
        size_t idx = jacob[k] - 1;
        if (idx >= pending.size() || inserted[idx]) continue;
        int value = pending[idx];
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
        main_chain.insert(pos, value);
        inserted[idx] = true;
    }
    if (has_last) {
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), last);
        main_chain.insert(pos, last);
    }
    return main_chain;
}

std::deque<int> PmergeMe::fordJohnsonDeque(const std::deque<int>& input) {
    if (input.size() <= 1)
        return input;
    std::deque<int> main_chain;
    std::deque<int> pending;
    size_t i = 0;
    for (; i + 1 < input.size(); i += 2) {
        int a = input[i];
        int b = input[i + 1];
        if (a < b) {
            pending.push_back(a);
            main_chain.push_back(b);
        } else {
            pending.push_back(b);
            main_chain.push_back(a);
        }
    }
    int last = -1;
    bool has_last = false;
    if (i < input.size()) {
        last = input[i];
        has_last = true;
    }
    main_chain = fordJohnsonDeque(main_chain);
    std::vector<size_t> jacob = jacobsthalSequence(pending.size());
    std::vector<bool> inserted(pending.size(), false);
    for (size_t k = 0; k < jacob.size(); ++k) {
        size_t idx = jacob[k] - 1;
        if (idx >= pending.size() || inserted[idx]) continue;
        int value = pending[idx];
        std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value);
        main_chain.insert(pos, value);
        inserted[idx] = true;
    }
    if (has_last) {
        std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), last);
        main_chain.insert(pos, last);
    }
    return main_chain;
} 