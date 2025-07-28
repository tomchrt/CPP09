#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    ~RPN();
    
    RPN& operator=(const RPN& other);
    
    int evaluate(const std::string& expr);
};

#endif 