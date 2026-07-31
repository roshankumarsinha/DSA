/*
    =====================================================
    CHECK IF ONE STRING IS ROTATION OF ANOTHER
    =====================================================

    Problem: Given two strings s and goal, return true if goal is a
    rotation of s, otherwise return false.
    A rotation means shifting characters from the front to the back
    (or vice versa) any number of times.

    Example:
    Input: s = "abcde", goal = "cdeab" → true  (rotate left by 2)
    Input: s = "abcde", goal = "abced" → false
    Input: s = "abcde", goal = "eabcd" → true  (rotate right by 1)

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
    1. If s.length != goal.length → return false
    2. Concatenate: doubled = s + s
    3. Check if goal is a substring of doubled
    4. Return the result

    =====================================================
    TIME COMPLEXITY:  O(n) - string concatenation + substring search
    SPACE COMPLEXITY: O(n) - For the concatenated string
    =====================================================
*/

// In C++ we used doubled.find(goal) != string::npos.
// In JavaScript the equivalent is the built-in String.prototype.includes(), which returns
// true/false directly — much cleaner.
function rotateString(s, goal) {
  if (s.length !== goal.length) return false;

  const doubled = s + s;
  return doubled.includes(goal);
}

console.log(rotateString("abcde", "cdeab")); // true
console.log(rotateString("abcde", "abced")); // false
console.log(rotateString("abcde", "eabcd")); // true
