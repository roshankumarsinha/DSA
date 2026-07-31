// Merge k sorted arrays into a single sorted array.

// Approach (Min-Heap):
// 1. Push the first element of each array into a min-heap, along with its (arrayIndex, elemIndex).
// 2. Pop the smallest; append to the result; push the next element from the same array (if any).
// 3. Repeat until the heap is empty.
// Time: O(N*k log k). Space: O(k) for the heap (plus the output).

// JavaScript note: C++ used priority_queue of pair<int,pair<int,int>> with a custom comparator.
// Here we include a comparator-based MinHeap that orders by the stored value.
class MinHeap {
  constructor(compare) {
    this.a = [];
    this.compare = compare; // returns negative if a should come before b
  }
  size() {
    return this.a.length;
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
        let s = i;
        if (l < n && this.compare(this.a[l], this.a[s]) < 0) s = l;
        if (r < n && this.compare(this.a[r], this.a[s]) < 0) s = r;
        if (s !== i) {
          [this.a[i], this.a[s]] = [this.a[s], this.a[i]];
          i = s;
        } else break;
      }
    }
    return top;
  }
}

function mergeKSortedArrays(arrays) {
  // Each heap item: { value, row, col }
  const minHeap = new MinHeap((x, y) => x.value - y.value);
  const result = [];

  for (let i = 0; i < arrays.length; i++) {
    if (arrays[i].length > 0) {
      minHeap.push({ value: arrays[i][0], row: i, col: 0 });
    }
  }

  while (minHeap.size() > 0) {
    const { value, row, col } = minHeap.pop();
    result.push(value);

    if (col + 1 < arrays[row].length) {
      minHeap.push({ value: arrays[row][col + 1], row, col: col + 1 });
    }
  }

  return result;
}

const arrays = [
  [1, 4, 7],
  [2, 5, 8],
  [3, 6, 9],
];
console.log("Merged sorted array:", mergeKSortedArrays(arrays).join(" ")); // 1 2 3 4 5 6 7 8 9
