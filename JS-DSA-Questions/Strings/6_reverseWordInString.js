/*
    =====================================================
    REVERSE WORDS IN A STRING
    =====================================================

    Problem: Given an input string s, reverse the order of the words.
    A word is defined as a sequence of non-space characters. The words
    in s are separated by at least one space. Return a string with words
    in reverse order, separated by a single space (no leading/trailing
    spaces, no extra spaces between words).

    Example:
    Input: s = "the sky is blue"   → "blue is sky the"
    Input: s = "  hello world  "   → "world hello"
    Input: s = "a good   example"  → "example good a"

    =====================================================
    INTUITION:
    =====================================================

    Approach 1: EXTRACT WORDS + BUILD IN REVERSE
    - Extract each word, store them, then build result from last to first
    - Clean and straightforward

    Approach 2: REVERSE ENTIRE STRING + REVERSE EACH WORD
    - Reverse the whole string → words are in correct order but each is reversed
    - Then reverse each individual word to fix them, cleaning up extra spaces

    Example walkthrough (Approach 2):
    "the sky is blue"
    → Reverse entire: "eulb si yks eht"
    → Reverse each word: "blue is sky the" ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Both approaches traverse string linearly
    SPACE COMPLEXITY: O(n) - For storing words / result string
    =====================================================
*/

// Approach 1: Extract words and build in reverse order.
// This mirrors the C++ manual two-pointer word extraction. In JavaScript strings are
// immutable, so we collect words into an array and then join them.
function reverseWords(s) {
  const words = [];
  const n = s.length;
  let i = 0;

  // Extract words, skipping spaces
  while (i < n) {
    // Skip spaces
    while (i < n && s[i] === " ") i++;

    if (i >= n) break;

    // Find end of word
    const start = i;
    while (i < n && s[i] !== " ") i++;

    // Extract word and store
    words.push(s.slice(start, i));
  }

  // Build result in reverse order
  let result = "";
  for (let j = words.length - 1; j >= 0; j--) {
    result += words[j];
    if (j > 0) result += " ";
  }

  return result;
}

// Approach 2 (Idiomatic JavaScript): trim, split on one-or-more spaces, reverse, join.
// The regex /\s+/ matches one or more whitespace characters, so multiple spaces between
// words are handled automatically.
function reverseWordsRegex(s) {
  return s.trim().split(/\s+/).reverse().join(" ");
}

console.log(reverseWords("the sky is blue")); // "blue is sky the"
console.log(reverseWords("  hello world  ")); // "world hello"
console.log(reverseWordsRegex("a good   example")); // "example good a"
