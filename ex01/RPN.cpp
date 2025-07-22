#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <stack>
#include <cctype>

RPN::RPN() {}
RPN::~RPN() {}

int RPN::evaluate(const std::string& expr) {
    std::stack<int> stack;
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token) {
        if (token.size() == 1 && std::isdigit(token[0])) {
            stack.push(token[0] - '0');
        } else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            if (stack.size() < 2)
                throw std::runtime_error("Error");
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int res = 0;
            switch (token[0]) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Error");
                    res = a / b;
                    break;
            }
            stack.push(res);
        } else {
            throw std::runtime_error("Error");
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error");
    return stack.top();
} 