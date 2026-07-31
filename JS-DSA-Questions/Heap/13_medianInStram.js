// Find the median of a stream of integers (median after each new number).

// Key idea — two heaps:
//   maxHeap → the smaller half of the numbers (root = largest of the small half)
//   minHeap → the larger half of the numbers (root = smallest of the large half)
// Invariants:
//   - maxHeap.size() >= minHeap.size() and they differ by at most 1
//   - every element in maxHeap <= every element in minHeap
// Then the median is maxHeap top (odd count) or the average of both tops (even count).

// Approach:
// 1. Insert: if num <= maxHeap top, it goes to maxHeap (left half); else minHeap.
// 2. Rebalance so sizes differ by at most 1 and maxHeap is never smaller than minHeap.
// 3. Median: maxHeap top if maxHeap larger; else average of both tops.
// addNum: O(log n), findMedian: O(1).

// JavaScript note: no built-in priority queue, so we include a small BinaryHeap parameterized by a
// comparator (used as a max-heap and a min-heap).
class BinaryHeap {
  constructor(compare) {
    this.a = [];
    this.compare = compare; // returns >0 if a[p] should be swapped below a[i]
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
      if (this.compare(this.a[p], this.a[i]) > 0) {
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
        let best = i;
        if (l < n && this.compare(this.a[best], this.a[l]) > 0) best = l;
        if (r < n && this.compare(this.a[best], this.a[r]) > 0) best = r;
        if (best !== i) {
          [this.a[i], this.a[best]] = [this.a[best], this.a[i]];
          i = best;
        } else break;
      }
    }
    return top;
  }
}

class MedianFinder {
  constructor() {
    this.maxHeap = new BinaryHeap((x, y) => y - x); // max-heap (smaller half)
    this.minHeap = new BinaryHeap((x, y) => x - y); // min-heap (larger half)
  }

  addNum(num) {
    if (this.maxHeap.size() === 0 || num <= this.maxHeap.peek()) {
      this.maxHeap.push(num);
    } else {
      this.minHeap.push(num);
    }

    // Rebalance
    if (this.maxHeap.size() > this.minHeap.size() + 1) {
      this.minHeap.push(this.maxHeap.pop());
    } else if (this.minHeap.size() > this.maxHeap.size()) {
      this.maxHeap.push(this.minHeap.pop());
    }
  }

  findMedian() {
    if (this.maxHeap.size() > this.minHeap.size()) {
      return this.maxHeap.peek();
    }
    return (this.maxHeap.peek() + this.minHeap.peek()) / 2.0;
  }
}

// Driver code
const mf = new MedianFinder();
for (const num of [5, 15, 1, 3]) {
  mf.addNum(num);
  console.log("Current Median:", mf.findMedian());
}
// 5, 10, 5, 4
