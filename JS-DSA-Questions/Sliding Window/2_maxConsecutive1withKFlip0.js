// Given a binary array (only 0s and 1s) nums and an integer k, return the maximum number of
// consecutive 1's in the array if you can flip at most k 0's.

// Notes link : https://takeuforward.org/data-structure/max-consecutive-ones-iii

// Intuition:
// This is equivalent to finding the longest subarray with at most k zeros.
// Use the sliding window technique: if the number of zeros in the current window exceeds k,
// shrink the window from the left until we have at most k zeros again.
// At each step, update the maximum length of the window that contains at most k zeros.

// Approach:
// 1. Two pointers left and right for the current window.
// 2. zeroCount tracks zeros in the window; maxLength tracks the best window size.
// 3. Expand with right:
//    a. If nums[right] is 0, increment zeroCount.
//    b. While zeroCount > k, shrink from left (decrement zeroCount when removing a 0).
//    c. Update maxLength with (right - left + 1).
// 4. Return maxLength.

// Example: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2 → answer 7.

function longestOnes(nums, k) {
  let left = 0; // Left pointer of the sliding window
  let zeroCount = 0; // Count of zeros in the current window
  let maxLength = 0; // Maximum length of the window found

  for (let right = 0; right < nums.length; right++) {
    // If the current element is 0, increment the zeroCount
    if (nums[right] === 0) {
      zeroCount++;
    }

    // If zeroCount exceeds k, shrink the window from the left
    while (zeroCount > k) {
      if (nums[left] === 0) {
        zeroCount--; // Removing a 0 from the window
      }
      left++; // Move the left pointer to the right
    }

    // Update maxLength with the current window size
    maxLength = Math.max(maxLength, right - left + 1);
  }

  return maxLength;
}

const nums = [1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0];
const k = 2;
console.log(`Maximum consecutive 1's after flipping at most ${k} 0's:`, longestOnes(nums, k)); // 7
