// You are given a binary array nums (containing only 0s and 1s) and an integer goal.
// Return the number of non-empty subarrays of nums that sum to goal. A subarray is a contiguous part of the array.

// Notes link : https://takeuforward.org/data-structure/binary-subarray-with-sum

// Intuition:
// We can use the sliding window technique to solve this problem efficiently.
// The idea is to maintain two sliding windows to count the number of subarrays with sum equal to goal.
// One window will count the number of subarrays with sum less than or equal to goal,
// and the other window will count the number of subarrays with sum less than or equal to goal - 1.
// The difference between the sizes of these two windows will give us the number of subarrays with sum equal to goal.
// Example let's say we need to find goal = 4, then we will find the number of subarrays with sum <= 4 and the number of subarrays with sum <= 3.
// The difference between these two counts will give us the number of subarrays with sum exactly equal to 4.

// Why we can't directly count subarrays with sum equal to goal?
// Counting subarrays with sum equal to a specific value directly can be complex because it requires keeping track of multiple potential starting points for subarrays.
// By counting subarrays with sums less than or equal to goal and goal - 1, we can leverage the properties of cumulative sums and the sliding window technique to simplify the problem.
// This approach allows us to efficiently calculate the desired count without explicitly enumerating all possible subarrays.
// Sliding window technique only works for monotonic conditions like <= or >=, not for exact equality.
// Example: sum ≤ k is monotonic.
// • If sum becomes too big, moving left pointer always decreases sum
// • If sum is valid, expanding right keeps increasing sum predictably
// But sum == goal is NOT monotonic.

// Approach:
// 1. Create a helper function countSubarraysWithSumAtMostGoal that takes the binary array nums and an integer goal as
//    input and returns the count of subarrays with sum less than or equal to goal.
// 2. In this helper function, initialize two pointers, left and right, to represent the current window.
// 3. Initialize a variable currentSum to keep track of the sum of the current window.
// 4. Initialize a variable count to keep track of the number of subarrays with sum less than or equal to goal.
// 5. Iterate through the array using the right pointer: (Expand the window by moving the right pointer)
//    a. Add the element at the right pointer to currentSum.
//    b. If currentSum exceeds goal, shrink the window from the left by moving the left pointer until currentSum is less than or equal to goal.
//       i. Subtract the element at the left pointer from currentSum.
//       ii. Move the left pointer to the right.
//    c. The number of subarrays ending at 'right' with sum less than or equal to goal is (right - left + 1), which is the size of the current valid window.
//       Add this to count.
// 6. Return count after iterating through the array.
// 7. In the main function numSubarraysWithSum, call the helper function twice:
//    a. First with goal to get the count of subarrays with sum less than or equal to goal.
//    b. Second with goal - 1 to get the count of subarrays with sum less than or equal to goal - 1.
// 8. The difference between these two counts will give the number of subarrays with sum exactly equal to goal.
// 9. Return this difference.

// Explanation with example nums = [1,0,1,0,1], goal = 2:
// - First, we call countSubarraysWithSumAtMostGoal with goal = 2
//   - Start with left = 0, right = 0, currentSum = 0, count = 0
//   - Read '1': left = 0, right = 0, currentSum = 1, 1 <= 2, count = 0 + (0 - 0 + 1) = 1
//   - Read '0': left = 0, right = 1, currentSum = 1, 1 <= 2, count = 1 + (1 - 0 + 1) = 3
//   - Read '1': left = 0, right = 2, currentSum = 2, 2 <= 2, count = 3 + (2 - 0 + 1) = 6
//   - Read '0': left = 0, right = 3, currentSum = 2, 2 <= 2, count = 6 + (3 - 0 + 1) = 10
//   - Read '1': left = 0, right = 4, currentSum = 3, 3 > 2, shrink window
//     - Remove '1' at index 0: left = 1, currentSum = 2, 2 <= 2, count = 10 + (4 - 1 + 1) = 14
// - Total count of subarrays with sum <= 2 is 14
// - Next, we call countSubarraysWithSumAtMostGoal with goal = 1
//   - Start with left = 0, right = 0, currentSum = 0, count = 0
//   - Read '1': left = 0, right = 0, currentSum = 1, 1 <= 1, count = 0 + (0 - 0 + 1) = 1
//   - Read '0': left = 0, right = 1, currentSum = 1, 1 <= 1, count = 1 + (1 - 0 + 1) = 3
//   - Read '1': left = 0, right = 2, currentSum = 2, 2 > 1, shrink window
//     - Remove '1' at index 0: left = 1, currentSum = 1, 1 <= 1, count = 3 + (2 - 1 + 1) = 5
//   - Read '0': left = 1, right = 3, currentSum = 1, 1 <= 1, count = 5 + (3 - 1 + 1) = 8
//   - Read '1': left = 1, right = 4, currentSum = 2, 2 > 1, shrink window
//     - Remove '0' at index 1: left = 2, currentSum = 2, 2 > 1, shrink window
//     - Remove '1' at index 2: left = 3, currentSum = 1, 1 <= 1, count = 8 + (4 - 3 + 1) = 10
// - Total count of subarrays with sum <= 1 is 10
// - Finally, the number of subarrays with sum exactly equal to 2 is 14 - 10 = 4.

#include <iostream>
#include <vector>
using namespace std;

int countSubarraysWithSumAtMostGoal(const vector<int>& nums, int goal) {
    // Handle edge case where goal is negative
    // This edge case can occur when we have goal 0, but next time we call with goal - 1 which is -1.
    // Since array contains only 0s and 1s, no subarray can have negative sum.
    if (goal < 0) return 0;     // No subarrays possible with negative sum

    int left = 0;   // Left pointer of the sliding window
    int currentSum = 0; // Current sum of the window
    int count = 0;  // Count of subarrays with sum <= goal

    for (int right = 0; right < nums.size(); right++) {
        currentSum = currentSum + nums[right];  // Expand the window by adding the right element

        // Shrink the window from the left if the current sum exceeds the goal
        // We keep moving left pointer to right until currentSum <= goal
        while (currentSum > goal && left <= right) {
            currentSum = currentSum - nums[left];   // Remove the left element from current sum
            left++;                                 // Move the left pointer to the right
        }

        // All subarrays ending at 'right' with sum <= goal
        // The number of such subarrays is length of the current window, because
        // any subarray that starts from index 'left' to 'right' will have sum <= goal
        count = count + (right - left + 1); // right - left + 1 is the size of the current valid window
    }

    return count;
}

int numSubarraysWithSum(vector<int>& nums, int goal) {
    // Count of subarrays with sum exactly equal to goal, which is equal to
    // count of subarrays with sum <= goal - count of subarrays with sum <= goal - 1
    return countSubarraysWithSumAtMostGoal(nums, goal) - countSubarraysWithSumAtMostGoal(nums, goal - 1);
}

int main() {
    vector<int> nums = {1, 0, 1, 0, 1};
    int goal = 2;

    int result = numSubarraysWithSum(nums, goal);
    cout << "Number of subarrays with sum equal to " << goal << " is: " << result << endl;

    return 0;
}


// Time Complexity: O(N), where N is the number of elements in the input array nums. Each element is processed at most twice (once by the right pointer and once by the left pointer).
// Space Complexity: O(1), as we are using only a constant amount of extra space



/*
    =====================================================
    COUNT NUMBER OF NICE SUBARRAYS
    =====================================================

    Problem: Given an array of integers nums and an integer k.
    A subarray is called "nice" if there are exactly k odd numbers in it.
    Return the number of nice sub-arrays.

    Notes link: https://takeuforward.org/data-structure/count-number-of-nice-subarrays

    Example:
    Input: nums = [1, 1, 2, 1, 1], k = 3
    Output: 2
    Explanation: Subarrays with 3 odd numbers are:
    - [1, 1, 2, 1] (indices 0-3)
    - [1, 2, 1, 1] (indices 1-4)

    =====================================================
    INTUITION:
    =====================================================
    
    Key Insight: This problem is IDENTICAL to "Binary Subarray with Sum"!
    
    Transform the problem:
    - Odd number  → 1 (counts as 1)
    - Even number → 0 (counts as 0)
    
    After transformation:
    - Sum of subarray = Count of odd numbers in subarray
    - Finding subarrays with k odd numbers = Finding subarrays with sum = k
    
    Example: [1, 1, 2, 1, 1] with k = 3
    Transform: [1, 1, 0, 1, 1] (odd→1, even→0)
    Now find subarrays with sum = 3 ✓

    =====================================================
    APPROACH:
    =====================================================
    1. Use the same sliding window technique as Binary Subarray with Sum
    2. Instead of using actual array values, use:
       - 1 if nums[i] is odd (nums[i] % 2 == 1)
       - 0 if nums[i] is even (nums[i] % 2 == 0)
    3. Apply: count(sum ≤ k) - count(sum ≤ k-1) = count(sum == k)
    
    Optimization: We don't need to actually transform the array!
    Just use (nums[i] % 2) which gives 1 for odd and 0 for even.

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: nums = [1, 1, 2, 1, 1], k = 3
    
    Transform to binary: [1, 1, 0, 1, 1]
    
    Step 1: Count subarrays with at most 3 ones (≤ 3)
    
    right=0: [1], sum=1, count = 0 + 1 = 1
    right=1: [1,1], sum=2, count = 1 + 2 = 3
    right=2: [1,1,0], sum=2, count = 3 + 3 = 6
    right=3: [1,1,0,1], sum=3, count = 6 + 4 = 10
    right=4: [1,1,0,1,1], sum=4 > 3, shrink left
             [1,0,1,1], sum=3, count = 10 + 4 = 14
    
    Total ≤ 3: 14
    
    Step 2: Count subarrays with at most 2 ones (≤ 2)
    
    right=0: [1], sum=1, count = 0 + 1 = 1
    right=1: [1,1], sum=2, count = 1 + 2 = 3
    right=2: [1,1,0], sum=2, count = 3 + 3 = 6
    right=3: [1,1,0,1], sum=3 > 2, shrink left
             [1,0,1], sum=2, count = 6 + 3 = 9
    right=4: [1,0,1,1], sum=3 > 2, shrink left
             [0,1,1], sum=2, count = 9 + 3 = 12
    
    Total ≤ 2: 12
    
    Result: 14 - 12 = 2 ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Each element processed at most twice
    SPACE COMPLEXITY: O(1) - Only using variables
    =====================================================
*/

int countSubarraysWithAtMostKOdd(const vector<int>& nums, int k) {
    if (k < 0) return 0;  // No subarrays with negative count of odd numbers
    
    int left = 0;
    int oddCount = 0;  // Count of odd numbers in current window
    int count = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        // Add contribution of right element (1 if odd, 0 if even)
        oddCount += nums[right] % 2;    // We can also write oddCount = oddCount + (nums[right] % 2)
        
        // Shrink window while oddCount exceeds k
        while (oddCount > k && left <= right) {
            oddCount -= nums[left] % 2;
            left++;
        }
        
        // All subarrays ending at 'right' with at most k odd numbers
        count += (right - left + 1);
    }
    
    return count;
}

int numberOfNiceSubarrays(vector<int>& nums, int k) {
    // Subarrays with exactly k odd = (at most k odd) - (at most k-1 odd)
    return countSubarraysWithAtMostKOdd(nums, k) - countSubarraysWithAtMostKOdd(nums, k - 1);
}