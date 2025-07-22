#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange(const std::string& dbFile);
    ~BitcoinExchange();

    // Charge la base de données CSV des taux de change
    void loadDatabase(const std::string& dbFile);

    // Retourne le taux de change pour une date (ou la date précédente la plus proche)
    float getRateForDate(const std::string& date) const;

private:
    std::map<std::string, float> _rates; // date -> taux
};

#endif // BITCOINEXCHANGE_HPP 