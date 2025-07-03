// Write a program to implement a trie data structure in C++.

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
// 5. After traversing all characters, check if we are at the end of a word by checking isEndOfWord.
// 6. If we are at the end of a word, return true (word found), otherwise return false.

// Approach for Deletion (without removing nodes) :
// 1. Start from the root node.
// 2. For each character in the word, check if the corresponding child node exists.
// 3. If it doesn't exist, return (word not found).
// 4. Move to the child node corresponding to the character.
// 5. After traversing all characters, check if we are at the end of a word.
// 6. If we are at the end of a word, mark isEndOfWord as false (word removed).
// 7. Note: The nodes are not deleted, but the word is effectively removed from the trie by marking isEndOfWord as false.

// Approach for Prefix Searching :
// 1. Start from the root node.
// 2. For each character in the prefix, check if the corresponding child node exists.
// 3. If it doesn't exist, return false (prefix not found).
// 4. Move to the child node corresponding to the character.
// 5. If we successfully traversed all characters in the prefix, return true (prefix found).


#include <iostream>
using namespace std;

class TrieNode {
  public:
    // Each TrieNode contains an array of pointers to its children
    TrieNode* children[26];
    // A boolean flag to indicate if the node represents the end of a word
    bool isEndOfWord;

    // Constructor to initialize a TrieNode
    // Sets isEndOfWord to false and initializes all children to nullptr
    TrieNode() {
        isEndOfWord = false;
        // We have 26 children for each letter of the alphabet
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

// Trie class to manage the root node and provide methods for insertion, search, and deletion
class Trie {
  private:
    // The root node of the trie
    TrieNode* root;

  public:
    // Constructor to initialize the root node
    Trie() {
        // Create a new TrieNode for the root
        // This node does not represent any character
        // It serves as the starting point for all words in the trie
        root = new TrieNode();
    }

    // Function to insert a word into the trie
    void insert(string word) {
        // Start from the root node
        TrieNode* currentNode = root;
        // Iterate through each character in the word
        for (char ch : word) {
            // Convert character to lowercase to handle case insensitivity
            int index = ch - 'a'; // Calculate index for the character
            // Check if the child node for the character exists
            // If it doesn't exist, create a new TrieNode for that character
            if (currentNode->children[index] == nullptr) {
                currentNode->children[index] = new TrieNode(); // Create a new node if it doesn't exist
            }
            // Move to the child node corresponding to the character
            // This allows us to traverse down the trie as we insert each character
            currentNode = currentNode->children[index]; // Move to the child node
        }
        // After inserting all characters, mark the end of the word
        // This indicates that the current node represents a complete word
        currentNode->isEndOfWord = true; // Mark the end of the word
    }
    
    // Function to search for a word in the trie
    bool search(string word) {
        // Start from the root node
        TrieNode* currentNode = root;
        // Iterate through each character in the word
        for (char ch : word) {
            // Convert character to lowercase to handle case insensitivity
            int index = ch - 'a'; // Calculate index for the character
            // Check if the child node for the character exists
            // If it doesn't exist, the word is not present in the trie
            if (currentNode->children[index] == nullptr) {
                return false; // Word not found
            }
            // Move to the child node corresponding to the character
            currentNode = currentNode->children[index]; // Move to the child node
        }
        // After traversing all characters, check if we are at the end of a word
        return currentNode->isEndOfWord; // Return true if it's a complete word, false otherwise
    }

    // Function for deleting a word from the trie, but without removing the nodes
    void remove(string word) {
        // Start from the root node
        TrieNode* currentNode = root;
        // Iterate through each character in the word
        for (char ch : word) {
            // Convert character to lowercase to handle case insensitivity
            int index = ch - 'a'; // Calculate index for the character
            // Check if the child node for the character exists
            // If it doesn't exist, the word is not present in the trie
            if (currentNode->children[index] == nullptr) {
                return; // Word not found, nothing to remove
            }
            // Move to the child node corresponding to the character
            currentNode = currentNode->children[index]; // Move to the child node
        }
        // After traversing all characters, mark the end of the word as false
        if (currentNode->isEndOfWord) {
            currentNode->isEndOfWord = false; // Mark the end of the word as false
        }
        // Note: The nodes are not deleted, but the word is effectively removed
        // from the trie by marking isEndOfWord as false.
    }

    // Function to check if any word in the trie starts with a given prefix
    bool startsWith(string prefix) {
        // Start from the root node
        TrieNode* currentNode = root;
        // Iterate through each character in the prefix
        for (char ch : prefix) {
            // Convert character to lowercase to handle case insensitivity
            int index = ch - 'a'; // Calculate index for the character
            // Check if the child node for the character exists
            // If it doesn't exist, no word with that prefix is present in the trie
            if (currentNode->children[index] == nullptr) {
                return false; // Prefix not found
            }
            // Move to the child node corresponding to the character
            currentNode = currentNode->children[index]; // Move to the child node
        }
        // If we successfully traversed all characters in the prefix, return true
        return true; // Prefix found
    }
};

int main() {
    // Create a new Trie object
    Trie trie;
    // Insert words into the trie
    trie.insert("cat");
    trie.insert("dog");
    trie.insert("cap");
    
    // Search for words in the trie
    cout << "Search for 'cat': " << (trie.search("cat") ? "Found" : "Not Found") << endl; // Output: Found
    cout << "Search for 'dog': " << (trie.search("dog") ? "Found" : "Not Found") << endl; // Output: Found
    cout << "Search for 'cap': " << (trie.search("cap") ? "Found" : "Not Found") << endl; // Output: Found
    cout << "Search for 'bat': " << (trie.search("bat") ? "Found" : "Not Found") << endl; // Output: Not Found

    // Remove a word from the trie
    trie.remove("cap");
    cout << "Search for 'cap' after removal: " << (trie.search("cap") ? "Found" : "Not Found") << endl; // Output: Not Found

    // Check if any word starts with a given prefix
    cout << "Starts with 'ca': " << (trie.startsWith("ca") ? "Yes" : "No") << endl; // Output: Yes
    cout << "Starts with 'do': " << (trie.startsWith("do") ? "Yes" : "No") << endl; // Output: Yes
    cout << "Starts with 'ba': " << (trie.startsWith("ba") ? "Yes" : "No") << endl; // Output: No

    return 0;
}

// Time Complexity:
// Insertion: O(m), where m is the length of the word being inserted.
// Search: O(m), where m is the length of the word being searched.
// Prefix Search: O(m), where m is the length of the prefix being searched.

