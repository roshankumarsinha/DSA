// Write a function for binary search in a rotated array.

// You are given a sorted array rotated at an unknown pivot. Given a target, return its index or -1.

// Input: nums = [4,5,6,7,0,1,2], target = 0 → Output: 4

// Video link : https://www.youtube.com/watch?v=6WNZQBHWQJs&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=18

// 🧠 Intuition:
// Even though the array is rotated, at least one half (left or right) is always sorted.
// Use that fact to decide where to search.

// How this works:
// 1. In a rotated array, one half must be sorted.
// 2. If the left half is sorted, check whether the target lies within it; search accordingly.
// 3. If the right half is sorted, check whether the target lies within it; search accordingly.

function binarySearchInRotatedArray(num, target) {
  let left = 0;
  let right = num.length - 1;
  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    if (num[mid] === target) {
      return mid;
    } else if (num[left] <= num[mid]) {
      // Left half is sorted
      if (num[left] <= target && target <= num[mid]) {
        right = mid - 1; // target is in the left half
      } else {
        left = mid + 1; // search the right half
      }
    } else {
      // Right half is sorted
      if (num[mid] < target && target <= num[right]) {
        left = mid + 1; // target is in the right half
      } else {
        right = mid - 1; // search the left half
      }
    }
  }
  return -1;
}

console.log(binarySearchInRotatedArray([4, 5, 6, 7, 0, 1, 2], 0)); // 4

// Variant: Search in a rotated sorted array WITH duplicates.
// Same logic, but when num[left] === num[mid] === num[right] we can't tell which side is sorted,
// so we shrink both ends (left++, right--) to avoid an infinite loop:
//
// if (num[left] === num[mid] && num[mid] === num[right]) {
//   left++;
//   right--;
//   continue;
// }
//
// Notes: https://takeuforward.org/arrays/search-element-in-rotated-sorted-array-ii/
