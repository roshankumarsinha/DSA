// Given a string s, this string consists of only uppercase English letters. You can perform at most k operations on that string.
// In one operation, you can choose any character of the string and change it to any other uppercase English character.
// Find the length of the longest substring containing all repeating letters you can get after performing the above operations.

// Notes link : https://takeuforward.org/data-structure/longest-repeating-character-replacement

// Intuition:
// We can use the sliding window technique to solve this problem efficiently.
// The idea is to maintain a window that contains at most k characters that are not the most frequent character in that window.
// If the number of characters that need to be replaced (i.e., window size - count of the most frequent character) exceeds k, we shrink the window from the left.
// At each step, we can update the maximum length of the window that contains all repeating letters after performing at most k operations.

// Approach:
// 1. Initialize two pointers, left and right, to represent the current window.
// 2. Use a hash map or an array of size 26 to keep track of the frequency of each character in the current window.
// 3. Initialize a variable maxFreqCount to keep track of the count of the most frequent character in the current window.
// 4. Initialize a variable maxLength to keep track of the maximum length of the window found so far.
// 5. Iterate through the string using the right pointer: (Expand the window by moving the right pointer)
//    a. Update the frequency of the character at the right pointer in the hash map.
//    b. Update maxFreqCount if the frequency of the current character exceeds maxFreqCount.
//    c. If the number of characters that need to be replaced (i.e., window size - maxFreqCount) exceeds k,
//       shrink the window from the left by moving the left pointer until the condition is satisfied and modify the frequency map and maxFreqCount accordingly.
//       i. Update the frequency of the character at the left pointer in the hash map.
//       ii. Move the left pointer to the right.
//       iii. Recalculate maxFreqCount for the current window.
//    d. Calculate the length of the current window (right - left + 1) and update maxLength if it's greater than the current maxLength.
// 6. Return maxLength after iterating through the string.

// Explanation with example "AAABBCCD", k = 2:
// - Start with left = 0, right = 0, maxFreqCount = 0, maxLength = 0
// - Read 'A': maxFreqCount = 1, maxLength = 1 left = 0, right = 0 change needed = 0 (charCount['A'] = 1)
// - Read 'A': maxFreqCount = 2, maxLength = 2 left = 0, right = 1 change needed = 0 (charCount['A'] = 2)
// - Read 'A': maxFreqCount = 3, maxLength = 3 left = 0, right = 2 change needed = 0 (charCount['A'] = 3)
// - Read 'B': maxFreqCount = 3, maxLength = 4 left = 0, right = 3 change needed = 1 (charCount['A'] = 3, charCount['B'] = 1)
// - Read 'B': maxFreqCount = 3, maxLength = 5 left = 0, right = 4 change needed = 2 (charCount['A'] = 3, charCount['B'] = 2)
// - Read 'C': maxFreqCount = 3, change needed = 3 which is > k, shrink window from left until change needed <= k
//   - Remove 'A' at index 0: change needed = 3 left = 1, right = 5 maxFreqCount = 2 (charCount['A'] = 2, charCount['B'] = 2, charCount['C'] = 1)
//   - Remove 'A' at index 1: change needed = 2 left = 2, right = 5 maxFreqCount = 2 (charCount['A'] = 1, charCount['B'] = 2, charCount['C'] = 1). Now change needed <= k
// - maxLength remains 5
// - Read 'C': maxFreqCount = 2, change needed = 3 which is > k, shrink window from left until change needed <= k
//   - Remove 'A' at index 2: change needed = 2 left = 3, right = 6 maxFreqCount = 2 (charCount['A'] = 0, charCount['B'] = 2, charCount['C'] = 2). Now change needed <= k
// - maxLength remains 5
// - Read 'D': maxFreqCount = 2, change needed = 3 which is > k, shrink window from left until change needed <= k
//   - Remove 'B' at index 3: change needed = 2 left = 4, right = 7 maxFreqCount = 2 (charCount['A'] = 0, charCount['B'] = 1, charCount['C'] = 2, charCount['D'] = 1). Now change needed <= k
// - maxLength remains 5
// - End of string, return maxLength = 5.




#include <iostream>
#include <string>
#include <vector>
using namespace std;

int characterReplacement(string s, int k) {
    vector<int> charCount(26, 0); // Frequency map for characters A-Z, index 0 for 'A', 1 for 'B', ..., 25 for 'Z', initialized to 0
    int left = 0; // Left pointer of the sliding window
    int maxFreqCount = 0; // Count of the most frequent character in the current window, initialized to 0
    int maxLength = 0; // Maximum length of the window found, initialized to 0

    // Expand the window with the right pointer
    for (int right = 0; right < s.length(); right++) {
        char currentChar = s[right];
        charCount[currentChar - 'A']++; // Update frequency of the current character

        // Update maxFreqCount if needed
        maxFreqCount = max(maxFreqCount, charCount[currentChar - 'A']);

        // If the number of characters to replace exceeds k, shrink the window from the left
        // We need to check condition: (window size - maxFreqCount) > k, right - left + 1 is window size
        while ((right - left + 1) - maxFreqCount > k) {
            char leftChar = s[left];
            charCount[leftChar - 'A']--; // Decrease frequency of the left character
            left++; // Move left pointer to the right

            // Recalculate maxFreqCount for the current window
            // If we want to improve time complexity, from O(N*26) to O(N), we can avoid recalculating maxFreqCount every time.
            // Why we can skip recalculating maxFreqCount every time?
            // Since we are only reducing the count of one character (the leftmost character) when we shrink the window,
            // the maxFreqCount can only decrease if the character we are removing was the one contributing to maxFreqCount.
            // However, if we keep track of the maximum frequency character while expanding the window,
            // we can avoid recalculating it every time we shrink the window.
            // window size - maxFreqCount > k means we have more than k characters to replace, and we are removing one character from the left,
            // means we are reducing window size, so decreasing maxFreqCount will only make the condition more likely to be satisfied.
            // Hence, we can afford to recalculate maxFreqCount only when necessary.
            maxFreqCount = 0;
            for (int count : charCount) {
                maxFreqCount = max(maxFreqCount, count);
            }
        }

        // Update maxLength
        maxLength = max(maxLength, right - left + 1);
    }

    return maxLength;
}

int main() {
    string s = "AAABBCCD";
    int k = 2;
    cout << "Length of Longest Repeating Character Replacement: " << characterReplacement(s, k) << "\n";
    return 0;
}

// Time Complexity: O(N * 26) = O(N), where N is the length of the string. In the worst case, we may need to recalculate maxFreqCount for each character in the string.
// Space Complexity: O(1), since the size of the frequency map is fixed at 26 for uppercase English letters.