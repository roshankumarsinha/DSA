// Write a function for Kadane's algorithm that finds the maximum sum of a subarray in an array of integers.

// Example:
// Input: arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4}
// Output: 6
// Explanation: The subarray [4, -1, 2, 1] has the largest sum = 6.

// Video link : https://www.youtube.com/watch?v=9IZYqostl2M&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=10

// Basically, the algorithm keeps track of the current sum of the subarray and the maximum sum of the subarray.
// If the current sum is less than 0, then we reset the current sum to 0.
// If the current sum is greater than the maximum sum, then we update the maximum sum.

// +ve + +ve = +ve
// Big(+ve) + Small(-ve) = +ve
// Big(-ve) + Small(+ve) = -ve.  So, we reset the current sum to 0.

// 🧠 Intuition and Approach:
// Kadane's Algorithm works on the idea of dynamic programming, but in a greedy way — at each step,
// we decide whether to continue the current subarray or start a new one.

// 🔁 Step-by-Step Process:
// Initialize:
//  1.  maxSum = -Infinity → holds the result.
//  2.  currentSum = 0 → tracks the sum of the current subarray.
// Traverse the array:
//  1.  For each element x, do:
//      a.  currentSum += x → add current number to the running subarray sum.
//      b.  Update maxSum = max(maxSum, currentSum).
//      c.  If currentSum < 0, it won't help future subarrays, so reset it to 0.
// Return maxSum.

// 🔎 Why Reset currentSum When It's Negative?
// A negative running sum can't contribute to a larger sum in future, so we discard it and start fresh.

// JavaScript note: C++ used INT_MIN as the initial maximum. In JS the equivalent is
// Number.NEGATIVE_INFINITY (also writable as -Infinity), since JS numbers are floating point.
function kadane(nums) {
  let currentSum = 0;
  let maxSum = -Infinity;
  for (let i = 0; i < nums.length; i++) {
    currentSum = currentSum + nums[i];
    maxSum = Math.max(maxSum, currentSum);
    if (currentSum < 0) {
      currentSum = 0;
    }
  }
  return maxSum;
}

console.log(kadane([-2, 1, -3, 4, -1, 2, 1, -5, 4])); // 6
