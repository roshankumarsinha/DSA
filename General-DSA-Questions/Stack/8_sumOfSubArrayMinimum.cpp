// Given an array of integers arr, return the sum of the minimum value of all subarrays of arr.
// Since the answer can be large, return the result modulo 10^9 + 7.

// Notes link : https://takeuforward.org/data-structure/sum-of-subarray-minimums
// Video link : https://www.youtube.com/watch?v=v0e8p9JCgRc

// Example :
// Input: [3, 1, 2, 4]
// Output: 17

// All subarrays and their minimums:
// [3] => 3  
// [3,1] => 1  
// [3,1,2] => 1  
// [3,1,2,4] => 1  
// [1] => 1  
// [1,2] => 1  
// [1,2,4] => 1  
// [2] => 2  
// [2,4] => 2  
// [4] => 4  

// Sum = 3+1+1+1+1+1+1+2+2+4 = 17

// Intiution:
// Each element contributes to the sum only when it is the minimum of a subarray.
// So instead of computing all subarrays →
// We compute how many subarrays have arr[i] as their minimum.
// If we know:
//    How many subarrays start before or at i,
//    And how many subarrays end after or at i,
//    Then their product gives us the total number of subarrays where arr[i] is the minimum.

// For every index i, we find:
//    PLE[i]: index of Previous Less Element → closest element to the left that is less than arr[i].
//    NLE[i]: index of Next Less Element → closest element to the right that is strictly less than arr[i].

// Any subarray that has:
//    its left boundary between PLE[i] + 1 and i,
//    its right boundary between i and NLE[i] - 1, will have arr[i] as its minimum element.

// So, the number of such subarrays is:
//    leftCount = i - PLE[i]
//    rightCount = NLE[i] - i
//    totalSubarraysWithArrIAsMin = leftCount * rightCount

// Therefore, the contribution of arr[i] is:
// arr[i] * leftCount * rightCount


// Why totalSubarraysWithArrIAsMin = leftCount * rightCount?
// Now, think about pairing the subarrays that end at i with the subarrays that start at i.
// ->  Each subarray that ends at i with arr[i] as the minimum (from the left side) can be combined with each subarray that starts at i with arr[i] as the minimum (from the right side).
// ->  The key point here is that each subarray ending at i and having arr[i] as the minimum can be paired with each subarray starting at i and having arr[i] as the minimum.
//     This results in a "rectangular" relationship between subarrays from the left side and the right side.
// For example, if there are left ways to pick subarrays that end at i and right ways to pick subarrays that start at i, then there are left × right subarrays that both include arr[i] as the minimum.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MOD = 1e9 + 7;

int sumSubarrayMins(vector<int>& arr) {
    int n = arr.size();
    vector<int> ple(n), nle(n); // Previous Less Element and Next Less Element
    // ple[i] will store the index of the previous less element for arr[i]
    // nle[i] will store the index of the next less element for arr[i]
    // If no such element exists, ple[i] will be -1 and nle[i] will be n (size of the array)
    stack<int> s;

    // Previous Less Element (PLE)
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && arr[s.top()] > arr[i]) { // Pop elements that are greater than the current element
            s.pop();
        }
        // -1 is used because, If no smaller element exists, that means all subarrays starting from index 0 up to i can have arr[i] as the minimum
        ple[i] = s.empty() ? -1 : s.top();  // If stack is empty, ple[i] is -1, otherwise it is the index of the previous less element
        // Push current index onto the stack
        s.push(i);
    }

    // Clear the stack to reuse
    while (!s.empty()) s.pop();

    // Next Less Element (NLE)
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {  // Pop elements that are greater than or equal to the current element
            s.pop();
        }
        // n is used because, If no smaller element exists, that means all subarrays ending from index i to n-1 can have arr[i] as the minimum
        nle[i] = s.empty() ? n : s.top(); // If stack is empty, nle[i] is n, otherwise it is the index of the next less element
        s.push(i);
    }

    // Calculate total sum
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        long long left = i - ple[i];
        long long right = nle[i] - i;
        sum = sum + (arr[i] * left * right) % MOD; // Calculate contribution of arr[i]
        sum %= MOD; // Take modulo to avoid overflow
    }

    return (int)sum;
}

int main() {
    vector<int> arr = {3, 1, 2, 4};
    cout << "Sum of Subarray Minimums: " << sumSubarrayMins(arr) << "\n";
    return 0;
}
// Time Complexity: O(n) - Each element is pushed and popped from the stack at most once.
// Space Complexity: O(n) - We use two arrays for PLE and NLE, and a stack for processing.




