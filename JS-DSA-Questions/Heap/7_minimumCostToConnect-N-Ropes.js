// Minimum cost to connect N ropes.
// Connecting two ropes costs the sum of their lengths. Connect all ropes into one with minimum
// total cost.

// Intuition (greedy): always combine the two SMALLEST ropes first. A min-heap gives the two
// smallest efficiently.

// Approach:
// 1. Push all lengths into a min-heap.
// 2. While more than one rope remains: pop the two smallest, add their sum to the total, push the
//    combined rope back.
// Time: O(N log N). Space: O(N).

// JavaScript note: JS has no built-in priority queue, so we include a small MinHeap class.
class MinHeap {
  constructor() {
    this.a = [];
  }
  size() {
    return this.a.length;
  }
  push(v) {
    this.a.push(v);
    let i = this.a.length - 1;
    while (i > 0) {
      const parent = Math.floor((i - 1) / 2);
      if (this.a[parent] > this.a[i]) {
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
        let smallest = i;
        if (l < n && this.a[l] < this.a[smallest]) smallest = l;
        if (r < n && this.a[r] < this.a[smallest]) smallest = r;
        if (smallest !== i) {
          [this.a[i], this.a[smallest]] = [this.a[smallest], this.a[i]];
          i = smallest;
        } else break;
      }
    }
    return top;
  }
}

function minCostToConnectRopes(arr) {
  const minHeap = new MinHeap();
  for (const len of arr) minHeap.push(len);

  let totalCost = 0;
  while (minHeap.size() > 1) {
    const first = minHeap.pop();
    const second = minHeap.pop();
    const cost = first + second;
    totalCost += cost;
    minHeap.push(cost);
  }

  return totalCost;
}

console.log("Minimum cost to connect ropes:", minCostToConnectRopes([4, 3, 2, 6])); // 29
