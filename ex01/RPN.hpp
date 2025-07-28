#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    ~RPN();
    
    RPN& operator=(const RPN& other);
    
    int evaluate(const std::string& expr);
};

#endif 