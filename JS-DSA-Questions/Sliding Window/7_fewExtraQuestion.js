// Longest Substring with At Most K Distinct Characters
// Given a string s and an integer k, return the length of the longest substring of s that
// contains at most k distinct characters.

// Notes link : https://takeuforward.org/data-structure/longest-substring-with-at-most-k-distinct-characters

// Intuition:
// Use the sliding window technique. Maintain a window with at most k distinct characters.
// If the number of distinct characters exceeds k, shrink from the left until it's <= k again.
// Track the maximum window length.

// Approach:
// 1. Two pointers left and right.
// 2. A map counts character frequencies in the window; distinctCount tracks distinct chars.
// 3. Expand with right: if a char's freq becomes 1, it's new → distinctCount++.
//    While distinctCount > k, shrink from left (when a char's freq hits 0, distinctCount--).
// 4. Update maxLength with (right - left + 1).

// JavaScript note: C++ used a fixed vector<int>(256, 0). Here a Map keyed by character is the
// idiomatic choice and works for any charset (not just ASCII).
function lengthOfLongestSubstringKDistinct(s, k) {
  const charCount = new Map();
  let left = 0;
  let distinctCount = 0;
  let maxLength = 0;

  for (let right = 0; right < s.length; right++) {
    const currentChar = s[right];
    charCount.set(currentChar, (charCount.get(currentChar) || 0) + 1);

    // New distinct character
    if (charCount.get(currentChar) === 1) {
      distinctCount++;
    }

    // Shrink while too many distinct characters
    while (distinctCount > k) {
      const leftChar = s[left];
      charCount.set(leftChar, charCount.get(leftChar) - 1);
      if (charCount.get(leftChar) === 0) {
        distinctCount--;
      }
      left++;
    }

    maxLength = Math.max(maxLength, right - left + 1);
  }

  return maxLength;
}

console.log(lengthOfLongestSubstringKDistinct("eceba", 2)); // 3 ("ece")

// Subarray with k different integers
// Given an array nums and an integer k, return the number of good subarrays.
// A good array has EXACTLY k distinct integers.

// Notes link : https://takeuforward.org/data-structure/subarray-with-k-different-integers

// Intuition:
// count(exactly k distinct) = count(at most k distinct) - count(at most k-1 distinct).
// Every subarray with exactly k distinct integers is counted in "at most k" but not "at most k-1".

function subarraysWithAtMostKDistinct(nums, k) {
  if (k < 0) return 0;
  const freq = new Map();
  let left = 0;
  let distinct = 0;
  let count = 0;

  for (let right = 0; right < nums.length; right++) {
    freq.set(nums[right], (freq.get(nums[right]) || 0) + 1);
    if (freq.get(nums[right]) === 1) distinct++;

    while (distinct > k) {
      freq.set(nums[left], freq.get(nums[left]) - 1);
      if (freq.get(nums[left]) === 0) distinct--;
      left++;
    }

    // All subarrays ending at 'right' within the window are valid
    count += right - left + 1;
  }

  return count;
}

function subarraysWithKDistinct(nums, k) {
  return (
    subarraysWithAtMostKDistinct(nums, k) -
    subarraysWithAtMostKDistinct(nums, k - 1)
  );
}

console.log(subarraysWithKDistinct([1, 2, 1, 2, 3], 2)); // 7
