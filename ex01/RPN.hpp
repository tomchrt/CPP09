#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
public:
    RPN();
    ~RPN();
    int evaluate(const std::string& expr);
};

#endif // RPN_HPP 