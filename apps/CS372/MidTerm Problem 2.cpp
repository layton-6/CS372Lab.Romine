// William Romine
// 00103649
// Dr. Lewis CS372

#include <iostream>
#include <stack>

int main() {
    std::stack<char> numParentheses;
    std::string input;
    std::cout << "What is your statement with parentheses: ";
    std::cin >> input;

    for (char count : input) {
        if (count == '(') {
            numParentheses.push(count);
        } else if (count == ')') {
            if (numParentheses.empty()) {
                std::cout << "Your statement does not have matching parentheses." << std::endl;
                return 0;
            } else {
                numParentheses.pop();
            }
        }
    }
    if (numParentheses.empty()) {
        std::cout << "Your statement has matching parentheses." << std::endl;
    } else {
        std::cout << "Your statement does not have matching parentheses." << std::endl;
    }

    return 0;
}

