// William Romine
// 00103649
// Dr. Lewis CS372

//Used https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/ for some help in understanding formatting for prefix and postfix

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int precedence(char c);

int main() {
    string infix;
    cout << "Type a fully parenthsized expression:" << endl;
    cin >> infix;

    stack<char> postfix;
    cout << "That evaluates to:" << endl;
    string output;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];
        if (isalpha(c)) {
            output += c;
        } else if (c == '(') {
            postfix.push(c);
        } else if (c == ')') {
            while (!postfix.empty() && postfix.top() != '(') {
                output += postfix.top();
                postfix.pop();
            }
            if (!postfix.empty() && postfix.top() == '(') {
                postfix.pop();
            } else {
                cerr << "Mismatched parentheses" << endl;
                return 1;
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!postfix.empty() && precedence(c) <= precedence(postfix.top())) {
                output += postfix.top();
                postfix.pop();
            }
            postfix.push(c);
        } else {
            cerr << "Invalid character: " << c << endl;
            return 1;
        }
    }

    while (!postfix.empty()) {
        if (postfix.top() == '(') {
            cerr << "Mismatched parentheses" << endl;
            return 1;
        }
        output += postfix.top();
        postfix.pop();
    }

    cout << "Postfix notation: " << output << endl;

    return 0;
}

int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
