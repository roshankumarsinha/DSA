// Find the smallest range that includes at least one element from each of k sorted arrays.

// Approach 2 (Min-Heap) — the optimized one:
// 1. Push the first element of each array into a min-heap; track currentMax of pushed elements.
// 2. The current range is [heap.min, currentMax]. Record it if smaller.
// 3. Pop the min, and push the next element from the SAME array (updating currentMax). This tries
//    to shrink the range from the low end.
// 4. Stop when any array is exhausted (we can no longer cover that array).
// Time: O(N log K). Space: O(K).

// (Approach 1 uses k pointers directly: O(K^2 * N). See the original file's commented version.)

// JavaScript note: uses a comparator-based MinHeap; Infinity/-Infinity replace INT_MAX/INT_MIN.
class MinHeap {
  constructor(compare) {
    this.a = [];
    this.compare = compare;
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

function smallestRange(nums) {
  const k = nums.length;
  // Heap items: { value, row, col }
  const minHeap = new MinHeap((x, y) => x.value - y.value);
  let currentMax = -Infinity;

  for (let i = 0; i < k; i++) {
    minHeap.push({ value: nums[i][0], row: i, col: 0 });
    currentMax = Math.max(currentMax, nums[i][0]);
  }

  let rangeStart = 0;
  let rangeEnd = Infinity;

  while (minHeap.size() > 0) {
    const currentNode = minHeap.pop();
    const currentMin = currentNode.value;

    if (currentMax - currentMin < rangeEnd - rangeStart) {
      rangeStart = currentMin;
      rangeEnd = currentMax;
    }

    if (currentNode.col + 1 < nums[currentNode.row].length) {
      const nextValue = nums[currentNode.row][currentNode.col + 1];
      minHeap.push({ value: nextValue, row: currentNode.row, col: currentNode.col + 1 });
      currentMax = Math.max(currentMax, nextValue);
    } else {
      break; // an array is exhausted
    }
  }

  return [rangeStart, rangeEnd];
}

const nums = [
  [4, 10, 15, 24, 26],
  [0, 9, 12, 20],
  [5, 18, 22, 30],
];
const [start, end] = smallestRange(nums);
console.log(`Smallest range: [${start}, ${end}]`); // [20, 24]
