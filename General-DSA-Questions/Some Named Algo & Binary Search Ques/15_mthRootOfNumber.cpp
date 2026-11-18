// Given two numbers N and M, find the Nth root of M. The nth root of a number M is defined as a number X when raised to the power N equals M.
// If the 'nth root is not an integer, return -1.

// Intiution:
// 1. Find a range/scale in which our answer lies.
// 2. For Nth root of M, the answer lies between 1 to M. So, our answer definitely lies in this range.
// 3. Now, we need to find maximum value of X such that X^N <= M.
// 4. Brute force approach would be to iterate from 1 to M and check for each number if its Nth power is equal to M. This would take O(M) time.
// 5. We can optimize this using binary search on the range 1 to M.

// Notes link : https://takeuforward.org/data-structure/nth-root-of-a-number-using-binary-search

// Approach:
// 1. Initialize two pointers, left = 1 and right = M.
// 2. While left <= right:
//    a. Calculate mid = left + (right - left) / 2.
//    b. Calculate mid^N using a helper function to avoid overflow.
//    c. If mid^N == M, return mid.
//    d. If mid^N < M, move the left pointer to mid + 1.
//    e. If mid^N > M, move the right pointer to mid - 1.
// 3. If no integer root is found, return -1.


#include <iostream>
using namespace std;

long long power(int mid, int n, int m) {
    long long result = 1;
    for (int i = 0; i < n; i++) {
        result *= mid;
        if (result > m) return result; // Early exit if result exceeds m
    }
    return result;
}

int nthRoot(int n, int m) {
    int left = 1;
    int right = m;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long midPowerN = power(mid, n, m);

        if (midPowerN == m) {
            return mid; // Found the Nth root
        } else if (midPowerN < m) {
            left = mid + 1; // Move to the right half
        } else {
            right = mid - 1; // Move to the left half
        }
    }

    return -1; // Nth root not found
}

int main() {
    int n = 3; // Example: Find the 3rd root
    int m = 27; // Example: of 27
    int result = nthRoot(n, m);
    if (result != -1) {
        cout << "The " << n << "th root of " << m << " is: " << result << endl;
    } else {
        cout << "The " << n << "th root of " << m << " is not an integer." << endl;
    }
    return 0;
}

// For these type of problems we need to find a range/scale in which our answer lies and then perform binary search on that range to find the optimal answer.
// Before applying binary search, think of brute force which is linear search on the answer space, and then optimize it using binary search.