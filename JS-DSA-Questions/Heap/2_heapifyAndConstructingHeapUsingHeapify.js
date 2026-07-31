// Heapify to maintain the max-heap property, and build a max-heap from an array.

// Heapify(arr, n, i): assuming the subtrees below index i are valid heaps, push the value at i
// down until the max-heap property holds from i downward.
// Approach:
// 1. Compare arr[i] with its children (2i and 2i+1 in 1-based indexing).
// 2. Swap with the larger child if a child is bigger, then recurse into that subtree.

// Build heap: call heapify from the last non-leaf node (n/2) down to the root (1).
// Time Complexity: O(N) overall (not O(N log N)) — most nodes are near the bottom and do little
// work; the geometric series of work sums to O(N).

// JavaScript note: uses 1-based indexing (index 0 holds a placeholder, here -1) to mirror the C++
// version, and Math.floor for integer division.
function heapify(arr, n, i) {
  let largest = i;
  const leftChildIndex = 2 * i;
  const rightChildIndex = 2 * i + 1;

  if (leftChildIndex <= n && arr[leftChildIndex] > arr[largest]) {
    largest = leftChildIndex;
  }
  if (rightChildIndex <= n && arr[rightChildIndex] > arr[largest]) {
    largest = rightChildIndex;
  }

  if (largest !== i) {
    [arr[i], arr[largest]] = [arr[largest], arr[i]];
    heapify(arr, n, largest); // recursively fix the affected subtree
  }
}

function buildHeap(arr, n) {
  // Start from the last non-leaf node (n/2) and heapify down to the root
  for (let i = Math.floor(n / 2); i > 0; i--) {
    heapify(arr, n, i);
  }
}

// Example array (1-based indexing; index 0 is a placeholder)
const arr = [-1, 10, 20, 5, 6, 1, 8];
const n = 6;

buildHeap(arr, n);
console.log("Max-Heap array:", arr.slice(1, n + 1).join(" "));
