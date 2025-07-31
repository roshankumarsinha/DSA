// Implement LFU Cache.

// Video Explanation: https://www.youtube.com/watch?v=0PSB9y8ehbk

// ✅ What is an LFU Cache?
// LFU stands for Least Frequently Used. It is a type of cache eviction policy that removes the item with the lowest usage frequency when the cache is full.

// 📌 Problem Statement
// Design a data structure that supports the following operations in O(1) or close to O(1) time:
//    1.  get(key) – Return the value of the key if it exists in the cache, otherwise return -1.
//    2.  put(key, value) – Update or insert the key-value pair.
//      a.  If the cache reaches its capacity, it should evict the least frequently used key.
//      b.  If multiple keys have the same frequency, remove the least recently used one among them.

// Intiution:
// We need to track:
//    1.  Frequency of each key (how many times it’s accessed).
//    2.  Among keys with the same frequency, evict the least recently used one (this requires ordering).
// To support both in O(1) time:
//    1.  Use a Doubly Linked List (DLL) for each frequency bucket.
//    2.  Use a map from key → node to access a node directly.
//    3.  Use a map from frequency → {head, tail} of the corresponding doubly linked list.


// 🧱 Data Structures Used:
// 1. unordered_map<int, Node*> cacheMap;
//    a.  Maps each key to its corresponding node (for O(1) lookup).
// 2. unordered_map<int, pair<Node*, Node*>> freqMap;
//    a.  Maps frequency f to a doubly linked list (DLL) (with dummy head and tail) of all nodes with frequency f.
// 3. minFreq
//    a.  Tracks the current minimum frequency in the cache (important for eviction).
// 4. Node class
//    a.  Each node stores: key, value, frequency, and DLL prev and next pointers.


// 🔄 Algorithm Steps:
// ✅ get(key):
//    1.  If key not found → return -1.
//    2.  Fetch the node.
//    3.  Update frequency of the node:
//      a.  Remove it from its current frequency list.
//      b.  Add it to the next higher frequency list.
//    4.  If the frequency list it was in becomes empty:
//      a.  Delete it from freqMap.
//      b.  If this was the minFreq, increment minFreq.
// ✅ put(key, value):
//    1.  If capacity == 0, do nothing.
//    2.  If key exists:
//      a.  Update value.
//      b.  Call updateFreq() to increase frequency.
//    3.  If key doesn't exist:
//      a.  If capacity is full:
//        a1. Evict least recently used node from minFreq list.
//        a2. Delete from cacheMap and DLL.
//      b.  Create new node with frequency = 1.
//      c.  Add to cacheMap and freqMap[1].
//      d.  Set minFreq = 1.

// 🔁 updateFreq(node):
//    1.  Increase the frequency of a node.
//    2.  Remove node from its current frequency DLL.
//    3.  If the DLL becomes empty and minFreq == oldFreq, increment minFreq.
//    4.  Insert the node into the DLL of newFreq.

// C++ Program to implement LFU (Least Frequently Used) cache
#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int key;  // Key of the node
    int value;  // Value of the node
    int cnt;  // Frequency count of the node
    Node *next;
    Node *prev;
  
    Node(int key, int val) {
        this->key = key;
        this->value = val;

        // Initial frequency is 1
        cnt = 1;
    }
};

// LFU Cache class
class LFUCache {
public:

    // Maps a key to the corresponding Node
    unordered_map<int, Node *> cacheMap;

    // Maps frequency to a pair of head and tail pointers
    unordered_map<int, pair<Node *, Node *>> freqMap;

    // Tracks the minimum frequency of the cache
    int minFreq;

    // Maximum capacity of the cache
    int capacity;

    // Constructor to initialize LFUCache with a given capacity
    LFUCache(int capacity) {
        this->capacity = capacity;
        
        // Initial minimum frequency is 0
        minFreq = 0; 
    }

    // Function to get the value associated with a key
    int get(int key) {

        // Return -1 if key is not found in the cache
        if (cacheMap.find(key) == cacheMap.end()) {
            return -1;
        }

        // Retrieve the Node and update its frequency
        Node *node = cacheMap[key];
        int res = node->value;
        updateFreq(node);
        return res;
    }

    // Function to add or update a key-value pair in the cache
    void put(int key, int value) {

        // Do nothing if the cache has zero capacity
        if (capacity == 0)
            return;

        // Update value if key already exists in the cache
        if (cacheMap.find(key) != cacheMap.end()) {

            Node *node = cacheMap[key];
            node->value = value;
            updateFreq(node);
        }

        // Add a new key-value pair to the cache
        else {

            // Remove the least frequently used node if cache is full
            if (cacheMap.size() == capacity) {

                Node *node = freqMap[minFreq].second->prev;
                cacheMap.erase(node->key);
                remove(node);

                // Remove the frequency list if it's empty
                if (freqMap[minFreq].first->next == freqMap[minFreq].second) {
                    freqMap.erase(minFreq);
                }

                // Free memory
                delete node; 
            }

            // Create a new node for the key-value pair
            Node *node = new Node(key, value);
            cacheMap[key] = node;
            
            // Reset minimum frequency to 1
            minFreq = 1; 
            add(node, 1);
        }
    }

    // Add a node to the frequency list
    void add(Node *node, int freq) {

        // Initialize the frequency list if it doesn't exist
        if (freqMap.find(freq) == freqMap.end()) {

            // Dummy head node
            Node *head = new Node(-1, -1); 
            
            // Dummy tail node
            Node *tail = new Node(-1, -1); 
            head->next = tail;
            tail->prev = head;
            freqMap[freq] = {head, tail};
        }

        // Insert the node right after the head
        Node *head = freqMap[freq].first;
        Node *temp = head->next;
        node->next = temp;
        node->prev = head;
        head->next = node;
        temp->prev = node;
    }

    // Remove a node from the frequency list
    void remove(Node *node) {

        // Update pointers to exclude the node
        Node *delprev = node->prev;
        Node *delnext = node->next;
        delprev->next = delnext;
        delnext->prev = delprev;
    }

    // Update the frequency of a node
    void updateFreq(Node *node) {

        // Get the current frequency
        int oldFreq = node->cnt; 

        // Increment the frequency
        node->cnt++; 

        // Remove the node from the current frequency list
        remove(node);

        // Remove the frequency list if it becomes empty
        if (freqMap[oldFreq].first->next == freqMap[oldFreq].second) {
            freqMap.erase(oldFreq);
            
            // Update minimum frequency if needed
            if (minFreq == oldFreq) {
                minFreq++;
            }
        }

        // Add the node to the updated frequency list
        add(node, node->cnt);
    }
};

int main() {

    LFUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << " ";
    cache.put(3, 3);
    cout << cache.get(2) << " ";
    cache.put(4, 4);
    cout << cache.get(3) << " ";
    cout << cache.get(4) << " ";
    cache.put(5, 5);

    return 0;
}