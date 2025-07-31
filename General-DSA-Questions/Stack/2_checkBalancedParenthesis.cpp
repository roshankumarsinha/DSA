// Write a function to check if the parentheses in a string are balanced in C++.

// Notes : https://takeuforward.org/data-structure/check-for-balanced-parentheses/

// String can contain '(', ')', '{', '}', '[' and ']'
// String is balanced if every opening bracket has a corresponding closing bracket in the correct order.

// Approach:
// 1. Use a stack to keep track of opening brackets.
// 2. For each character in the string:
//    - If it's an opening bracket ('(', '{', '['), push it onto the stack.
//    - If it's a closing bracket (')', '}', ']'), check if the stack is not empty and if the top of the stack matches the corresponding opening bracket.
//      If it does, pop the stack; otherwise, return false.
// 3. After processing all characters, if the stack is empty, return true (indicating the string is balanced); otherwise, return false.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isValid(string s) {
        stack<char>st; 
        for(auto it: s) {
            if(it=='(' || it=='{' || it == '[') st.push(it); 
            else {
                if(st.size() == 0) return false; 
                char ch = st.top(); 
                st.pop(); 
                if((it == ')' and ch == '(') or  (it == ']' and ch == '[') or (it == '}' and ch == '{')) continue;
                else return false;
            }
        }
        return st.empty(); 
    }
int main()
{
    string s="()[{}()]";
    if(isValid(s))
    cout<<"True"<<endl;
    else
    cout<<"False"<<endl;
}