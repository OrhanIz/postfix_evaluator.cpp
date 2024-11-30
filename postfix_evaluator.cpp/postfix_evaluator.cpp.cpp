#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <stdexcept>

// Function to evaluate a postfix expression
double evaluatePostfix(const std::string& expression) {
    std::stack<double> stack;

    // Use stringstream for tokenizing
    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            // Push numeric operands to the stack
            stack.push(std::stod(token));
        }
        else {
            // Pop top two operands for the operator
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression.");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();

            // Perform operations based on the operator
            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Division by zero.");
                stack.push(a / b);
            }
            else {
                throw std::invalid_argument("Invalid operator.");
            }
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression.");
    }

    return stack.top();
}

int main() {
    std::string expression;
    std::cout << "Enter a postfix expression (space-separated): ";
    std::getline(std::cin, expression);

    try {
        double result = evaluatePostfix(expression);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
