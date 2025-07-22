#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

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

const std::vector<int>& PmergeMe::getVector() const { return _vec; }
const std::deque<int>& PmergeMe::getDeque() const { return _deq; } 