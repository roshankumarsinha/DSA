/*
    =====================================================
    FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY
    =====================================================

    Problem: Given a sorted array of integers and a target value, find the starting and ending
    position of the target. If not found, return [-1, -1]. Must run in O(log n).

    Example:
    nums = [5, 7, 7, 8, 8, 10], target = 8 → [3, 4]
    nums = [5, 7, 7, 8, 8, 10], target = 6 → [-1, -1]
    nums = [1], target = 1 → [0, 0]

    =====================================================
    INTUITION:
    =====================================================
    Since the array is sorted, use BINARY SEARCH twice:

    1. Lower Bound (First Occurrence): when we find target, keep searching LEFT (right = mid - 1),
       storing the answer each time.
    2. Upper Bound (Last Occurrence): when we find target, keep searching RIGHT (left = mid + 1),
       storing the answer each time.

    =====================================================
    TIME COMPLEXITY:  O(log n)   SPACE COMPLEXITY: O(1)
    =====================================================
*/

function findFirst(nums, target) {
  let left = 0;
  let right = nums.length - 1;
  let ans = -1;

  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);

    if (nums[mid] === target) {
      ans = mid;
      right = mid - 1; // keep searching LEFT for an earlier occurrence
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return ans;
}

function findLast(nums, target) {
  let left = 0;
  let right = nums.length - 1;
  let ans = -1;

  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);

    if (nums[mid] === target) {
      ans = mid;
      left = mid + 1; // keep searching RIGHT for a later occurrence
    } else if (nums[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return ans;
}

function searchRange(nums, target) {
  return [findFirst(nums, target), findLast(nums, target)];
}

console.log(searchRange([5, 7, 7, 8, 8, 10], 8)); // [3, 4]
console.log(searchRange([5, 7, 7, 8, 8, 10], 6)); // [-1, -1]
