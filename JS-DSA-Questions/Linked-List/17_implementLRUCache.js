// Implement an LRU (Least Recently Used) Cache.

// Notes : https://takeuforward.org/data-structure/implement-lru-cache/
// Video link : https://www.youtube.com/watch?v=z9bJUPxzFOw&list=PLgUwDviBIf0pOd5zvVVSzgpo6BaCpHT9c&index=18

// 📌 Problem: fixed-capacity cache with O(1):
//    get(key)        – return value or -1
//    put(key, value) – insert/update; evict the least recently used item when over capacity.

// ⚙️ Approach:
// 1. Doubly Linked List (DLL): most recently used at the front (after head), least recently used at
//    the back (before tail). O(1) insert/delete at both ends.
// 2. Map: key -> node, for O(1) access.
//
// JavaScript note: C++ used unordered_map<int, Node*>. Here we use a Map. JS has a built-in Map
// that actually preserves insertion order, so an LRU can also be written with just a Map — but we
// keep the explicit DLL to mirror the original and show the mechanism.

class Node {
  constructor(key, value) {
    this.key = key;
    this.value = value;
    this.prev = null;
    this.next = null;
  }
}

class LRUCache {
  constructor(capacity) {
    this.capacity = capacity;
    this.cache = new Map(); // key -> Node

    // Dummy head and tail
    this.head = new Node(0, 0);
    this.tail = new Node(0, 0);
    this.head.next = this.tail;
    this.tail.prev = this.head;
  }

  // Add node right after head (most recently used position)
  #addNode(node) {
    node.next = this.head.next;
    node.prev = this.head;
    this.head.next.prev = node;
    this.head.next = node;
  }

  // Remove a node from its current position
  #removeNode(node) {
    const prevNode = node.prev;
    const nextNode = node.next;
    prevNode.next = nextNode;
    nextNode.prev = prevNode;
  }

  // Move a node to the front (mark most recently used)
  #moveToFront(node) {
    this.#removeNode(node);
    this.#addNode(node);
  }

  // Remove and return the least recently used node (before tail)
  #removeLRU() {
    const lru = this.tail.prev;
    this.#removeNode(lru);
    return lru;
  }

  get(key) {
    if (this.cache.has(key)) {
      const node = this.cache.get(key);
      this.#moveToFront(node);
      return node.value;
    }
    return -1;
  }

  put(key, value) {
    if (this.cache.has(key)) {
      const node = this.cache.get(key);
      node.value = value;
      this.#moveToFront(node);
    } else {
      if (this.cache.size === this.capacity) {
        const lru = this.#removeLRU();
        this.cache.delete(lru.key);
      }
      const newNode = new Node(key, value);
      this.cache.set(key, newNode);
      this.#addNode(newNode);
    }
  }
}

// Driver code (capacity = 2)
const cache = new LRUCache(2);
cache.put(1, 1); // [1]
cache.put(2, 2); // [2, 1]
console.log(cache.get(1)); // 1, now [1, 2]
cache.put(3, 3); // evicts key 2 → [3, 1]
console.log(cache.get(2)); // -1
cache.put(4, 4); // evicts key 1 → [4, 3]
console.log(cache.get(1)); // -1
console.log(cache.get(3)); // 3
console.log(cache.get(4)); // 4
