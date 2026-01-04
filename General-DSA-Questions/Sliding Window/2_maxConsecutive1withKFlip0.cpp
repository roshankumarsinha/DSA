// Given a binary array(array consisting of only 0s and 1s) nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

// Notes link : https://takeuforward.org/data-structure/max-consecutive-ones-iii

// Intuition:
// Think like if we need to find the longest subarray with at most k zeros.
// We can use the sliding window technique to solve this problem efficiently.
// If the number of zeros in the current window exceeds k, we can shrink the window from the left until we have at most k zeros again.
// At each step, we can update the maximum length of the window that contains at most k zeros.

// Approach:
// 1. Initialize two pointers, left and right, to represent the current window.
// 2. Initialize a variable zeroCount to keep track of the number of zeros in the current window.
// 3. Initialize a variable maxLength to keep track of the maximum length of the window found so far.
// 4. Iterate through the array using the right pointer: (Expand the window by moving the right pointer)
//    a. If the current element is 0, increment the zeroCount.
//    b. If the zeroCount exceeds k, shrink the window from the left by moving the left pointer until the zeroCount is at most k.
//       i. If the element at the left pointer is 0, decrement the zeroCount.
//    c. Calculate the length of the current window (right - left + 1) and update maxLength if it's greater than the current maxLength.
// 5. Return maxLength after iterating through the array.

// Explanation with example nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2:
// - Start with left = 0, right = 0, zeroCount = 0, maxLength = 0
// - Read '1': zeroCount = 0, maxLength = 1 left = 0, right = 0 (subarray [1])
// - Read '1': zeroCount = 0, maxLength = 2 left = 0, right = 1 (subarray [1,1])
// - Read '1': zeroCount = 0, maxLength = 3 left = 0, right = 2 (subarray [1,1,1])
// - Read '0': zeroCount = 1 which is <= k, maxLength = 4 left = 0, right = 3 (subarray [1,1,1,0])
// - Read '0': zeroCount = 2 which is <= k, maxLength = 5 left = 0, right = 4 (subarray [1,1,1,0,0])
// - Read '0': zeroCount = 3 which is > k, shrink window from left until zeroCount <= k
//   - Remove '1' at index 0: zeroCount = 3 left = 1, right = 5 (subarray [1,1,0,0,0])
//   - Remove '1' at index 1: zeroCount = 3 left = 2, right = 5 (subarray [1,0,0,0])
//   - Remove '1' at index 2: zeroCount = 3 left = 3, right = 5 (subarray [0,0,0])
//   - Remove '0' at index 3: zeroCount = 2 left = 4, right = 5 (subarray [0,0]). Now zeroCount <= k
// - maxLength remains 5
// - Read '1': zeroCount = 2 which is <= k, maxLength = 5 left = 4, right = 6 (subarray [0,0,1])
// - Read '1': zeroCount = 2 which is <= k, maxLength = 5 left = 4, right = 7 (subarray [0,0,1,1])
// - Read '1': zeroCount = 2 which is <= k, maxLength = 6 left = 4, right = 8 (subarray [0,0,1,1,1])
// - Read '1': zeroCount = 2 which is <= k, maxLength = 7 left = 4, right = 9 (subarray [0,0,1,1,1,1])
// - Read '0': zeroCount = 3 which is > k, shrink window from left until zeroCount <= k
//   - Remove '0' at index 4: zeroCount = 2 left = 5, right = 10 (subarray [0,1,1,1,1,0]). Now zeroCount <= k
// - maxLength remains 7
// - End of array, return maxLength = 7.


#include <iostream>
#include <vector>
using namespace std;

int longestOnes(vector<int>& nums, int k) {
    int left = 0; // Left pointer of the sliding window
    int zeroCount = 0; // Count of zeros in the current window
    int maxLength = 0; // Maximum length of the window found

    // Expand the window with the right pointer
    for (int right = 0; right < nums.size(); right++) {
        // If the current element is 0, increment the zeroCount
        if (nums[right] == 0) {
            zeroCount++;
        }

        // If zeroCount exceeds k, shrink the window from the left
        while (zeroCount > k) {
            if (nums[left] == 0) {
                zeroCount--; // Decrement zeroCount if we are removing a 0 from the window
            }
            left++; // Move the left pointer to the right
        }

        // Calculate the length of the current window and update maxLength if needed
        maxLength = max(maxLength, right - left + 1);
    }

    return maxLength;
}

int main() {
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    cout << "Maximum number of consecutive 1's after flipping at most " << k << " 0's: " << longestOnes(nums, k) << endl;
    return 0;
}
