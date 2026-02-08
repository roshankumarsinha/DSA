/*
    =====================================================
    REVERSE WORDS IN A STRING
    =====================================================

    Problem: Given an input string s, reverse the order of the words.
    A word is defined as a sequence of non-space characters. The words 
    in s are separated by at least one space. Return a string with words 
    in reverse order, separated by a single space (no leading/trailing 
    spaces, no extra spaces between words).

    Example:
    Input: s = "the sky is blue"
    Output: "blue is sky the"

    Input: s = "  hello world  "
    Output: "world hello"

    Input: s = "a good   example"
    Output: "example good a"

    =====================================================
    INTUITION:
    =====================================================
    
    Approach 1: EXTRACT WORDS + BUILD IN REVERSE
    - Extract each word, store them, then build result from last to first
    - Clean and straightforward

    Approach 2: REVERSE ENTIRE STRING + REVERSE EACH WORD (In-place)
    - Similar to the array rotation trick!
    - Step 1: Reverse the entire string → words are in correct order 
              but each word is reversed
    - Step 2: Reverse each individual word to fix them
    - Step 3: Clean up extra spaces

    Example walkthrough (Approach 2):
    "the sky is blue"
    → Reverse entire: "eulb si yks eht"
    → Reverse each word: "blue is sky the" ✓

    =====================================================
    APPROACH 1 (Using word extraction):
    =====================================================
    1. Traverse string, skip spaces, extract words
    2. Store words in a vector
    3. Build result by iterating vector from LAST to FIRST
    4. Join with single space

    =====================================================
    EXAMPLE DRY RUN (Approach 1):
    =====================================================
    Input: s = "a good   example"

    Step 1: Extract words
    i=0: 'a' → word = "a", words = ["a"]
    i=1: ' ' → skip
    i=2: 'g' → start of word
    i=5: ' ' → word = "good", words = ["a", "good"]
    i=6,7,8: ' ' → skip
    i=9: 'e' → start of word
    i=15: end → word = "example", words = ["a", "good", "example"]

    Step 2: Build result from last to first
    result = "example" + " " + "good" + " " + "a"
    result = "example good a"

    Output: "example good a" ✓

    =====================================================
    APPROACH 2 (In-place with reversals):
    =====================================================
    1. Reverse the entire string
    2. Reverse each individual word
    3. Clean up: remove leading, trailing, and extra spaces

    =====================================================
    EXAMPLE DRY RUN (Approach 2):
    =====================================================
    Input: s = "  hello world  "

    Step 1: Reverse entire string
    "  dlrow olleh  "

    Step 2: Reverse each word (skip spaces, find word boundaries)
    Word 1: "dlrow" at index 2-6 → reverse → "world"
    Word 2: "olleh" at index 8-12 → reverse → "hello"
    String: "  world hello  "

    Step 3: Clean up spaces
    Remove leading/trailing spaces, collapse multiple spaces
    Result: "world hello"

    Output: "world hello" ✓

    =====================================================
    TIME COMPLEXITY:  O(n) - Both approaches traverse string linearly
    SPACE COMPLEXITY: O(n) - For storing words / result string
    =====================================================
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Approach 1: Extract words and build in reverse order
string reverseWords(string s) {
    vector<string> words;
    int n = s.length();
    int i = 0;
    
    // Extract words, skipping spaces
    while (i < n) {
        // Skip spaces
        while (i < n && s[i] == ' ') i++;
        
        if (i >= n) break;
        
        // Find end of word
        int start = i;
        while (i < n && s[i] != ' ') i++;
        
        // Extract word and store
        words.push_back(s.substr(start, i - start));
    }
    
    // Build result in reverse order
    string result = "";
    for (int j = words.size() - 1; j >= 0; j--) {
        result += words[j];
        if (j > 0) result += " ";
    }
    
    return result;
}


// Approach 2: In-place reversals (no extra word storage)
string reverseWordsInPlace(string s) {
    // Step 1: Reverse entire string
    reverse(s.begin(), s.end());
    
    int n = s.length();
    int i = 0;

    // writePos will track the position to write cleaned-up characters (no extra spaces), example: "  hello world  " → "hello world"
    int writePos = 0;
    
    while (i < n) {
        // Skip spaces
        while (i < n && s[i] == ' ') i++;
        
        if (i >= n) break;
        
        // Add space before word (except for the first word)
        if (writePos > 0) s[writePos++] = ' ';
        
        // Step 2: Copy and reverse each word
        int wordStart = writePos;
        while (i < n && s[i] != ' ') {
            s[writePos++] = s[i++];
        }
        
        // Reverse the word to fix its order
        reverse(s.begin() + wordStart, s.begin() + writePos);
    }
    
    // Step 3: Resize to remove trailing characters
    s.resize(writePos);
    
    return s;
}


// In Javascript we can easily achieve this using regex:
/*
function reverseWords(s) {
    // Trim leading/trailing spaces
    s = s.trim();

    // Split by one or more spaces using regex, then reverse and join
    // The regex /\s+/ matches one or more whitespace characters, so it will handle multiple spaces between words.
    return s.split(/\s+/).reverse().join(' ');
}
*/
