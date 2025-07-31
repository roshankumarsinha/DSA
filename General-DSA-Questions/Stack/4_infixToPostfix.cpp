// Write a function to convert an infix expression to postfix in C++.

// Infix notation (human-friendly):
// A + B * C
// Here, we need to respect operator precedence (i.e., * comes before +), which makes it hard to evaluate directly.

// Postfix notation (machine-friendly):
// A B C * +
// No need for parentheses or precedence rules — it can be evaluated left to right using a stack.

// Operator precedence:
// 1. ^ (highest) -> 3
// 2. * and / -> 2
// 3. + and - (lowest) -> 1
// 4. rest -> -1


// 🔧 Algorithm
// 1. Initialize:
//    a.  An empty stack for operators.
//    b.  An empty string for output.
// 2. Scan the infix expression left to right:
//    a.  Operand (A-Z or 0–9): Add to output.
//    b.  Left Parenthesis (: Push to stack.
//    c.  Right Parenthesis ):
//      c1. Pop from stack to output until you find (.
//      c2. Discard (.
//    d.  Operator +, -, *, /, ^:
//      d1. While the stack is not empty, and the top of stack is an operator with greater or equal precedence, pop it to output.
//      d2. Push current operator to stack.
// 3. After processing the expression:
//    a.  Pop remaining operators from stack to output.


#include <iostream>
#include <stack>
#include <string>
using namespace std;

int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string s) {
    stack<char> st;
    string res; // Store the result

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];  // Current character in the expression

        // If the scanned character is
        // an operand, add it to the output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            res += c;

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (c == '(')
            st.push('(');

        // If the scanned character is an ‘)’,
        // pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (st.top() != '(') {
                res += st.top();
                st.pop();
            }
            st.pop(); // Pop the '(' from the stack
        }

        // If an operator is scanned
        else {
            while (!st.empty() && prec(c) <= prec(st.top())) {  // While the stack is not empty and the top of the stack has greater or equal precedence, pop it to output
                res += st.top();
                st.pop();
            }
            st.push(c); // Push the current operator to the stack
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }

    return res;
}

int main() {
    string exp = "a+b*(c^d-e)^(f+g*h)-i";
    cout << infixToPostfix(exp);
    return 0;
}

