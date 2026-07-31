/*
    =====================================================
    LARGEST ODD NUMBER IN A STRING
    =====================================================

    Problem: Given a string num representing a large integer, return the
    largest-valued odd number that is a non-empty substring of num.
    If no odd number exists, return an empty string "".

    Note: A substring is a contiguous sequence of characters within a string.

    Example:
    Input: num = "52"
    Output: "5"

    Input: num = "4206"
    Output: ""
    Explanation: No odd digits exist, so no odd substring possible.

    Input: num = "35427"
    Output: "35427"
    Explanation: "35427" itself is odd (ends in 7).

    =====================================================
    INTUITION:
    =====================================================

    Key Property: A number is ODD if and only if its LAST DIGIT is odd.

    So we need the largest substring that ends with an odd digit.

    How to maximize the value?
    - A number gets larger when it has MORE digits (with same leading digits)
    - "354" > "35" > "3" — longer prefix = larger value
    - So we want to keep as many leading digits as possible

    Strategy: Find the RIGHTMOST odd digit in the string.
    - Everything from index 0 to that odd digit forms the largest odd number
    - Why rightmost? Because including more digits from the left makes
      the number larger

    =====================================================
    APPROACH:
    =====================================================
    1. Traverse the string from RIGHT to LEFT
    2. Find the first (rightmost) odd digit
    3. Return substring from index 0 to that position (inclusive)
    4. If no odd digit found, return ""

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: num = "4528"

    i=3: num[3] = '8' → 8 is even → skip
    i=2: num[2] = '2' → 2 is even → skip
    i=1: num[1] = '5' → 5 is odd → return num.slice(0, 2) = "45"

    Output: "45" ✓

    =====================================================
    EXAMPLE DRY RUN 3 (no odd number):
    =====================================================
    Input: num = "4206"

    All digits even → loop ends, return ""

    =====================================================
    TIME COMPLEXITY:  O(n) - Single reverse pass
    SPACE COMPLEXITY: O(1) - Only using variables (excluding output)
    =====================================================
*/

// In C++ we did `num[i] - '0'` to convert a char digit to its numeric value.
// In JavaScript, `num[i]` is a single-character string, so we use Number(num[i])
// (or the unary + operator) to convert it to a number.
function largestOddNumber(num) {
  for (let i = num.length - 1; i >= 0; i--) {
    if (Number(num[i]) % 2 !== 0) {
      return num.slice(0, i + 1);
    }
  }

  return "";
}

console.log(largestOddNumber("52")); // "5"
console.log(largestOddNumber("4206")); // ""
console.log(largestOddNumber("35427")); // "35427"
