/*
    =====================================================
    NEXT PERMUTATION - Find Next Lexicographically Greater Permutation
    =====================================================

    Problem: Rearrange the numbers into the lexicographically next greater permutation.
    If not possible, rearrange to the lowest order (sorted ascending).

    Example:
    [1, 2, 3] → [1, 3, 2]
    [3, 2, 1] → [1, 2, 3]  (no greater, reset to smallest)
    [1, 3, 2] → [2, 1, 3]
    [2, 1, 5, 4, 3, 0, 0] → [2, 3, 0, 0, 1, 4, 5]

    =====================================================
    INTUITION / APPROACH:
    =====================================================
    1. Find break point: from right, first i where arr[i] < arr[i+1].
    2. If none → array is largest permutation → reverse the entire array.
    3. Find swap candidate: from right, first element > arr[breakPoint]. Swap them.
    4. Reverse the suffix after the break point (it's descending → becomes smallest).

    =====================================================
    TIME COMPLEXITY:  O(n)   SPACE COMPLEXITY: O(1) - in-place
    =====================================================
*/

// Helper to reverse a sub-range in place (JS reverse() only reverses the whole array).
function reverseRange(nums, l, r) {
  while (l < r) {
    [nums[l], nums[r]] = [nums[r], nums[l]];
    l++;
    r--;
  }
}

function nextPermutation(nums) {
  const n = nums.length;
  let breakPoint = -1;

  // Step 1: Find break point (rightmost i where nums[i] < nums[i+1])
  for (let i = n - 2; i >= 0; i--) {
    if (nums[i] < nums[i + 1]) {
      breakPoint = i;
      break;
    }
  }

  // Step 2: If no break point, reverse entire array (largest → smallest)
  if (breakPoint === -1) {
    reverseRange(nums, 0, n - 1);
    return;
  }

  // Step 3: Find swap candidate (rightmost element > nums[breakPoint])
  for (let j = n - 1; j > breakPoint; j--) {
    if (nums[j] > nums[breakPoint]) {
      [nums[breakPoint], nums[j]] = [nums[j], nums[breakPoint]];
      break;
    }
  }

  // Step 4: Reverse suffix (elements after break point)
  reverseRange(nums, breakPoint + 1, n - 1);
}

/*
    =====================================================
    ROTATE IMAGE BY 90 DEGREES (Clockwise)
    =====================================================

    Problem: Given an N x N 2D matrix, rotate it by 90 degrees clockwise, IN-PLACE.

    Example:
    1  2  3          7  4  1
    4  5  6    →     8  5  2
    7  8  9          9  6  3

    =====================================================
    INTUITION:
    =====================================================
    90° clockwise rotation = TRANSPOSE + REVERSE each row.
    - Transpose: (i, j) → (j, i)
    - Reverse row: (j, i) → (j, n-1-i)
    - Combined: (i, j) → (j, n-1-i)  ✓ matches the rotation formula.

    ROTATION VARIANTS:
    90° Clockwise:      Transpose → Reverse each ROW
    90° Anti-clockwise: Transpose → Reverse each COLUMN
    180°:               Reverse each ROW → Reverse each COLUMN

    =====================================================
    TIME COMPLEXITY:  O(n²)   SPACE COMPLEXITY: O(1) - in-place
    =====================================================
*/

function rotate90Clockwise(matrix) {
  const n = matrix.length;

  // Step 1: Transpose the matrix. Only iterate the upper triangle (j > i) to avoid
  // double-swapping.
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      [matrix[i][j], matrix[j][i]] = [matrix[j][i], matrix[i][j]];
    }
  }

  // Step 2: Reverse each row (JS arrays have a built-in reverse() for the whole row)
  for (let i = 0; i < n; i++) {
    matrix[i].reverse();
  }
}

// Driver code
const p = [2, 1, 5, 4, 3, 0, 0];
nextPermutation(p);
console.log("Next permutation:", p.join(" ")); // 2 3 0 0 1 4 5

const matrix = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9],
];
rotate90Clockwise(matrix);
console.log("Rotated 90°:", JSON.stringify(matrix)); // [[7,4,1],[8,5,2],[9,6,3]]
