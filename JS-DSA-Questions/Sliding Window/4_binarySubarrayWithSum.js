// You are given a binary array nums (only 0s and 1s) and an integer goal.
// Return the number of non-empty subarrays of nums that sum to goal.

// Notes link : https://takeuforward.org/data-structure/binary-subarray-with-sum

// Intuition:
// Use the sliding window technique with a helper that counts subarrays with sum <= goal.
// Then: count(sum == goal) = count(sum <= goal) - count(sum <= goal - 1).
//
// Why not count sum == goal directly? The sliding window only works for MONOTONIC conditions
// like <= or >= (as the window grows, the sum grows predictably). Exact equality is not
// monotonic, so we express it as a difference of two "at most" counts.

// Approach (helper countSubarraysWithSumAtMostGoal):
// 1. Two pointers left and right; currentSum tracks the window sum; count accumulates results.
// 2. Expand with right, adding nums[right].
// 3. While currentSum > goal, shrink from the left.
// 4. Every subarray ending at 'right' within the window is valid: add (right - left + 1).

function countSubarraysWithSumAtMostGoal(nums, goal) {
  // Edge case: goal can be -1 when called with goal - 1 for goal = 0.
  // Since the array is 0s and 1s, no subarray can have negative sum.
  if (goal < 0) return 0;

  let left = 0;
  let currentSum = 0;
  let count = 0;

  for (let right = 0; right < nums.length; right++) {
    currentSum += nums[right]; // Expand the window

    // Shrink from the left while the sum exceeds the goal
    while (currentSum > goal && left <= right) {
      currentSum -= nums[left];
      left++;
    }

    // Number of subarrays ending at 'right' with sum <= goal = window size
    count += right - left + 1;
  }

  return count;
}

function numSubarraysWithSum(nums, goal) {
  return (
    countSubarraysWithSumAtMostGoal(nums, goal) -
    countSubarraysWithSumAtMostGoal(nums, goal - 1)
  );
}

console.log("Number of subarrays with sum equal to 2:", numSubarraysWithSum([1, 0, 1, 0, 1], 2)); // 4

// Time Complexity: O(N). Space Complexity: O(1).

/*
    =====================================================
    COUNT NUMBER OF NICE SUBARRAYS
    =====================================================

    Problem: A subarray is "nice" if it has exactly k odd numbers. Return the count of nice subarrays.
    Notes link: https://takeuforward.org/data-structure/count-number-of-nice-subarrays

    Example:
    Input: nums = [1, 1, 2, 1, 1], k = 3 → Output: 2

    Key Insight: This is IDENTICAL to "Binary Subarray with Sum"!
    Transform: odd number → 1, even number → 0. Then count of odds in a subarray = its sum,
    so "subarrays with k odd numbers" = "subarrays with sum = k".

    Optimization: we don't actually transform the array — just use (nums[i] % 2), which is 1 for
    odd and 0 for even. (In JS, be careful: negative odd numbers give -1 for %, but these
    problems use non-negative inputs, so nums[i] % 2 is 0 or 1.)
*/

function countSubarraysWithAtMostKOdd(nums, k) {
  if (k < 0) return 0;

  let left = 0;
  let oddCount = 0; // Count of odd numbers in the current window
  let count = 0;

  for (let right = 0; right < nums.length; right++) {
    oddCount += nums[right] % 2; // 1 if odd, 0 if even

    while (oddCount > k && left <= right) {
      oddCount -= nums[left] % 2;
      left++;
    }

    count += right - left + 1;
  }

  return count;
}

function numberOfNiceSubarrays(nums, k) {
  return (
    countSubarraysWithAtMostKOdd(nums, k) -
    countSubarraysWithAtMostKOdd(nums, k - 1)
  );
}

console.log("Number of nice subarrays:", numberOfNiceSubarrays([1, 1, 2, 1, 1], 3)); // 2
