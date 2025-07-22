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
    void sortAndPrint();
    void sortAndTime(); // nouvelle méthode pour trier et chronométrer
    const std::vector<int>& getVector() const;
    const std::deque<int>& getDeque() const;

private:
    std::vector<int> _vec;
    std::deque<int> _deq;
    std::vector<int> fordJohnsonVector(const std::vector<int>& input);
    std::deque<int> fordJohnsonDeque(const std::deque<int>& input);
};

#endif // PMERGEME_HPP 