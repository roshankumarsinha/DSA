/*
    =====================================================
    CHECK IF TWO STRINGS ARE ANAGRAMS OF EACH OTHER
    =====================================================

    Problem: Given two strings s and t, return true if t is an anagram
    of s, and false otherwise. An anagram is a word formed by rearranging
    the letters of another word, using all the original letters exactly once.

    Example:
    Input: s = "anagram", t = "nagaram" → true
    Input: s = "rat", t = "car"         → false
    Input: s = "listen", t = "silent"   → true

    =====================================================
    INTUITION:
    =====================================================

    Two strings are anagrams if they have the SAME characters with
    the SAME frequencies, just in different order.

    Approach 1: SORTING
    - Sort both strings → if they're anagrams, sorted versions are identical
    - Simple but O(n log n)

    Approach 2: FREQUENCY COUNTING (Optimal)
    - Count frequency of each character in s (increment)
    - Count frequency of each character in t (decrement)
    - If all counts are 0 → anagram!

    Since we only deal with lowercase English letters (26 chars),
    we can use a fixed-size array of 26 instead of a map.

    =====================================================
    APPROACH (Frequency Array):
    =====================================================
    1. If lengths differ → return false
    2. Create frequency array of size 26 (for 'a' to 'z')
    3. For each index i:
       a. Increment freq[s[i] - 'a']
       b. Decrement freq[t[i] - 'a']
    4. If all entries in freq are 0 → return true
    5. Otherwise → return false

    Why single pass works?
    - Incrementing for s and decrementing for t in the same loop
    - If characters match perfectly, every increment gets canceled
      by a corresponding decrement → all zeros

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through both strings
    SPACE COMPLEXITY: O(1) - Fixed array of size 26
    =====================================================
*/

// In C++ we did `s[i] - 'a'` to turn a lowercase letter into an index 0..25.
// In JavaScript there is no char type, so we use charCodeAt(0) to get the ASCII/UTF-16 code
// and subtract the code of 'a' (97). `new Array(26).fill(0)` creates the zero-filled counts.
function isAnagram(s, t) {
  if (s.length !== t.length) return false;

  const freq = new Array(26).fill(0);
  const aCode = "a".charCodeAt(0);

  for (let i = 0; i < s.length; i++) {
    freq[s.charCodeAt(i) - aCode]++;
    freq[t.charCodeAt(i) - aCode]--;
  }

  for (let i = 0; i < 26; i++) {
    if (freq[i] !== 0) return false;
  }

  return true;
}

console.log(isAnagram("anagram", "nagaram")); // true
console.log(isAnagram("rat", "car")); // false
console.log(isAnagram("listen", "silent")); // true
