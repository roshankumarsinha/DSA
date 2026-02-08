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
    i=1: num[1] = '5' → 5 is odd → return num.substr(0, 2) = "45"

    Output: "45" ✓

    =====================================================
    EXAMPLE DRY RUN 2:
    =====================================================
    Input: num = "35427"

    i=4: num[4] = '7' → 7 is odd → return num.substr(0, 5) = "35427"

    Output: "35427" ✓ (found at first check itself)

    =====================================================
    EXAMPLE DRY RUN 3 (no odd number):
    =====================================================
    Input: num = "4206"

    i=3: num[3] = '6' → even → skip
    i=2: num[2] = '0' → even → skip
    i=1: num[1] = '2' → even → skip
    i=0: num[0] = '4' → even → skip

    Loop ends, no odd digit found → return ""

    Output: "" ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Single reverse pass
    SPACE COMPLEXITY: O(1) - Only using variables (excluding output)
    =====================================================
*/

#include <iostream>
#include <string>
using namespace std;

string largestOddNumber(string num) {
    string result = "";
    for (int i = num.length() - 1; i >= 0; i--) {
        if ((num[i] - '0') % 2 != 0) {
            return num.substr(0, i + 1);
        }
    }
    
    return "";
}
