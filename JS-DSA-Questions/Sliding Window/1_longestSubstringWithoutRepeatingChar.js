// Given a string s, find the length of the longest substring without repeating characters.

// Notes link : https://takeuforward.org/data-structure/length-of-longest-substring-without-any-repeating-character

// Example 1:
// Input: s = "cadbzabcd"
// Output: 5

// Intuition:
// Generally, the sliding window technique is used to solve such problems related to substrings or subarrays.
// 1. We maintain a window defined by two pointers, left and right, representing the current substring without repeating characters.
// 2. We use a hash map to keep track of the characters in the current window and their latest indices.

// Approach:
// 1. Initialize two pointers, left and right, at the start of the string.
// 2. Use a map to store the last index of each character. Initialize with -1 (nothing seen yet).
// 3. Iterate with the right pointer:
//    a. If the current char was seen before and its last index >= left, move left to lastIndex + 1.
//    b. Update the last index of the current character.
//    c. Update maxLength with (right - left + 1).
// 4. Return maxLength.

// JavaScript note: C++ used a fixed vector<int>(256, -1) indexed by the char's ASCII code.
// In JS we use a Map from character -> last index. `charIndex.get(ch) ?? -1` treats an unseen
// character as -1 (the ?? nullish-coalescing operator handles undefined).
function lengthOfLongestSubstring(s) {
  const charIndex = new Map(); // character -> last index seen
  let left = 0; // Left pointer of the sliding window
  let maxLength = 0; // Maximum length of substring found

  for (let right = 0; right < s.length; right++) {
    const currentChar = s[right];

    // If the character has been seen and is within the current window
    if ((charIndex.get(currentChar) ?? -1) >= left) {
      left = charIndex.get(currentChar) + 1; // Move left past the last occurrence
    }

    charIndex.set(currentChar, right); // Update the last index of the current character
    maxLength = Math.max(maxLength, right - left + 1); // Update maxLength if needed
  }

  return maxLength;
}

console.log("Length of Longest Substring Without Repeating Characters:", lengthOfLongestSubstring("cadbzabcd")); // 5

// Time Complexity: O(n) - Each character is processed at most twice (right and left pointers).
// Space Complexity: O(min(n, charset)) - the map holds at most one entry per distinct character.
