// Given a string s consisting only of characters 'a', 'b', 'c'.
// Find the number of substrings that contain at least one occurrence of all of 'a', 'b', 'c'.

// Notes link : https://takeuforward.org/data-structure/number-of-substring-containing-all-three-characters

// Intuition:
// Use the sliding window technique. Maintain a window that contains at least one of each of
// 'a', 'b', 'c'. Whenever the window is valid, every substring that starts at 'left' and ends at
// any index from 'right' to the end of the string is also valid. That count is (s.length - right).
// Then shrink from the left and keep counting.

// Approach:
// 1. Two pointers left and right for the window.
// 2. An array of size 3 counts 'a', 'b', 'c' (index 0, 1, 2).
// 3. Expand with right; while the window has all three chars, add (s.length - right) and shrink.

// Example: "abcabc" → 10.

// JavaScript note: index a/b/c with charCodeAt(i) - 'a'.charCodeAt(0), giving 0, 1, 2.
function numberOfSubstrings(s) {
  const charCount = [0, 0, 0]; // counts of 'a', 'b', 'c'
  const aCode = "a".charCodeAt(0);
  let left = 0;
  let count = 0;

  for (let right = 0; right < s.length; right++) {
    charCount[s.charCodeAt(right) - aCode]++;

    // While the window contains at least one of each character
    while (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
      // Every substring starting at 'left' and ending at index >= right is valid
      count += s.length - right;

      // Shrink the window from the left
      charCount[s.charCodeAt(left) - aCode]--;
      left++;
    }
  }

  return count;
}

console.log("Number of substrings containing 'a', 'b', and 'c':", numberOfSubstrings("abcabc")); // 10

// Time Complexity: O(n). Space Complexity: O(1).
