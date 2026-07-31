// Write a function for binary search.

// Binary Search finds an element's position in a SORTED array in O(log n) time.

// Video link : https://www.youtube.com/watch?v=TbbSJrY5GqQ&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=17

// How this works:
// 1. Divide the array into two halves and check whether the target is in the left or right half,
//    discarding the other half.
// 2. Each iteration discards half of the search space → O(log n).

function binarySearch(num, target) {
  let left = 0;
  let right = num.length - 1;
  while (left <= right) {
    // mid = left + (right - left)/2 avoids potential overflow of (left + right) in fixed-width
    // languages. In JS overflow isn't a concern until 2^53, but we keep the safe form. Use
    // Math.floor since JS division produces a float.
    const mid = left + Math.floor((right - left) / 2);
    if (num[mid] === target) {
      return mid;
    } else if (num[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

console.log(binarySearch([1, 2, 3, 4, 5, 6, 7, 8, 9], 5)); // 4
