#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange(const std::string& dbFile);
    BitcoinExchange(const BitcoinExchange& other);
    ~BitcoinExchange();
    
    BitcoinExchange& operator=(const BitcoinExchange& other);

    void loadDatabase(const std::string& dbFile);

    float getRateForDate(const std::string& date) const;

private:
    std::map<std::string, float> _rates;
};

#endif 