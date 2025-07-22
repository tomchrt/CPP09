#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try {
        PmergeMe pm(argc, argv);
        pm.printOriginal();
        pm.sortAndPrint();
        pm.sortAndTime();
    } catch (const std::exception& e) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    return 0;
} 