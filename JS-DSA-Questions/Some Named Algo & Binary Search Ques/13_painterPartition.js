// 🧩 Painter's Partition Problem
// You are given:
//  1.  n boards of different lengths: arr[]
//  2.  k painters
//  3.  Time to paint 1 unit of board = 1 unit
// Each painter can only paint CONTIGUOUS boards, and painters work in parallel.
// Goal: Assign boards to k painters so that the time to paint all boards is minimized.

// Notes : https://takeuforward.org/arrays/painters-partition-problem/

// Example: arr = [10, 20, 30, 40], k = 2 → Output: 60
// (Painter 1: 10+20+30 = 60, Painter 2: 40. Max = 60, minimized.)

// 🧩 Split Array Largest Sum (identical problem)
// Split nums[] into k non-empty contiguous subarrays such that the maximum subarray sum is
// minimized. Example: arr = [10, 20, 30, 40], k = 2 → 60.
// Notes : https://takeuforward.org/arrays/split-array-largest-sum/

// All three problems (Painter's Partition, Split Array Largest Sum, Allocate Minimum Number of
// Pages) are the SAME binary-search-on-answer pattern. Whenever a problem asks to "minimize the
// maximum", think of the Allocate Minimum Number of Pages approach.

// Implementation (same as book allocation): binary search the answer between max(arr) and sum(arr),
// counting how many painters are needed for a given max time.
function countPainters(boards, maxTime) {
  let painters = 1;
  let timeAllocated = 0;

  for (let i = 0; i < boards.length; i++) {
    if (timeAllocated + boards[i] <= maxTime) {
      timeAllocated += boards[i];
    } else {
      painters++;
      timeAllocated = boards[i];
    }
  }

  return painters;
}

function painterPartition(boards, k) {
  let low = boards[0];
  let high = boards[0];
  for (let i = 1; i < boards.length; i++) {
    low = Math.max(low, boards[i]);
    high += boards[i];
  }

  let result = -1;
  while (low <= high) {
    const mid = low + Math.floor((high - low) / 2);
    if (countPainters(boards, mid) > k) {
      low = mid + 1; // mid too small; need more painters than allowed
    } else {
      result = mid; // candidate; try to minimize further
      high = mid - 1;
    }
  }
  return result;
}

console.log(painterPartition([10, 20, 30, 40], 2)); // 60
