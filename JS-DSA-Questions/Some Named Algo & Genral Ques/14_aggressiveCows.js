// 🧩 Aggressive Cows
// You are given:
//  1.  An array stalls[] of positions of n stalls along a straight line.
//  2.  An integer k, the number of cows.
// Goal: Place k cows in the stalls so that the MINIMUM distance between any two cows is MAXIMIZED.

// Notes link : https://takeuforward.org/data-structure/aggressive-cows-detailed-solution/
// Video link : https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0pMFMWuuvDNMAkoQFi-h0ZF&index=18

// Example: stalls = [0, 3, 4, 7, 10, 9], k = 4 → Output: 3
// (Place cows at 0, 3, 7, 10; consecutive gaps are 3, 4, 3; the minimum is 3.)

// Sort the stalls first — the minimum distance always comes from two consecutive placed cows.
// This is another "maximize the minimum" binary-search-on-answer problem (like Allocate Pages).

// JavaScript note: sort numerically with (a, b) => a - b. stalls[stalls.length-1] and stalls[0]
// replace C++ .back()/.front().
function countCows(stalls, minDist) {
  let count = 1; // first cow at the first stall
  let lastPosition = stalls[0];
  for (let i = 1; i < stalls.length; i++) {
    if (stalls[i] - lastPosition >= minDist) {
      count++; // place a cow here
      lastPosition = stalls[i];
    }
  }
  return count;
}

function aggressiveCows(stalls, k) {
  stalls.sort((a, b) => a - b);
  let left = 1; // minimum possible distance
  let right = stalls[stalls.length - 1] - stalls[0]; // maximum possible distance
  let result = 0;
  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    const cowsPlaced = countCows(stalls, mid);
    if (cowsPlaced >= k) {
      result = mid; // feasible; try a larger minimum distance
      left = mid + 1;
    } else {
      right = mid - 1; // not feasible; try a smaller distance
    }
  }
  return result;
}

console.log(aggressiveCows([0, 3, 4, 7, 10, 9], 4)); // 3

// Time Complexity: O(N log N) + O(N * log(maxDistance)). Space Complexity: O(1).
