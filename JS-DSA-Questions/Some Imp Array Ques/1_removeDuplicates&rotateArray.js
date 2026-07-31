/*
    =====================================================
    REMOVE DUPLICATES IN-PLACE FROM SORTED ARRAY
    =====================================================

    Problem: Given a sorted array, remove the duplicates in-place such that each element appears only once and return the new length.

    =====================================================
    INTUITION:
    =====================================================
    Since the array is SORTED, all duplicate elements are ADJACENT to each other.

    We can use the TWO-POINTER technique:
    - One pointer (i) to track the position where the next unique element should go
    - Another pointer (j) to scan through the array

    Key Insight: We only need to compare adjacent elements. If they're different,
    we've found a new unique element.

    =====================================================
    APPROACH:
    =====================================================
    1. Use pointer 'i' starting at index 0 (first unique element position)
    2. Use pointer 'j' to iterate from index 1 to end
    3. If arr[j] != arr[i], we found a new unique element:
       - Increment i
       - Place arr[j] at position i
    4. Return i + 1 (length of unique elements)

    =====================================================
    EXAMPLE DRY RUN:
    =====================================================
    Input: [1, 1, 2, 2, 2, 3, 3]
    After processing, first 3 elements [1, 2, 3] are unique. Return 3.

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through array
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

function removeDuplicates(nums) {
  // Edge case: empty array
  if (nums.length === 0) return 0;

  // 'i' points to the last unique element's position
  let i = 0;

  // 'j' scans through the array starting from index 1
  for (let j = 1; j < nums.length; j++) {
    // If current element is different from the last unique element
    if (nums[j] !== nums[i]) {
      i++; // Move to next position for unique element
      nums[i] = nums[j]; // Place the new unique element
    }
  }

  // Return count of unique elements (i is index, so add 1)
  return i + 1;
}

/*
    =====================================================
    ROTATE ARRAY BY K ELEMENTS
    =====================================================

    Problem: Given an array of integers, rotate the array by k elements
    either left or right.

    =====================================================
    INTUITION:
    =====================================================
    Rotating an array can be achieved using the REVERSAL ALGORITHM.

    For RIGHT ROTATION by k:
    - Reverse the entire array
    - Reverse first k elements to fix their order
    - Reverse remaining elements to fix their order

    For LEFT ROTATION by k:
    - Reverse first k elements
    - Reverse remaining n-k elements
    - Reverse entire array

    =====================================================
    EXAMPLE (Right Rotation by k=3):
    [1, 2, 3, 4, 5, 6, 7] → [5, 6, 7, 1, 2, 3, 4]

    EXAMPLE (Left Rotation by k=2):
    [1, 2, 3, 4, 5] → [3, 4, 5, 1, 2]

    =====================================================
    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

// JavaScript note: C++ used std::reverse(begin, end) on an iterator range. JS arrays have a
// built-in reverse(), but it reverses the WHOLE array only. To reverse a sub-range in place
// we write a small helper using two pointers (l and r) — the same idea as the C++ iterators.
function reverseRange(nums, l, r) {
  while (l < r) {
    [nums[l], nums[r]] = [nums[r], nums[l]];
    l++;
    r--;
  }
}

// Right Rotation by k elements
function rotateRight(nums, k) {
  const n = nums.length;
  if (n === 0) return;

  k = k % n; // Handle k > n
  if (k === 0) return;

  reverseRange(nums, 0, n - 1); // Step 1: Reverse entire array
  reverseRange(nums, 0, k - 1); // Step 2: Reverse first k elements
  reverseRange(nums, k, n - 1); // Step 3: Reverse remaining n-k elements
}

// Left Rotation by k elements
function rotateLeft(nums, k) {
  const n = nums.length;
  if (n === 0) return;

  k = k % n; // Handle k > n
  if (k === 0) return;

  reverseRange(nums, 0, k - 1); // Step 1: Reverse first k elements
  reverseRange(nums, k, n - 1); // Step 2: Reverse remaining n-k elements
  reverseRange(nums, 0, n - 1); // Step 3: Reverse entire array
}

// Driver code
const a = [1, 1, 2, 2, 2, 3, 3];
console.log("Unique length:", removeDuplicates(a), "->", a.slice(0, 3)); // 3 -> [1,2,3]

const r = [1, 2, 3, 4, 5, 6, 7];
rotateRight(r, 3);
console.log("Rotate right by 3:", r.join(" ")); // 5 6 7 1 2 3 4

const l = [1, 2, 3, 4, 5];
rotateLeft(l, 2);
console.log("Rotate left by 2:", l.join(" ")); // 3 4 5 1 2
