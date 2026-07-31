// The 3 Sum problem asks you to find all unique triplets in an array that sum up to a given
// target value (usually zero).

// Approach and Intuition: (Fix one element and use two pointers for the other two)
// 1. Sorting: sort the array to easily skip duplicates and apply two pointers.
// 2. Fix nums[i], then find two numbers summing to -nums[i] using two pointers.
// 3. Two-pointer technique with left = i+1 and right = n-1:
//    a. If sum < 0, move left right (need larger sum).
//    b. If sum > 0, move right left (need smaller sum).
//    c. If sum == 0, record the triplet and move both pointers inward.
// 4. Avoid duplicates: skip repeated values for nums[i], nums[left], and nums[right].

// JavaScript note: sort numbers with (a, b) => a - b (default sort is lexicographic).
function threeSum(nums) {
  const result = [];
  const n = nums.length;

  // Step 1: Sort the array
  nums.sort((a, b) => a - b);

  // Step 2: Iterate; we need at least 3 elements, so go up to n-2
  for (let i = 0; i < n - 2; i++) {
    // Skip duplicate first elements
    if (i > 0 && nums[i] === nums[i - 1]) continue;

    let left = i + 1;
    let right = n - 1;

    // Step 3: Two-pointer search
    while (left < right) {
      const sum = nums[i] + nums[left] + nums[right];

      if (sum < 0) {
        left++; // need a larger sum
      } else if (sum > 0) {
        right--; // need a smaller sum
      } else {
        // Found a triplet
        result.push([nums[i], nums[left], nums[right]]);

        left++;
        right--;

        // Skip duplicates for the second and third elements
        while (left < right && nums[left] === nums[left - 1]) left++;
        while (left < right && nums[right] === nums[right + 1]) right--;
      }
    }
  }
  return result;
}

console.log(threeSum([-1, 0, 1, 2, -1, -4])); // [[-1,-1,2],[-1,0,1]]

// Time Complexity: O(n^2). Space Complexity: O(1) (not counting output).
// The 4 Sum problem is similar, but there we fix two elements and use two pointers for the rest.
