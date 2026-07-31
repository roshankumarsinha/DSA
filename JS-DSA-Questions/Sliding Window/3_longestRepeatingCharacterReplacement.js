// Given a string s of only uppercase English letters, you can perform at most k operations.
// In one operation, you can change any character to any other uppercase English character.
// Find the length of the longest substring containing all repeating letters after the operations.

// Notes link : https://takeuforward.org/data-structure/longest-repeating-character-replacement

// Intuition:
// Maintain a window that contains at most k characters that are NOT the most frequent character
// in that window. If (window size - count of most frequent character) exceeds k, shrink from the left.
// Track the maximum valid window length.

// Approach:
// 1. Two pointers left and right for the current window.
// 2. Use an array of size 26 to count character frequencies in the window.
// 3. maxFreqCount tracks the highest single-character frequency seen.
// 4. Expand with right, update counts and maxFreqCount.
//    While (windowSize - maxFreqCount) > k, shrink from the left.
// 5. Update maxLength with (right - left + 1).

// Example: "AAABBCCD", k = 2 → answer 5.

// JavaScript note: C++ used `s[i] - 'A'` to index a size-26 array. Here we compute the index
// with charCodeAt(i) - 'A'.charCodeAt(0). Array(26).fill(0) is the zero-initialized counts.
function characterReplacement(s, k) {
  const charCount = new Array(26).fill(0); // Frequency of A-Z in the window
  const aCode = "A".charCodeAt(0);
  let left = 0; // Left pointer of the sliding window
  let maxFreqCount = 0; // Count of the most frequent character in the window
  let maxLength = 0; // Maximum length of the window found

  for (let right = 0; right < s.length; right++) {
    const idx = s.charCodeAt(right) - aCode;
    charCount[idx]++; // Update frequency of the current character

    // Update maxFreqCount if needed
    maxFreqCount = Math.max(maxFreqCount, charCount[idx]);

    // If the number of characters to replace exceeds k, shrink the window from the left.
    // (window size - maxFreqCount) > k, where window size = right - left + 1.
    while (right - left + 1 - maxFreqCount > k) {
      charCount[s.charCodeAt(left) - aCode]--; // Decrease frequency of the left character
      left++; // Move left pointer to the right

      // Recalculate maxFreqCount for the current window.
      // Note: this recalculation can be skipped for an O(N) solution, because maxLength never
      // shrinks and a smaller maxFreqCount only makes the window grow more slowly — the answer
      // is unaffected. It is kept here to mirror the original explanation.
      maxFreqCount = 0;
      for (const count of charCount) {
        maxFreqCount = Math.max(maxFreqCount, count);
      }
    }

    // Update maxLength
    maxLength = Math.max(maxLength, right - left + 1);
  }

  return maxLength;
}

console.log("Length of Longest Repeating Character Replacement:", characterReplacement("AAABBCCD", 2)); // 5

// Time Complexity: O(N * 26) = O(N). Space Complexity: O(1) (fixed 26-size array).
