// Write a function to implement a Phone Directory.

// Implement a system where:
//    You can add names to a phone directory.
//    Given a search prefix, you can return all contact names that start with that prefix — like auto-suggestions!

// Approach:
// 1. The Data Structure will look like this. Each node has:
//    a.  children: A map of character -> child node (26 lowercase letters in the original).
//    b.  isEndOfWord: Marks if a full word ends here.
//    c.  fullName: The full contact name (for final output).
// 2. Then we will insert all names into the Trie.
//    a.  For each word, when we reach the end we set isEndOfWord to true and store the full name.
// 3. For searching, we traverse the Trie using the prefix.
// 4. If we reach the end of the prefix, we run a DFS to collect all names starting with that prefix.

// JavaScript note: like the other Trie files, children is a plain object keyed by character
// instead of a fixed array[26]. We iterate children with Object.values() during DFS. To keep
// the DFS output in sorted (alphabetical) order like the C++ array-index traversal, we sort
// the child keys before recursing.
class TrieNode {
  constructor() {
    this.children = {};
    this.isEndOfWord = false; // Initially, it's not the end of a word
    this.fullName = ""; // Full contact name (for final output)
  }
}

class PhoneDirectory {
  constructor() {
    this.root = new TrieNode();
  }

  // Function to recursively find all names starting from a given node
  #dfs(node, results) {
    // If the current node is the end of a word, add the full name to the result
    if (node.isEndOfWord) {
      results.push(node.fullName);
    }
    // Traverse child nodes in alphabetical order (mimics C++ array index order)
    for (const ch of Object.keys(node.children).sort()) {
      this.#dfs(node.children[ch], results);
    }
  }

  // Function to insert a name into the phone directory
  insert(name) {
    let node = this.root;
    for (const ch of name) {
      if (!node.children[ch]) {
        node.children[ch] = new TrieNode();
      }
      node = node.children[ch];
    }
    node.isEndOfWord = true; // Mark the end of the word
    node.fullName = name; // Store the full name at the end of the word
  }

  // Function to search for names starting with a given prefix
  search(prefix) {
    let node = this.root;
    const results = [];

    // Traverse the trie for each character in the prefix
    for (const ch of prefix) {
      if (!node.children[ch]) {
        return results; // No names found with this prefix
      }
      node = node.children[ch];
    }

    // DFS from the node where the prefix ends to find all names below it
    this.#dfs(node, results);
    return results;
  }
}

// Driver code
const phoneDirectory = new PhoneDirectory();
phoneDirectory.insert("alice");
phoneDirectory.insert("alex");
phoneDirectory.insert("albert");
phoneDirectory.insert("bob");
phoneDirectory.insert("bella");

const prefix = "al";
const results = phoneDirectory.search(prefix);
console.log(`Names starting with prefix '${prefix}':`);
for (const name of results) {
  console.log(name);
}

// Output:
// Names starting with prefix 'al':
// albert
// alex
// alice

// Time Complexity:
// Insertion of 1 contact of length L: O(L). For N contacts of avg length L: O(N × L).
// Searching by prefix: O(P + K × M), where P = prefix length, K = number of matches,
// M = average length of matching names.
