// Write a function to implement a Longest Common Prefix.

// Given an array of strings, find the longest common prefix among all the strings.
// If there's no common prefix, return an empty string "".

// Example:
// Input:  ["flower", "flow", "flight"]  -> Output: "fl"
// Input:  ["dog", "racecar", "car"]     -> Output: ""

// Approach 1: (Using Vertical scanning)
// We compare characters column by column (vertically) from left to right across all strings:
// 1. Start with the first character of the first word.
// 2. Check if this character matches the same position in every other word.
// 3. If all match, continue to the next character. If not, return the prefix collected so far.
// Time Complexity: O(S), where S is the sum of all characters in all strings.
// Space Complexity: O(1).
//
// function longestCommonPrefix(strs) {
//     if (strs.length === 0) return "";
//     for (let i = 0; i < strs[0].length; i++) {
//         const currentChar = strs[0][i];
//         for (let j = 1; j < strs.length; j++) {
//             if (i >= strs[j].length || strs[j][i] !== currentChar) {
//                 return strs[0].slice(0, i);
//             }
//         }
//     }
//     return strs[0];
// }

// Approach 2: (Using Trie)
// 1. Insert all words into the Trie.
// 2. Each node tracks childCount (number of distinct children).
// 3. Traverse the Trie until we find a node with more than one child or that is isEndOfWord.
// 4. The path taken so far is the longest common prefix.
// Time Complexity: O(S) for inserting all words.
// Space Complexity: O(N), where N is the number of nodes in the Trie.
// This approach is relatively bad for space, as we store all characters in the Trie.

// JavaScript note: children is an object keyed by character. childCount is simply
// Object.keys(node.children).length, but we maintain it explicitly to mirror the C++ code.
class TrieNode {
  constructor() {
    this.children = {};
    this.isEndOfWord = false;
    this.childCount = 0; // Number of children for this node
  }
}

class Trie {
  constructor() {
    this.root = new TrieNode();
  }

  insert(word) {
    let node = this.root;
    for (const ch of word) {
      if (!node.children[ch]) {
        node.children[ch] = new TrieNode();
        node.childCount++; // ✅ increment child count on first creation
      }
      node = node.children[ch];
    }
    node.isEndOfWord = true;
  }

  // Function to find the longest common prefix in the Trie
  longestCommonPrefix() {
    let prefix = "";
    let node = this.root;

    // Continue while the node has exactly one child and is not the end of a word
    while (node && node.childCount === 1 && !node.isEndOfWord) {
      // There is exactly one child; grab its key and move down
      const onlyChar = Object.keys(node.children)[0];
      prefix += onlyChar;
      node = node.children[onlyChar];
    }
    return prefix;
  }
}

// Driver code
const trie = new Trie();
const words = ["flower", "flow", "flight"];
for (const word of words) {
  trie.insert(word);
}
console.log("Longest Common Prefix:", trie.longestCommonPrefix()); // "fl"
