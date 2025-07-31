// Given an array arr[] of size n, for each element arr[i], find the next greater element to the right.
// If no such element exists, return -1.

// Notes : https://takeuforward.org/data-structure/next-greater-element-using-stack/

// Intuition: (Use Monotonic Decreasing Stack : top of stack has the smallest of the larger elements seen so far)
// 1. You process from right to left so that you’ve already seen future values.
// 2. You use the stack to hold possible candidates for the next greater element.
// 3. You pop smaller elements because they’re useless for future elements.
//    a. The main intuition behind popping them is that these elements can never be the NGE for any element present at the left of A[i] because A[i] is greater than these elements.
// 4. The top of the stack is always the next greater element for the current element.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElements(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);  // Initialize result with -1
    stack<int> s;

    for (int i = n - 1; i >= 0; --i) {
        // Pop all elements smaller than or equal to current
        while (!s.empty() && s.top() <= arr[i]) {
            s.pop();
        }

        if (!s.empty()) { // If stack is not empty, the top element is the next greater element
            result[i] = s.top();
        }

        s.push(arr[i]); // Push the current element onto the stack
    }

    return result;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> res = nextGreaterElements(arr);

    cout << "Next Greater Elements:\n";
    for (int val : res) {
        cout << val << " ";
    }

    return 0;
}


// Time Complexity: O(n) - Each element is pushed and popped from the stack at most once.
// Space Complexity: O(n) - The stack can hold up to n elements in the worst case.