// Given an integer array arr sorted in ascending order (distinct values), rotated at an unknown
// index, find the minimum element. (The pivot element is the minimum in a rotated sorted array.)

// Intuition:
// 1. In a rotated sorted array, one half is always sorted.
// 2. Compare arr[left] and arr[mid] to find which half is sorted.
// 3. The first element of the sorted half is a candidate for the minimum — record it.
// 4. Discard that half and continue searching the other half.
// 5. Repeat while left <= right.

// JavaScript note: C++ used INT_MAX as the initial answer; here we use Infinity.
function findMinInRotatedArray(arr) {
  let left = 0;
  let right = arr.length - 1;
  let ans = Infinity;

  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);

    if (arr[left] <= arr[mid]) {
      // Left half is sorted; its first element is the smallest here
      ans = Math.min(ans, arr[left]);
      left = mid + 1; // discard the left half
    } else {
      // Right half is sorted; arr[mid] is the smallest here
      ans = Math.min(ans, arr[mid]);
      right = mid - 1; // discard the right half
    }
  }

  return ans;
}

console.log("Minimum element:", findMinInRotatedArray([4, 5, 6, 7, 0, 1, 2])); // 0

// Time Complexity: O(log N). Space Complexity: O(1).
