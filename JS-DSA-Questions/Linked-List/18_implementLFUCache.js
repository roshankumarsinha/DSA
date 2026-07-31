// Implement an LFU (Least Frequently Used) Cache.

// Video Explanation: https://www.youtube.com/watch?v=0PSB9y8ehbk

// 📌 Problem: cache with (near) O(1) operations:
//    get(key)        – return value or -1
//    put(key, value) – insert/update; when full, evict the least frequently used key, breaking
//                      ties by the least recently used among that frequency.

// Intuition — track two things:
// 1. Frequency of each key.
// 2. Among keys with equal frequency, evict the least recently used → needs ordering.
// To support both quickly:
//    - A doubly linked list per frequency bucket (front = most recent, back = least recent).
//    - cacheMap: key -> node.
//    - freqMap: frequency -> { head, tail } dummy nodes of that bucket's DLL.
//    - minFreq: current minimum frequency (for eviction).

class Node {
  constructor(key, val) {
    this.key = key;
    this.value = val;
    this.cnt = 1; // frequency starts at 1
    this.prev = null;
    this.next = null;
  }
}

class LFUCache {
  constructor(capacity) {
    this.capacity = capacity;
    this.minFreq = 0;
    this.cacheMap = new Map(); // key -> Node
    this.freqMap = new Map(); // freq -> { head, tail }
  }

  get(key) {
    if (!this.cacheMap.has(key)) return -1;
    const node = this.cacheMap.get(key);
    const res = node.value;
    this.#updateFreq(node);
    return res;
  }

  put(key, value) {
    if (this.capacity === 0) return;

    if (this.cacheMap.has(key)) {
      const node = this.cacheMap.get(key);
      node.value = value;
      this.#updateFreq(node);
    } else {
      // Evict LRU of the minimum-frequency bucket if full
      if (this.cacheMap.size === this.capacity) {
        const { head, tail } = this.freqMap.get(this.minFreq);
        const node = tail.prev; // least recently used in this bucket
        this.cacheMap.delete(node.key);
        this.#remove(node);
        if (head.next === tail) {
          this.freqMap.delete(this.minFreq);
        }
      }

      const node = new Node(key, value);
      this.cacheMap.set(key, node);
      this.minFreq = 1;
      this.#add(node, 1);
    }
  }

  // Add a node to the front of the DLL for a given frequency
  #add(node, freq) {
    if (!this.freqMap.has(freq)) {
      const head = new Node(-1, -1); // dummy head
      const tail = new Node(-1, -1); // dummy tail
      head.next = tail;
      tail.prev = head;
      this.freqMap.set(freq, { head, tail });
    }

    const { head } = this.freqMap.get(freq);
    const temp = head.next;
    node.next = temp;
    node.prev = head;
    head.next = node;
    temp.prev = node;
  }

  // Detach a node from its DLL
  #remove(node) {
    const delprev = node.prev;
    const delnext = node.next;
    delprev.next = delnext;
    delnext.prev = delprev;
  }

  // Increase a node's frequency and move it to the correct bucket
  #updateFreq(node) {
    const oldFreq = node.cnt;
    node.cnt++;

    this.#remove(node);

    const { head, tail } = this.freqMap.get(oldFreq);
    if (head.next === tail) {
      this.freqMap.delete(oldFreq);
      if (this.minFreq === oldFreq) {
        this.minFreq++;
      }
    }

    this.#add(node, node.cnt);
  }
}

// Driver code
const cache = new LFUCache(2);
cache.put(1, 1);
cache.put(2, 2);
console.log(cache.get(1)); // 1
cache.put(3, 3); // evicts key 2 (freq 1, LRU)
console.log(cache.get(2)); // -1
cache.put(4, 4); // evicts key 3
console.log(cache.get(3)); // -1
console.log(cache.get(4)); // 4
