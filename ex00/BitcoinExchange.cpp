#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(const std::string& dbFile) {
    loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _rates(other._rates) {
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _rates = other._rates;
    }
    return *this;
}

void BitcoinExchange::loadDatabase(const std::string& dbFile) {
    std::ifstream db(dbFile.c_str());
    if (!db.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }
    std::string line;
    std::getline(db, line);
    while (std::getline(db, line)) {
        std::istringstream iss(line);
        std::string date, rateStr;
        if (!std::getline(iss, date, ',') || !std::getline(iss, rateStr))
            continue;
        float rate = static_cast<float>(std::atof(rateStr.c_str()));
        _rates[date] = rate;
    }
}

float BitcoinExchange::getRateForDate(const std::string& date) const {
    if (_rates.empty())
        return 0.0f;
    std::map<std::string, float>::const_iterator it = _rates.lower_bound(date);
    if (it != _rates.end() && it->first == date)
        return it->second;
    if (it == _rates.begin())
        return 0.0f;
    --it;
    return it->second;
} 