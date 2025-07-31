// Given an array arr[], for each element, find the closest smaller element to its left (i.e., previous index).
// If no such element exists, return -1.

// Approach:
// 1. It is almost similar to the next greater element problem, but we need to find the previous smaller element.
// 2. We process the array from left to right, since we are looking for previous elements.
// 3. We use a monotonic increasing stack (stack holds candidates in increasing order from bottom to top).
// 4. Rest all approach is similar to the next greater element problem.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> previousSmallerElements(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);  // Initialize result with -1
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        // Remove elements greater than or equal to current
        while (!s.empty() && s.top() >= arr[i]) {
            s.pop();
        }

        if (!s.empty()) {
            result[i] = s.top();
        }

        s.push(arr[i]);
    }

    return result;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> res = previousSmallerElements(arr);

    cout << "Previous Smaller Elements:\n";
    for (int val : res) {
        cout << val << " ";
    }

    return 0;
}
