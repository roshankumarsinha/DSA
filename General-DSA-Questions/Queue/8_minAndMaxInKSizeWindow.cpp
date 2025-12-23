// Find sum of minimum and maximum elements of all subarrays of window size k.
// Given an array of both positive and negative integers, the task is to compute sum of minimum and maximum elements of all sub-array of size k.

// Example:
// Input: arr[] = {2, 5, -1, 7, -3, -1, -2}, k = 3
// Output: 14
// Explanation:
// Subarrays of size 3 are:
// {2, 5, -1} => max = 5, min = -1
// {5, -1, 7} => max = 7, min = -1
// {-1, 7, -3} => max = 7, min = -3
// {7, -3, -1} => max = 7, min = -3
// {-3, -1, -2} => max = -1, min = -3
// Sum of all max and min = (5 + -1) + (7 + -1) + (7 + -3) + (7 + -3) + (-1 + -3) = 14

// Approach:
// 1. We will use two Deques to store the maximum and minimum elements of the current window.
//    a. maxi stores indices of elements in decreasing order — front is max.
//    b. mini stores indices of elements in increasing order — front is min.
// 2. For every window of size k:
//    a. Remove elements which are out of the current window from both Deques.
//    b. Maintain the order in both Deques:
//       - For maxi, pop elements from the back while the current element is greater than the back element.
//       - For mini, pop elements from the back while the current element is less than the back element.
// 3. The front of maxi gives the maximum and the front of mini gives the minimum for the current window.
// 4. Add the sum of these two values to the result.

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int sumMinMaxInKSizeWindow(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return 0; // If array size is less than k, return 0

    deque<int> maxi, mini; // Deques for max and min
    long long sum = 0; // To store the final sum

    // Process the first k elements
    for (int i = 0; i < k; i++) {
        // Maintain the max deque
        while (!maxi.empty() && arr[maxi.back()] <= arr[i]) {
            maxi.pop_back();
        }
        maxi.push_back(i);

        // Maintain the min deque
        while (!mini.empty() && arr[mini.back()] >= arr[i]) {
            mini.pop_back();
        }
        mini.push_back(i);
    }

    // Add the first window's min and max to the sum
    sum += arr[maxi.front()] + arr[mini.front()];

    // Process the rest of the elements
    for (int i = k; i < n; i++) {
        // Remove elements that are out of the current window for max deque
        if (!maxi.empty() && maxi.front() <= i - k) {
            maxi.pop_front();
        }
        // Maintain the max deque
        while (!maxi.empty() && arr[maxi.back()] <= arr[i]) {
            maxi.pop_back();
        }
        maxi.push_back(i);

        // Remove elements that are out of the current window for min deque
        if (!mini.empty() && mini.front() <= i - k) {
            mini.pop_front();
        }
        // Maintain the min deque
        while (!mini.empty() && arr[mini.back()] >= arr[i]) {
            mini.pop_back();
        }
        mini.push_back(i);

        // Add the current window's min and max to the sum
        sum += arr[maxi.front()] + arr[mini.front()];
    }

    return sum; // Return the total sum of min and max elements
}

int main() {
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    int result = sumMinMaxInKSizeWindow(arr, k);
    cout << "Sum of min and max in all subarrays of size " << k << ": " << result << endl;

    return 0;
}
// Time Complexity: O(n) - Each element is pushed and popped from the deques at most once.
// Space Complexity: O(k) - The deques can hold at most k elements at any time.
