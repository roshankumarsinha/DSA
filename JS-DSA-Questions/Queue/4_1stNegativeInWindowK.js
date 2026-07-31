// Return the first negative number in every window of size k. If a window has no negative number,
// use 0 for that window.

// Example:
// Input: arr = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
// Output: [-1, -1, -7, -15, -15, 0]

// Approach:
// 1. Use a queue (deque) to store the INDICES of negative numbers in the current window.
// 2. Slide the window one element at a time:
//    a. Add the current index if the element is negative.
//    b. Remove front indices that fall outside the current window.
// 3. For each window, the first index in the queue is the first negative number (0 if empty).

// JavaScript note: C++ used std::deque. In JS a plain array with push()/shift() works as a queue.
// (shift() is O(n) in the worst case, but for clarity we use it here; for large inputs use a
// pointer-based deque.)
function firstNegativeInteger(arr, k) {
  const n = arr.length;
  const negatives = []; // indices of negative numbers
  const result = [];

  // Process the first window
  for (let i = 0; i < k; i++) {
    if (arr[i] < 0) {
      negatives.push(i);
    }
  }
  result.push(negatives.length === 0 ? 0 : arr[negatives[0]]);

  // Process remaining windows
  for (let i = k; i < n; i++) {
    // Remove indices that are out of the current window
    if (negatives.length > 0 && i - negatives[0] >= k) {
      negatives.shift();
    }

    // Add the current index if negative
    if (arr[i] < 0) {
      negatives.push(i);
    }

    result.push(negatives.length === 0 ? 0 : arr[negatives[0]]);
  }

  console.log(result.join(" "));
  return result;
}

const arr = [12, -1, -7, 8, -15, 30, 16, 28];
const k = 3;
console.log(`First negative integers in every window of size ${k}:`);
firstNegativeInteger(arr, k); // -1 -1 -7 -15 -15 0

// Time Complexity: O(n). Space Complexity: O(k) for the deque.
// An O(1) extra-space variant tracks the index of the first negative in the current window and
// only re-scans when that index falls outside the window.
