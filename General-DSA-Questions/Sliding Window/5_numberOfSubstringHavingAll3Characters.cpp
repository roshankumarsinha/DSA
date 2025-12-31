// Given a string s , consisting only of characters 'a' , 'b' , 'c'.
// Find the number of substrings that contain at least one occurrence of all these characters 'a' , 'b' , 'c'.

// Notes link : https://takeuforward.org/data-structure/number-of-substring-containing-all-three-characters

// Intuition:
// We can use the sliding window technique to solve this problem efficiently.
// The idea is to maintain a window that contains at least one occurrence of all three characters 'a', 'b', and 'c'.
// We can expand the window by moving the right pointer and shrink the window by moving the left pointer.
// Whenever we find a valid window that contains all three characters, we can count the number of substrings that can be formed with the current window.
// The number of such substrings is equal to the number of ways we can choose the starting point of the substring from the left side of the window.
// Number of substrings will be equal to number of characters remaining on the right side of the window including the right pointer.
// Number of such substrings = (length of the string - right pointer).

// Approach:
// 1. Initialize two pointers, left and right, to represent the current window.
// 2. Use a hash map or an array of size 3 to keep track of the frequency of each character 'a', 'b', and 'c' in the current window.
// 3. Initialize a variable count to keep track of the number of substrings that contain at least one occurrence of all three characters.
// 4. Iterate through the string using the right pointer: (Expand the window by moving the right pointer)
//    a. Update the frequency of the character at the right pointer in the hash map.
//    b. While the current window contains at least one occurrence of all three characters, shrink the window from the left by moving the left pointer and update the frequency map accordingly.
//       i. Calculate the number of substrings that can be formed with the current window and add it to count.
//       ii. Update the frequency of the character at the left pointer in the hash map.
//       iii. Move the left pointer to the right.
// 5. Return count after iterating through the string.

// Explanation with example "abcabc":
// - Start with left = 0, right = 0, count = 0
// - Read 'a': charCount['a'] = 1, window does not contain all three characters
// - Read 'b': charCount['b'] = 1, window does not contain all three characters
// - Read 'c': charCount['c'] = 1, window contains all three characters
//   - Calculate substrings: count = 0 + (6 - 2) = 4 (substrings "abc", "abca", "abcab", "abcabc")
//   - Shrink window from left: charCount['a'] = 0, left = 1
// - Read 'a': charCount['a'] = 1, window contains all three characters
//   - Calculate substrings: count = 4 + (6 - 3) = 7 (substrings "bca", "bcab", "bcabc")
//   - Shrink window from left: charCount['b'] = 0, left = 2
// - Read 'b': charCount['b'] = 1, window contains all three characters
//   - Calculate substrings: count = 7 + (6 - 4) = 9 (substrings "cab", "cabc")
//   - Shrink window from left: charCount['c'] = 0, left = 3
// - Read 'c': charCount['c'] = 1, window contains all three characters
//   - Calculate substrings: count = 9 + (6 - 5) = 10 (substring "abc")
//   - Shrink window from left: charCount['a'] = 0, left = 4
// - End of string, return count = 10.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int numberOfSubstrings(string s) {
    vector<int> charCount(3, 0); // Frequency map for characters 'a', 'b', 'c', index 0 for 'a', 1 for 'b', 2 for 'c', initialized to 0
    int left = 0; // Left pointer of the sliding window
    int count = 0; // Count of substrings containing all three characters

    // Expand the window with the right pointer
    for (int right = 0; right < s.length(); right++) {
        charCount[s[right] - 'a']++; // Update frequency of the current character

        // While the current window contains at least one occurrence of all three characters
        // charCount[0] represents count of 'a'
        // charCount[1] represents count of 'b'
        // charCount[2] represents count of 'c'
        // so, if all three counts are greater than 0, we have at least one occurrence of each character in the current window.
        while (charCount[0] > 0 && charCount[1] > 0 && charCount[2] > 0) {
            // Calculate the number of substrings that can be formed with the current window
            count = count + (s.length() - right); // All substrings starting from left to end of string with current right pointer

            // Shrink the window from the left
            charCount[s[left] - 'a']--; // Update frequency of the character at the left pointer
            left++; // Move the left pointer to the right
        }
    }

    return count; // Return the total count of substrings
}

int main() {
    string s = "abcabc";
    int result = numberOfSubstrings(s);
    cout << "Number of substrings containing all three characters 'a', 'b', and 'c': " << result << endl;
    return 0;
}

// The above approach has a time complexity of O(n) and a space complexity of O(1), where n is the length of the string.
// The algorithm uses a sliding window technique with two pointers and a frequency map to efficiently count the substrings.