/*
    =====================================================
    CHECK IF TWO STRINGS ARE ANAGRAMS OF EACH OTHER
    =====================================================

    Problem: Given two strings s and t, return true if t is an anagram 
    of s, and false otherwise. An anagram is a word formed by rearranging 
    the letters of another word, using all the original letters exactly once.

    Example:
    Input: s = "anagram", t = "nagaram"
    Output: true

    Input: s = "rat", t = "car"
    Output: false

    Input: s = "listen", t = "silent"
    Output: true

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
    we can use a fixed-size array of 26 instead of a hashmap.

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
    EXAMPLE DRY RUN:
    =====================================================
    Input: s = "anagram", t = "nagaram"
    freq[26] = {0, 0, ..., 0}

    i=0: s='a' → freq[0]++  = 1,   t='n' → freq[13]-- = -1
    i=1: s='n' → freq[13]++ = 0,   t='a' → freq[0]--  = 0
    i=2: s='a' → freq[0]++  = 1,   t='g' → freq[6]--  = -1
    i=3: s='g' → freq[6]++  = 0,   t='a' → freq[0]--  = 0
    i=4: s='r' → freq[17]++ = 1,   t='r' → freq[17]-- = 0
    i=5: s='a' → freq[0]++  = 1,   t='a' → freq[0]--  = 0
    i=6: s='m' → freq[12]++ = 1,   t='m' → freq[12]-- = 0

    All freq entries are 0 → return true ✓

    =====================================================
    EXAMPLE DRY RUN 2 (false case):
    =====================================================
    Input: s = "rat", t = "car"
    freq[26] = {0, 0, ..., 0}

    i=0: s='r' → freq[17]++ = 1,   t='c' → freq[2]--  = -1
    i=1: s='a' → freq[0]++  = 1,   t='a' → freq[0]--  = 0
    i=2: s='t' → freq[19]++ = 1,   t='r' → freq[17]-- = 0

    Check: freq[2] = -1, freq[19] = 1 → NOT all zeros
    return false ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through both strings
    SPACE COMPLEXITY: O(1) - Fixed array of size 26
    =====================================================
*/

#include <iostream>
#include <string>
using namespace std;

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;
    
    int freq[26] = {0};
    
    for (int i = 0; i < s.length(); i++) {
        freq[s[i] - 'a']++;
        freq[t[i] - 'a']--;
    }
    
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) return false;
    }
    
    return true;
}
