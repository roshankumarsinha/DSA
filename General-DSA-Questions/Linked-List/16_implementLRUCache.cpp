// Implement LRU Cache

// Notes : https://takeuforward.org/data-structure/implement-lru-cache/
// Video link : https://www.youtube.com/watch?v=z9bJUPxzFOw&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=18

// LRU stands for Least Recently Used. It is a caching mechanism that removes the least recently used item when the cache reaches its capacity limit.

// 📌 Problem Statement
// You are given a fixed-size cache (say of capacity k). You need to implement two operations efficiently:
//    1.  get(key) – Return the value if the key exists in the cache, else return -1.
//    2.  put(key, value) – Insert or update the key with the given value.
//      If the cache exceeds capacity, remove the least recently used item.
// Both operations must be done in O(1) time.

// ⚙️ Approach to Implement LRU Cache in O(1) Time
// We use two data structures:
// 1. Doubly Linked List (DLL)
//    a.  Stores the actual data in the order of usage.
//    b.  The most recently used (MRU) item is at the front (head).
//    c.  The least recently used (LRU) item is at the back (tail).
//    d.  Allows O(1) insertion and deletion from both ends.
// 2. Hash Map (unordered_map in C++)
//    a.  Maps a key to its corresponding node in the DLL.
//    b.  Allows O(1) access to any node for get() or update().

// 🔄 Operations Breakdown
// ✅ get(key):
//    1.  If the key exists in the map:
//      a.  Move the corresponding node to the front of the DLL (mark as most recently used).
//      b.  Return its value.
//    2.  If the key doesn't exist, return -1.
// ✅ put(key, value):
//    1.  If the key already exists:
//      a.  Update the node's value.
//      b.  Move it to the front.
//    2.  If it’s a new key:
//      a.  If cache is at capacity:
//        a1. Remove the node at the tail (least recently used).
//        a2. Remove its key from the map.
//      b.  Create a new node and insert it at the front.
//      c.  Add its key to the map.



#include <iostream>
#include <unordered_map>
using namespace std;

// Node for doubly linked list
class Node {
public:
    int key, value;
    Node* prev;
    Node* next;

    // Constructor for Node
    Node(int _key, int _value) {
        key = _key;
        value = _value;
        prev = next = nullptr;  // Initialize pointers to null
    }
};

class LRUCache {
  private:
    int capacity; // Maximum capacity of the cache
    unordered_map<int, Node*> cache;  // Maps key to Node in the doubly linked list
    // Doubly linked list to maintain the order of usage
    // head is the most recently used (MRU) and tail is the least recently used (LRU)
    Node* head;
    Node* tail;

    // Add node right after head, Insert at the front of the list
    // This is where the most recently used node will be added
    void addNode(Node* node) {
        node->next = head->next;  // Point new node's next to current head's next
        node->prev = head;  // Point new node's prev to head

        head->next->prev = node;  // Point current head's next's prev to new node
        head->next = node;  // Point head's next to new node
    }

    // Remove a node from the list, removes the node from its current position
    void removeNode(Node* node) {
        Node* prevNode = node->prev;  // Node before the one to be removed
        Node* nextNode = node->next;  // Node after the one to be removed

        prevNode->next = nextNode;  // Point previous node's next to next node
        nextNode->prev = prevNode;  // Point next node's prev to previous node
    }

    // Move a node to the front (most recently used)
    void moveToFront(Node* node) {
        removeNode(node); // Remove the node from its current position
        addNode(node);  // Add it to the front of the list
    }

    // Remove the least recently used node (from the back)
    Node* removeLRU() {
        Node* lru = tail->prev; // The node before tail is the least recently used
        removeNode(lru);  // Remove it from the list
        return lru; // Return the removed node
    }

  public:
    LRUCache(int _capacity) {
        capacity = _capacity;

        // Dummy head and tail
        head = new Node(0, 0);  // Create dummy head node
        tail = new Node(0, 0);  // Create dummy tail node

        head->next = tail;  // Point head's next to tail
        tail->prev = head;  // Point tail's prev to head
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            moveToFront(node);
            return node->value;
        }
        return -1; // Not found
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) { // Key exists
            // Update existing node and move to front
            Node* node = cache[key];
            node->value = value;
            moveToFront(node);
        } else {
            // New node
            if (cache.size() == capacity) {
                // Evict LRU
                Node* lru = removeLRU();
                cache.erase(lru->key);
                delete lru;
            }

            Node* newNode = new Node(key, value); // Create a new node
            cache[key] = newNode; // Add to cache map
            addNode(newNode); // Add to the front of the list
        }
    }

    ~LRUCache() {
        // Clean up memory
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
  LRUCache cache(2); // Capacity = 2

  cache.put(1, 1);   // Cache: [1]
  cache.put(2, 2);   // Cache: [2, 1]
  cout << cache.get(1) << endl; // Returns 1, Cache: [1, 2]

  cache.put(3, 3);   // Evicts key 2, Cache: [3, 1]
  cout << cache.get(2) << endl; // Returns -1 (not found)

  cache.put(4, 4);   // Evicts key 1, Cache: [4, 3]
  cout << cache.get(1) << endl; // Returns -1 (not found)
  cout << cache.get(3) << endl; // Returns 3
  cout << cache.get(4) << endl; // Returns 4

  return 0;
}

