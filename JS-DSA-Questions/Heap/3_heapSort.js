// Heap Sort.

// Approach:
// 1. Build a max-heap from the array.
// 2. The largest element is at the root; swap it with the last element of the heap.
// 3. Shrink the heap by one and heapify the root.
// 4. Repeat until the heap size is 1. The array ends up sorted ascending.
// Time Complexity: O(N log N).

// JavaScript note: 1-based indexing (index 0 placeholder), Math.floor for division, destructuring
// for swaps.
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
    heapify(arr, n, largest);
  }
}

function heapSort(arr, n) {
  // Build a max-heap
  for (let i = Math.floor(n / 2); i > 0; i--) {
    heapify(arr, n, i);
  }

  // Extract elements one by one
  for (let i = n; i > 1; i--) {
    [arr[1], arr[i]] = [arr[i], arr[1]]; // move current root to the end
    heapify(arr, i - 1, 1); // heapify the reduced heap
  }
}

// Example array (1-based indexing; index 0 placeholder)
const arr = [-1, 10, 20, 5, 6, 1, 8];
const n = 6;

heapSort(arr, n);
console.log("Sorted array:", arr.slice(1, n + 1).join(" ")); // 1 5 6 8 10 20

// Alternative: JavaScript has no built-in priority queue, but if you had a MaxHeap/PriorityQueue
// class you could push all elements and pop them to sort — analogous to the C++ priority_queue
// approach mentioned in the original file.
