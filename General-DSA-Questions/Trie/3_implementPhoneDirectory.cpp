// Write a function to implement a Phone Directory.

// Implement a system where:
//    You can add names to a phone directory.
//    Given a search prefix, you can return all contact names that start with that prefix — like auto-suggestions!

// Approach:
// 1. The Data Structure will look like this, Each node has:
//    a.  children[26]: An array for 26 lowercase letters.
//    b.  isEndOfWord: Marks if a full word ends here.
//    c.  fullName: The full contact name (for final output).
// 2. Then we will insert all names into the Trie.
//    a.  For each word, if we reach the end of the word, we will set isEndOfWord to true and store the full name.
// 3. For searching, we will traverse the Trie using the prefix.
// 4. If we reach the end of the prefix, we will call a recursive function to find all names starting with that prefix.


#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode {
  public:
    TrieNode* children[ALPHABET_SIZE]; // Array of child nodes
    bool isEndOfWord; // Flag to indicate if the node represents the end of a word
    string fullName; // Full contact name (for final output)

    // Constructor to initialize a TrieNode
    TrieNode() {
        isEndOfWord = false; // Initially, it's not the end of a word
        fullName = ""; // Initialize fullName as an empty string
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr; // Initialize all children to nullptr
        }
    }
};

class PhoneDirectory {
  private:
    TrieNode* root; // Root node of the trie

    // Function to recursively find all names starting with a given prefix
    void dfs(TrieNode* node, vector<string>& results) {
        // If the current node is the end of a word, add the full name to the result
        if (node->isEndOfWord) {
            results.push_back(node->fullName);
        }

        // Traverse all children nodes, for each child node
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            // If the child node exists, recursively call dfs on it
            if (node->children[i] != nullptr) {
                dfs(node->children[i], results); // Recursive call for child nodes
            }
        }
    }

  public:
    PhoneDirectory() {
        root = new TrieNode(); // Initialize the root node
    }

    // Function to insert a name into the phone directory
    void insert(string name) {
        TrieNode* node = root; // Start from the root node
        // Traverse the trie for each character in the name
        for (char ch : name) {
            int index = ch - 'a'; // Calculate index for the character
            // If the child node for the character doesn't exist, create a new TrieNode
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index]; // Move to the child node
        }
        node->isEndOfWord = true; // Mark the end of the word
        node->fullName = name; // Store the full name at the end of the word
    }

    // Function to search for names starting with a given prefix
    vector<string> search(string prefix) {
        TrieNode* node = root; // Start from the root node
        vector<string> results; // Vector to store the results

        // Traverse the trie for each character in the prefix
        for (char ch : prefix) {
            int index = ch - 'a'; // Calculate index for the character
            // If the child node for the character doesn't exist, return an empty result
            if (!node->children[index]) {
                return results; // No names found with this prefix
            }
            node = node->children[index]; // Move to the child node
        }

        // Call dfs to find all names starting with the given prefix. We are passing the node where the prefix ends
        // This node may or may not be the end of a word, but we want to find all names starting from here
        dfs(node, results); // Recursive call to find all names

        return results; // Return the list of names starting with the prefix
    }

};

int main() {
    PhoneDirectory phoneDirectory; // Create a PhoneDirectory object

    // Insert names into the phone directory
    phoneDirectory.insert("alice");
    phoneDirectory.insert("alex");
    phoneDirectory.insert("albert");
    phoneDirectory.insert("bob");
    phoneDirectory.insert("bella");

    // Search for names starting with a given prefix
    string prefix = "al";
    vector<string> results = phoneDirectory.search(prefix);

    // Print the results
    cout << "Names starting with prefix '" << prefix << "':" << endl;
    for (const string& name : results) {
        cout << name << endl; // Print each name found
    }

    return 0; // Return success
}

// Output:
// Names starting with prefix 'al':
// alice
// alex
// albert

// Explanation:
// 🔢 Step-by-Step Insertion into Trie
// Let's insert "alice":
// 'a' → create node
// 'l' → create node
// 'i' → create node
// 'c' → create node
// 'e' → create node and mark it as isEndOfWord = true, and store fullName = "alice"

// Now insert "alex":
// 'a' → already exists
// 'l' → already exists
// 'e' → new node (under 'l')
// 'x' → create node → isEndOfWord = true, fullName = "alex"

// Now insert "albert":
// 'a' → exists
// 'l' → exists
// 'b' → new node
// 'e', 'r', 't' → create each node, ending in isEndOfWord = true, fullName = "albert"

// (And we insert "bob" and "bella" in similar fashion.)


// 🔍 Search for Prefix "al"
// Step 1: Traverse Trie
// 'a' → go to 'a'
// 'l' → go to 'l' → ✅ found prefix node

// Step 2: DFS from 'l' node
// We explore every path from 'l':
// l → i → c → e → isEndOfWord = true → "alice"
// l → e → x → isEndOfWord = true → "alex"
// l → b → e → r → t → isEndOfWord = true → "albert"

// Final Results:
// ["alex", "alice", "albert"]




// Time Complexity:

// ✅ 1. Insertion of a Contact
// void insert(const string& name);
//    a.  For a contact of length L, we insert each character once.
//    b.  At each character, we check and possibly create a node in O(1) time.
// TC for inserting 1 contact:
// O(L)

// TC for inserting N contacts with average length L:
// O(N × L)


// ✅ 2. Searching by Prefix
// vector<string> searchPrefix(const string& prefix);
// Step 1: Traverse the Prefix
//    a.  Walk through each character in the prefix → O(P)
//        (P = length of prefix)

// Step 2: DFS for Suggestions
//    a.  Suppose K strings match the prefix, with average length M:
//        a1. DFS explores every character of every matching name
//        a2. So DFS time is O(K × M)

// ✅ Total Search Time:
// O(P + K × M)
