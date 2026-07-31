// Find the single element in an array where every element appears twice except one, which
// appears only once.

// Note: This code does not rely on the array being sorted for correctness of the "single element"
// property, but the O(log n) binary-search version below DOES require the array to be sorted so
// that pairs sit adjacently.

// Example:
// Input : nums = [1, 1, 2, 3, 3, 4, 4, 8, 8] → Output: 2

// Video link : https://www.youtube.com/watch?v=qsbCBduIs40&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=20

// Intuition:
// 1. Total number of elements is always odd.
// 2. If mid is even: even count on both sides.
//    a. If nums[mid] === nums[mid-1], the single element is on the left; else on the right.
// 3. If mid is odd:
//    a. If nums[mid] === nums[mid-1], the single element is on the right; else on the left.

// Time Complexity: O(log n). Space Complexity: O(1).

function singleElement(nums) {
  const length = nums.length;

  // Single element in the array
  if (length === 1) return nums[0];

  let start = 0;
  let end = length - 1;
  while (start <= end) {
    const mid = start + Math.floor((end - start) / 2);

    // Single element is the first element (guard mid - 1)
    if (mid === 0 && nums[mid] !== nums[1]) return nums[mid];
    // Single element is the last element (guard mid + 1)
    else if (mid === length - 1 && nums[mid] !== nums[length - 2]) return nums[mid];
    // Single element found in the middle
    else if (nums[mid] !== nums[mid - 1] && nums[mid] !== nums[mid + 1]) return nums[mid];
    // Case 1: mid is even
    else if (mid % 2 === 0) {
      if (nums[mid] === nums[mid - 1]) {
        end = mid - 1; // single element on the left
      } else {
        start = mid + 1; // single element on the right
      }
    }
    // Case 2: mid is odd
    else {
      if (nums[mid] === nums[mid - 1]) {
        start = mid + 1; // single element on the right
      } else {
        end = mid - 1; // single element on the left
      }
    }
  }
  return -1;
}

console.log(singleElement([1, 1, 2, 3, 3, 4, 4, 8, 8])); // 2
