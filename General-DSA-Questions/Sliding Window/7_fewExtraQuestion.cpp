// Longest Substring with At Most K Distinct Characters
// Given a string s and an integer k, return the length of the longest substring of s that contains at most k distinct characters.

// Notes link : https://takeuforward.org/data-structure/longest-substring-with-at-most-k-distinct-characters

// Intuition:
// We can use the sliding window technique to solve this problem efficiently.
// The idea is to maintain a window that contains at most k distinct characters.
// If the number of distinct characters in the current window exceeds k, we shrink the window from the left until we have at most k distinct characters again.
// At each step, we can update the maximum length of the window that contains at most k distinct characters.

// Approach:
// 1. Initialize two pointers, left and right, to represent the current window.
// 2. Use a hash map or an array of size 256 to keep track of the frequency of each character in the current window. We can use an array since there are only 256 ASCII characters.
//    We can also use unordered_map for a more general approach. Something like vector<int> charCount(256, 0); or unordered_map<char, int> charCount;
// 3. Initialize a variable distinctCount to keep track of the number of distinct characters in the current window.
// 4. Initialize a variable maxLength to keep track of the maximum length of the window found so far.
// 5. Iterate through the string using the right pointer: (Expand the window by moving the right pointer)
//    a. Update the frequency of the character at the right pointer in the hash map.
//    b. If the frequency of the current character becomes 1, it means it's a new distinct character, so increment distinctCount.
//    c. If distinctCount exceeds k, shrink the window from the left by moving the left pointer until distinctCount is at most k.
//       i. Update the frequency of the character at the left pointer in the hash map.
//       ii. If the frequency of that character becomes 0, it means we have removed a distinct character from the window, so decrement distinctCount.
//       iii. Move the left pointer to the right.
//    d. Calculate the length of the current window (right - left + 1) and update maxLength if it's greater than the current maxLength.
// 6. Return maxLength after iterating through the string.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int lengthOfLongestSubstringKDistinct(string s, int k) {
    vector<int> charCount(256, 0); // Frequency map for all ASCII characters, initialized to 0
    int left = 0; // Left pointer of the sliding window
    int distinctCount = 0; // Count of distinct characters in the current window
    int maxLength = 0; // Maximum length of the window found

    // Expand the window with the right pointer
    for (int right = 0; right < s.length(); right++) {
        char currentChar = s[right];
        charCount[currentChar]++; // Update frequency of the current character

        // If it's a new distinct character, increment distinctCount
        if (charCount[currentChar] == 1) {
            distinctCount++;
        }

        // If distinctCount exceeds k, shrink the window from the left
        while (distinctCount > k) {
            char leftChar = s[left];
            charCount[leftChar]--; // Update frequency of the left character

            // If frequency becomes 0, we removed a distinct character
            if (charCount[leftChar] == 0) {
                distinctCount--;
            }
            left++; // Move left pointer to the right
        }

        // Update maxLength if the current window is larger
        maxLength = max(maxLength, right - left + 1);
    }

    return maxLength;
}



// Subarray with k different integers
// Given an array nums and an integer k, return the number of good subarrays of nums.
// A good array is an array where the number of different integers in that array is exactly k.

// Notes link : https://takeuforward.org/data-structure/subarray-with-k-different-integers

// Intuition:
// We can use the sliding window technique to solve this problem efficiently.
// The idea is to find the number of subarrays with at most k distinct integers and the number of subarrays with at most (k-1) distinct integers.
// The difference between these two counts will give us the number of subarrays with exactly k distinct integers.
// This is because every subarray with exactly k distinct integers is counted in the count of subarrays with at most k distinct integers
// but not in the count of subarrays with at most (k-1) distinct integers.

// This question is similar to the previous question where we needed to find the length of the longest substring with at most k distinct characters.
// Here, instead of length, we need to count the number of such subarrays.