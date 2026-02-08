/*
    =====================================================
    LONGEST COMMON PREFIX
    =====================================================

    Problem: Given an array of strings, find the longest common prefix 
    string amongst them. If there is no common prefix, return "".

    Example:
    Input: strs = ["flower", "flow", "flight"]
    Output: "fl"

    Input: strs = ["dog", "racecar", "car"]
    Output: ""
    Explanation: No common prefix among the input strings.

    Input: strs = ["interspecies", "interstellar", "interstate"]
    Output: "inters"

    =====================================================
    INTUITION:
    =====================================================
    
    The common prefix can be at most as long as the SHORTEST string.
    
    Approach: Use the FIRST string as a reference and compare it 
    character-by-character with ALL other strings.

    For each character position in the first string:
    - Check if that character matches at the same position in every 
      other string
    - If ANY string doesn't match (or is too short) → stop
    - If all match → this character is part of the common prefix

    Why compare with first string?
    - The common prefix must be a prefix of EVERY string, including 
      the first one
    - So we just need to check how far the first string matches 
      with all others

    =====================================================
    APPROACH:
    =====================================================
    1. Edge case: If array is empty, return ""
    2. For each index i in the first string:
       a. Get character c = strs[0][i]
       b. For every other string j (from 1 to n-1):
          - If i >= strs[j].length() → string j is too short, stop
          - If strs[j][i] != c → mismatch found, stop
       c. If all strings matched at position i, continue
    3. Return the prefix found so far

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: strs = ["flower", "flow", "flight"]
    Reference string: "flower"

    i=0, c='f':
        "flow"[0] = 'f' ✓
        "flight"[0] = 'f' ✓
        All match → prefix so far: "f"

    i=1, c='l':
        "flow"[1] = 'l' ✓
        "flight"[1] = 'l' ✓
        All match → prefix so far: "fl"

    i=2, c='o':
        "flow"[2] = 'o' ✓
        "flight"[2] = 'i' ✗ → MISMATCH! Stop.

    Return: "fl" ✓

    =====================================================
    EXAMPLE DRY RUN 2:
    =====================================================
    Input: strs = ["dog", "racecar", "car"]
    Reference string: "dog"

    i=0, c='d':
        "racecar"[0] = 'r' ✗ → MISMATCH at first character! Stop.

    Return: "" ✓

    =====================================================
    TIME COMPLEXITY:  O(S) - where S = sum of all characters in all strings
                      (worst case we compare every character)
    SPACE COMPLEXITY: O(1) - Only using variables (excluding output)
    =====================================================
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string longestCommonPrefix(vector<string>& strs) {
    // Edge case: If array is empty, return ""
    if (strs.empty()) return "";
    
    // Compare each character of the first string with all other strings
    for (int i = 0; i < strs[0].length(); i++) {
        char c = strs[0][i];
        
        // Check this character against all other strings
        for (int j = 1; j < strs.size(); j++) {
            // If current string is too short OR character doesn't match
            if (i >= strs[j].length() || strs[j][i] != c) {
                return strs[0].substr(0, i);
            }
        }
    }
    
    // If we get here, the entire first string is the common prefix
    return strs[0];
}
