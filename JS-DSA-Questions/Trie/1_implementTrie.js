// Write a program to implement a trie data structure in JavaScript.

// Notes link : https://takeuforward.org/data-structure/implement-trie-1/

// Approach for Insertion :
// 1. Start from the root node, which is an empty node.
// 2. For each character in the word, check if the corresponding child node exists.
// 3. If it doesn't exist, create a new TrieNode for that character.
// 4. Move to the child node corresponding to the character.
// 5. After inserting all characters, mark the end of the word by setting isEndOfWord to true.
// 6. Repeat the process for each word to be inserted.
// Example: If we want to insert the word "cat", "dog" and "cap". I've represented isEndOfWord with " ' ".
// The trie structure will look like this:
  //       (root)
  //       /    \
  //     c       d
  //    /         \
  //   a           o
  //  / \           \
  // t'  p'          g'

// Approach for Searching :
// 1. Start from the root node.
// 2. For each character in the word, check if the corresponding child node exists.
// 3. If it doesn't exist, return false (word not found).
// 4. Move to the child node corresponding to the character.
// 5. After traversing all characters, check isEndOfWord to see if it's a complete word.

// Approach for Deletion (without removing nodes) :
// 1. Traverse to the node representing the last character of the word.
// 2. If the word exists, mark isEndOfWord as false.
// 3. Note: The nodes are not deleted, but the word is effectively removed by unsetting isEndOfWord.

// Approach for Prefix Searching :
// 1. Traverse the trie following the prefix characters.
// 2. If we can walk the whole prefix, return true; otherwise false.

// JavaScript note: C++ used a fixed array children[26] indexed by (ch - 'a'). In JS the
// idiomatic choice is a plain object (or Map) keyed directly by the character, so we don't
// need charCodeAt arithmetic. Here we use an object `{}` for children.
class TrieNode {
  constructor() {
    // Each TrieNode maps a character -> child TrieNode
    this.children = {};
    // A boolean flag to indicate if the node represents the end of a word
    this.isEndOfWord = false;
  }
}

// Trie class to manage the root node and provide methods for insertion, search, and deletion
class Trie {
  constructor() {
    // The root node does not represent any character; it's the starting point for all words.
    this.root = new TrieNode();
  }

  // Function to insert a word into the trie
  insert(word) {
    let currentNode = this.root;
    for (const ch of word) {
      // If the child node for the character doesn't exist, create a new TrieNode
      if (!currentNode.children[ch]) {
        currentNode.children[ch] = new TrieNode();
      }
      // Move to the child node corresponding to the character
      currentNode = currentNode.children[ch];
    }
    // Mark the end of the word
    currentNode.isEndOfWord = true;
  }

  // Function to search for a word in the trie
  search(word) {
    let currentNode = this.root;
    for (const ch of word) {
      // If the child node doesn't exist, the word is not present
      if (!currentNode.children[ch]) {
        return false;
      }
      currentNode = currentNode.children[ch];
    }
    // Return true only if this node marks the end of a complete word
    return currentNode.isEndOfWord;
  }

  // Function to delete a word from the trie, but without removing the nodes
  remove(word) {
    let currentNode = this.root;
    for (const ch of word) {
      if (!currentNode.children[ch]) {
        return; // Word not found, nothing to remove
      }
      currentNode = currentNode.children[ch];
    }
    // Effectively remove the word by unsetting the end-of-word flag
    if (currentNode.isEndOfWord) {
      currentNode.isEndOfWord = false;
    }
  }

  // Function to check if any word in the trie starts with a given prefix
  startsWith(prefix) {
    let currentNode = this.root;
    for (const ch of prefix) {
      if (!currentNode.children[ch]) {
        return false; // Prefix not found
      }
      currentNode = currentNode.children[ch];
    }
    return true; // Prefix found
  }
}

// Driver code
const trie = new Trie();
trie.insert("cat");
trie.insert("dog");
trie.insert("cap");

console.log("Search for 'cat':", trie.search("cat") ? "Found" : "Not Found"); // Found
console.log("Search for 'dog':", trie.search("dog") ? "Found" : "Not Found"); // Found
console.log("Search for 'cap':", trie.search("cap") ? "Found" : "Not Found"); // Found
console.log("Search for 'bat':", trie.search("bat") ? "Found" : "Not Found"); // Not Found

trie.remove("cap");
console.log("Search for 'cap' after removal:", trie.search("cap") ? "Found" : "Not Found"); // Not Found

console.log("Starts with 'ca':", trie.startsWith("ca") ? "Yes" : "No"); // Yes
console.log("Starts with 'do':", trie.startsWith("do") ? "Yes" : "No"); // Yes
console.log("Starts with 'ba':", trie.startsWith("ba") ? "Yes" : "No"); // No

// Time Complexity:
// Insertion: O(m), where m is the length of the word being inserted.
// Search: O(m), where m is the length of the word being searched.
// Prefix Search: O(m), where m is the length of the prefix being searched.
