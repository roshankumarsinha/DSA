// Find the kth smallest element in an array using a heap.

// Sorting would be O(N log N). Using a MAX-heap of size k, we can do it in O(N log K):
// 1. Push the first k elements into a max-heap.
// 2. For each remaining element, if it is smaller than the heap's max (root), pop the max and push
//    it. The heap always holds the k smallest elements seen; its root is the kth smallest.
// Space: O(K).

// JavaScript note: JS has NO built-in priority queue, so we include a small MaxHeap class here
// (0-based array binary heap). In interviews you'd either write one like this or use a library.
class MaxHeap {
  constructor() {
    this.a = [];
  }
  size() {
    return this.a.length;
  }
  peek() {
    return this.a[0];
  }
  push(v) {
    this.a.push(v);
    let i = this.a.length - 1;
    while (i > 0) {
      const parent = Math.floor((i - 1) / 2);
      if (this.a[parent] < this.a[i]) {
        [this.a[parent], this.a[i]] = [this.a[i], this.a[parent]];
        i = parent;
      } else break;
    }
  }
  pop() {
    const top = this.a[0];
    const last = this.a.pop();
    if (this.a.length > 0) {
      this.a[0] = last;
      let i = 0;
      const n = this.a.length;
      while (true) {
        const l = 2 * i + 1;
        const r = 2 * i + 2;
        let largest = i;
        if (l < n && this.a[l] > this.a[largest]) largest = l;
        if (r < n && this.a[r] > this.a[largest]) largest = r;
        if (largest !== i) {
          [this.a[i], this.a[largest]] = [this.a[largest], this.a[i]];
          i = largest;
        } else break;
      }
    }
    return top;
  }
}

function kthSmallest(arr, k) {
  const maxHeap = new MaxHeap();

  for (let i = 0; i < k; i++) {
    maxHeap.push(arr[i]);
  }

  for (let i = k; i < arr.length; i++) {
    if (arr[i] < maxHeap.peek()) {
      maxHeap.pop();
      maxHeap.push(arr[i]);
    }
  }

  return maxHeap.peek();
}

const arr = [7, 10, 4, 3, 20, 15];
const k = 3;
console.log(`The ${k}rd smallest element is ${kthSmallest(arr, k)}`); // 7
