// Find the kth largest sum among all contiguous subarrays.

// Example: arr = [20, -5, -1], k = 3
// Subarray sums: 20, 15, 14, -5, -6, -1 → sorted desc: 20, 15, 14, -1, -5, -6 → 3rd largest = 14.

// Approach (min-heap of size k):
// 1. Enumerate all subarray sums with two loops.
// 2. Keep a min-heap of size k: if the heap has < k items push; else if the current sum is larger
//    than the heap's min, pop and push. The heap's root is the kth largest sum.
// Time: O(N^2 log K). Space: O(K).

// JavaScript note: no built-in priority queue, so we include a small numeric MinHeap.
class MinHeap {
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
      const p = Math.floor((i - 1) / 2);
      if (this.a[p] > this.a[i]) {
        [this.a[p], this.a[i]] = [this.a[i], this.a[p]];
        i = p;
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
        let s = i;
        if (l < n && this.a[l] < this.a[s]) s = l;
        if (r < n && this.a[r] < this.a[s]) s = r;
        if (s !== i) {
          [this.a[i], this.a[s]] = [this.a[s], this.a[i]];
          i = s;
        } else break;
      }
    }
    return top;
  }
}

function kthLargestSumSubarray(arr, k) {
  const minHeap = new MinHeap();
  const n = arr.length;

  for (let i = 0; i < n; i++) {
    let sum = 0;
    for (let j = i; j < n; j++) {
      sum += arr[j];
      if (minHeap.size() < k) {
        minHeap.push(sum);
      } else if (sum > minHeap.peek()) {
        minHeap.pop();
        minHeap.push(sum);
      }
    }
  }

  return minHeap.peek();
}

console.log("The 3rd largest sum of a subarray is:", kthLargestSumSubarray([20, -5, -1], 3)); // 14
