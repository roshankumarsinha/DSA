// Given a string s, find the length of the longest substring without repeating characters.

// Notes link : https://takeuforward.org/data-structure/length-of-longest-substring-without-any-repeating-character

// Example 1:
// Input: s = "cadbzabcd"
// Output: 5

// Intuition:
// Generally, sliding window technique is used to solve such problems related to substrings or subarrays.
// 1. We can use a sliding window approach to solve this problem efficiently.
// 2. We maintain a window defined by two pointers, left and right, which represent the current substring without repeating characters.
// 3. We use a hash map to keep track of the characters in the current window and their latest indices.

// Approach:
// 1. Initialize two pointers, left and right, to the start of the string.
// 2. Use a hash map of 256 size (for all ASCII characters) to store the last index of each character.
// 3. Initialize the hash map with -1 index to indicate that no characters have been seen yet.
// 4. Initialize a variable maxLength to keep track of the maximum length of substring found so far.
// 5. Iterate through the string using the right pointer:
//    a. If the character at the right pointer has been seen before and its last index is greater than or equal to left, it means we have a repeating character.
//       In this case, move the left pointer to the index right after the last occurrence of the current character.
//    b. Update the last index of the current character in the hash map to the current right index.
//    c. Calculate the length of the current substring (right - left + 1) and update maxLength if it's greater than the current maxLength.
// 6. Return maxLength after iterating through the string.

// Explanation with example "cadbzabcd":
// - Start with left = 0, right = 0, maxLength = 0
// - Read 'c': No repeat, maxLength = 1 (substring "c"), [hashMap['c'] = 0]
// - Read 'a': No repeat, maxLength = 2 (substring "ca"), [hashMap['c'] = 0, hashMap['a'] = 1]
// - Read 'd': No repeat, maxLength = 3 (substring "cad"), [hashMap['c'] = 0, hashMap['a'] = 1, hashMap['d'] = 2]
// - Read 'b': No repeat, maxLength = 4 (substring "cadb"), [hashMap['c'] = 0, hashMap['a'] = 1, hashMap['d'] = 2, hashMap['b'] = 3]
// - Read 'z': No repeat, maxLength = 5 (substring "cadbz"), [hashMap['c'] = 0, hashMap['a'] = 1, hashMap['d'] = 2, hashMap['b'] = 3, hashMap['z'] = 4]
// - Read 'a': Repeat found at index 1 which is >= left (0), move left to index 2, maxLength remains 5 (substring "dbza"), [hashMap['c'] = 0, hashMap['a'] = 5, hashMap['d'] = 2, hashMap['b'] = 3, hashMap['z'] = 4]
// - Read 'b': Repeat found at index 3 which is >= left (2), move left to index 4, maxLength remains 5 (substring "zab"), [hashMap['c'] = 0, hashMap['a'] = 5, hashMap['d'] = 2, hashMap['b'] = 6, hashMap['z'] = 4]
// - Read 'c': Repeat found at index 0 which is < left (4), no need to move left, maxLength remains 5 (substring "zabc"), [hashMap['c'] = 7, hashMap['a'] = 5, hashMap['d'] = 2, hashMap['b'] = 6, hashMap['z'] = 4]
// - Read 'd': Repeat found at index 2 which is < left (4), no need to move left, maxLength remains 5 (substring "zabcd"), [hashMap['c'] = 7, hashMap['a'] = 5, hashMap['d'] = 8, hashMap['b'] = 6, hashMap['z'] = 4]
// - End of string, return maxLength = 5.


#include <iostream>
#include <string>
#include <vector>
using namespace std;

int lengthOfLongestSubstring(string s) {
    vector<int> charIndex(256, -1); // Hash map to store the last index of each character
    int left = 0; // Left pointer of the sliding window
    int maxLength = 0; // Maximum length of substring found

    // Expand the window with the right pointer
    for (int right = 0; right < s.length(); right++) {
        char currentChar = s[right];

        // If the character has been seen and is within the current window
        if (charIndex[currentChar] >= left) {   // charIndex[currentChar] is working fine because currentChar is of type char which gets implicitly converted to its ASCII integer value.
            left = charIndex[currentChar] + 1; // Move left pointer to the right of the last occurrence
        }

        charIndex[currentChar] = right; // Update the last index of the current character
        maxLength = max(maxLength, right - left + 1); // Update maxLength if needed
    }

    return maxLength;
}

int main() {
    string s = "cadbzabcd";
    cout << "Length of Longest Substring Without Repeating Characters: " << lengthOfLongestSubstring(s) << "\n";
    return 0;
}

// Time Complexity: O(n) - Each character is processed at most twice (once by the right pointer and once by the left pointer).
// Space Complexity: O(1) - The hash map size is fixed (256 for ASCII characters).