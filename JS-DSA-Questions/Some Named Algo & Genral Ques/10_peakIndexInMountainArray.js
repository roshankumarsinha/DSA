// Find the peak index in a mountain array. The input is guaranteed to be a mountain array
// (at least 3 elements), so there is always exactly one peak.

// A mountain array strictly increases, then strictly decreases. Find the index of the peak.

// Video link : https://www.youtube.com/watch?v=cXxmbemS6XM
// Notes link : https://takeuforward.org/data-structure/peak-element-in-array

// Example: num = [1, 2, 3, 4, 5, 4, 3, 2] → Output: 4

// How this works:
// 1. Use binary search. Start left = 1 and right = n-2 (the peak can't be at the first or last
//    index, and this keeps num[mid-1]/num[mid+1] in bounds).
// 2. If num[mid] > both neighbors, it's the peak.
// 3. If num[mid] < num[mid+1], we're on the ascending slope → go right.
// 4. Else we're on the descending slope → go left.
// O(log n).

function peakIndexInMountainArray(num) {
  let left = 1; // peak can't be at index 0
  let right = num.length - 2; // peak can't be at the last index
  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    if (num[mid] > num[mid - 1] && num[mid] > num[mid + 1]) {
      return mid;
    } else if (num[mid] < num[mid + 1]) {
      left = mid + 1; // ascending slope
    } else {
      right = mid - 1; // descending slope
    }
  }
  return -1;
}

console.log(peakIndexInMountainArray([1, 2, 3, 4, 5, 4, 3, 2, 1])); // 4

// Modified version: general "Find Peak Element" where an element is a peak if it's strictly
// greater than both neighbors, imagining nums[-1] = nums[n] = -Infinity. If multiple peaks
// exist, return any peak's index.
//
// Intuition:
// 1. Handle single element (return 0).
// 2. If arr[0] > arr[1], index 0 is a peak.
// 3. If arr[n-1] > arr[n-2], index n-1 is a peak.
// 4. Otherwise binary search on [1, n-2]; the increasing/decreasing check still leads to a peak.
function peakElementInArray(arr) {
  const n = arr.length;
  if (n === 1) return 0;
  if (arr[0] > arr[1]) return 0;
  if (arr[n - 1] > arr[n - 2]) return n - 1;

  let left = 1;
  let right = n - 2;

  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
      return mid;
    } else if (arr[mid] < arr[mid + 1]) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1; // never reached — a peak always exists
}
