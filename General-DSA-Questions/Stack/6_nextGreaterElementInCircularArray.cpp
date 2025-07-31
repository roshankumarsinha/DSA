// Given a circular array arr[], for each element arr[i], find the next greater element, wrapping around to the beginning if needed.
// If no such element exists, return -1.

// Approach:
// 1. We can use similar logic to the next greater element problem, but we need to handle the circular nature of the array.
// 2. We can simulate the circular array by iterating through the array twice.
// 3. We use modulo (i % n) to wrap around.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextGreaterElementsCircular(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> s; // will store indices

    for (int i = 2 * n - 1; i >= 0; --i) {  // Iterate twice to simulate circular array
        // Calculate the index in the original array
        // i % n gives us the index in the original array
        // This way, we can handle the circular nature of the array
        int idx = i % n;

        // Pop elements <= current one
        while (!s.empty() && nums[s.top()] <= nums[idx]) {
            s.pop();
        }

        if (i < n) { // Only fill result in the first pass
            if (!s.empty()) {
                result[idx] = nums[s.top()];
            }
        }

        s.push(idx); // Always push current index
    }

    return result;
}

int main() {
    vector<int> nums = {1, 2, 1};
    vector<int> result = nextGreaterElementsCircular(nums);

    cout << "Next Greater in Circular Array:\n";
    for (int val : result) {
        cout << val << " ";
    }

    return 0;
}
