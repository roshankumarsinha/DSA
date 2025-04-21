// Write a function to implement a Longest Common Prefix.

// Given an array of strings, find the longest common prefix among all the strings.
// If there's no common prefix, return an empty string "".

// Example:
// Input:  ["flower", "flow", "flight"]
// Output: "fl"
// So, common prefix for ["flower", "flow", "flight"] is "fl"

// Input:  ["dog", "racecar", "car"]
// Output: ""

// Approach 1: (Using Vertical scanning)
// We compare characters column by column (vertically) from left to right across all strings:
// 1. Start with the first character of the first word.
// 2. Check if this character matches the same position in every other word.
// 3. If all match, continue to the next character.
// 4. If not, return the common prefix collected so far.
// Time Complexity: O(S), where S is the sum of all characters in all strings.
// Space Complexity: O(1), as we are using only a few variables to store the prefix.

// string longestCommonPrefix(vector<string>& strs) {
//     if (strs.empty()) return "";

//     // Iterate through each character of the first string
//     // and compare it with the same index in all other strings
//     for (int i = 0; i < strs[0].size(); ++i) {
//         char currentChar = strs[0][i];  // Current character to compare
//         for (int j = 1; j < strs.size(); ++j) { // Start from the second string
//             // Stop if index exceeds current string length or characters mismatch
//             if (i >= strs[j].size() || strs[j][i] != currentChar) {
//                 return strs[0].substr(0, i);  // return prefix till now
//             }
//         }
//     }

//     return strs[0];  // all characters matched in all strings
// }


// Approach 2: (Using Trie)
// 1. Insert all words into the Trie.
// 2. The Trie structure will have childCount for each node.
// 3. Traverse the Trie until we find a node with more than one child or isEndOfWord.
// 4. The path taken to reach this node will be the longest common prefix.
// 5. Return the prefix collected during the traversal.
// Time Complexity: O(S), where S is the sum of all characters in all strings. For inserting all words.
// Space Complexity: O(N), where N is the number of nodes in the Trie.
// This approach is relatively bad for space complexity, as we are storing all characters in the Trie.

#include <iostream>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;

// Trie Node with childCount
struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int childCount;  // Number of children for this node

    TrieNode() {
        isEndOfWord = false;
        childCount = 0;  // initialize to 0
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }
};

class Trie {
  private:
    TrieNode* root;

  public:
    Trie() {
        root = new TrieNode();
    }


    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
                // Increment child count for each new child node created
                // This is the first time we are creating this child node
                node->childCount++;  // ✅ increment child count
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    // Function to find the longest common prefix in the Trie
    string longestCommonPrefix() {
        string prefix = "";
        TrieNode* node = root;

        // Traverse the Trie until we find a node with more than one child or isEndOfWord
        while (node && node->childCount == 1 && !node->isEndOfWord) {
            // Find the only child node
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (node->children[i]) {
                    prefix += (char)(i + 'a');  // Append character to prefix
                    node = node->children[i];    // Move to the child node
                    break;
                }
            }
        }
        return prefix;
    }
};

int main() {
    Trie trie;
    vector<string> words = {"flower", "flow", "flight"};

    // Insert all words into the Trie
    for (const string& word : words) {
        trie.insert(word);
    }

    // Find and print the longest common prefix
    string lcp = trie.longestCommonPrefix();
    cout << "Longest Common Prefix: " << lcp << endl;

    return 0;
}
