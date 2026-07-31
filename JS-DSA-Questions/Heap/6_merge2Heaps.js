// Merge two heaps into a single max-heap.

// Approach:
// 1. Concatenate both heap arrays.
// 2. Build a max-heap from the combined array (heapify from the last non-leaf node down).
// Time: O(N + M). Space: O(N + M).

// JavaScript note: this file uses 0-based indexing (children at 2i+1 and 2i+2), so the last
// non-leaf node is at floor(n/2) - 1. Uses concat and destructuring swaps.
function heapify(arr, n, i) {
  let largest = i;
  const leftChildIndex = 2 * i + 1;
  const rightChildIndex = 2 * i + 2;

  if (leftChildIndex < n && arr[leftChildIndex] > arr[largest]) {
    largest = leftChildIndex;
  }
  if (rightChildIndex < n && arr[rightChildIndex] > arr[largest]) {
    largest = rightChildIndex;
  }

  if (largest !== i) {
    [arr[i], arr[largest]] = [arr[largest], arr[i]];
    heapify(arr, n, largest);
  }
}

function buildHeap(arr, n) {
  for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

function mergeHeaps(heap1, heap2) {
  const mergedHeap = heap1.concat(heap2);
  buildHeap(mergedHeap, mergedHeap.length);
  return mergedHeap;
}

const heap1 = [10, 5, 6, 2];
const heap2 = [12, 7, 9];
console.log("Merged Max-Heap:", mergeHeaps(heap1, heap2).join(" "));
