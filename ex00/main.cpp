#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cctype>

static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(s[start])) ++start;
    size_t end = s.size();
    while (end > start && std::isspace(s[end - 1])) --end;
    return s.substr(start, end - start);
}

static bool isValidDate(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        return false;
    if (y < 2009 || m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    return true;
}

static bool isValidNumber(const std::string& valueStr, float& value) {
    char* end;
    value = std::strtof(valueStr.c_str(), &end);
    if (*end != '\0')
        return false;
    if (value < 0)
        return false;
    if (value > 1000)
        return false;
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc("data.csv");

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line)) {
        if (line.empty() || trim(line).empty())
            continue;
        size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = trim(line.substr(0, sep));
        std::string valueStr = trim(line.substr(sep + 1));
        float value = 0.0f;
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!isValidNumber(valueStr, value)) {
            if (valueStr.find('-') != std::string::npos || value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else if (value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else
                std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        float rate = btc.getRateForDate(date);
        float result = value * rate;
        std::cout << date << " => " << valueStr << " = " << result << std::endl;
    }
    return 0;
} 