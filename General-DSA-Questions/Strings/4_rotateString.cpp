/*
    =====================================================
    CHECK IF ONE STRING IS ROTATION OF ANOTHER
    =====================================================

    Problem: Given two strings s and goal, return true if goal is a 
    rotation of s, otherwise return false.
    A rotation means shifting characters from the front to the back 
    (or vice versa) any number of times.

    Example:
    Input: s = "abcde", goal = "cdeab"
    Output: true
    Explanation: "abcde" → rotate left by 2 → "cdeab"

    Input: s = "abcde", goal = "abced"
    Output: false

    Input: s = "abcde", goal = "eabcd"
    Output: true
    Explanation: "abcde" → rotate right by 1 → "eabcd"

    =====================================================
    INTUITION:
    =====================================================
    
    Key Trick: If goal is a rotation of s, then goal MUST appear 
    as a SUBSTRING of (s + s).

    Why?
    - Concatenating s with itself produces ALL possible rotations!
    
    Example: s = "abcde"
    s + s = "abcdeabcde"
             -----         → "abcde" (rotation by 0)
              -----        → "bcdea" (rotation by 1)
               -----       → "cdeab" (rotation by 2)
                -----      → "deabc" (rotation by 3)
                 -----     → "eabcd" (rotation by 4)

    Every rotation of s is a contiguous substring of (s + s)!

    So the problem reduces to:
    1. Check if lengths are equal
    2. Check if goal is a substring of (s + s)

    =====================================================
    APPROACH:
    =====================================================
    1. If s.length() != goal.length() → return false
    2. Concatenate: doubled = s + s
    3. Check if goal is a substring of doubled
    4. Return the result

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: s = "abcde", goal = "cdeab"

    Step 1: Lengths equal? 5 == 5 ✓

    Step 2: doubled = "abcde" + "abcde" = "abcdeabcde"

    Step 3: Is "cdeab" in "abcdeabcde"?
            "abcdeabcde"
               ^^^^^
            Found at index 2 ✓

    Output: true ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - string concatenation + substring search
                      (std::string::find uses efficient algorithms)
    SPACE COMPLEXITY: O(n) - For the concatenated string
    =====================================================
*/

#include <iostream>
#include <string>
using namespace std;

bool rotateString(string s, string goal) {
    if (s.length() != goal.length()) return false;
    
    string doubled = s + s;
    // Check if goal is a substring of doubled
    // std::string::find returns the index of the first occurrence or npos if not found
    // We can simply check if it's not npos to determine if it's a substring
    return doubled.find(goal) != string::npos;
}

// In Javascript, we can use the includes() method to check for substring existence:
/*
function rotateString(s, goal) {
    if (s.length !== goal.length) return false;
    const doubled = s + s;
    return doubled.includes(goal);
}
*/