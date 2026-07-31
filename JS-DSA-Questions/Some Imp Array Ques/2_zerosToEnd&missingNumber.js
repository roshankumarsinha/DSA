/*
    =====================================================
    MOVE ALL ZEROS TO THE END OF ARRAY
    =====================================================

    Problem: Given an array of integers, move all zeros to the end while
    maintaining the relative order of non-zero elements.

    =====================================================
    INTUITION:
    =====================================================
    We use the TWO-POINTER technique:
    - One pointer (i) tracks the position where the next non-zero element should go
    - Another pointer (j) scans through the array looking for non-zero elements

    Key Insight: Instead of "moving zeros to end", think of it as
    "moving non-zeros to front" — zeros will naturally end up at the back.

    =====================================================
    APPROACH:
    =====================================================
    1. Use pointer 'i' starting at 0 (position for next non-zero)
    2. Use pointer 'j' to iterate through the array
    3. If arr[j] is non-zero: swap arr[i] and arr[j], increment i
    4. After loop, all non-zeros are at front, zeros at end

    EXAMPLE: [0, 1, 0, 3, 12] → [1, 3, 12, 0, 0]

    =====================================================
    TIME COMPLEXITY:  O(n) - Single pass through array
    SPACE COMPLEXITY: O(1) - In-place modification
    =====================================================
*/

function moveZeroes(nums) {
  let i = 0; // Position for next non-zero element

  for (let j = 0; j < nums.length; j++) {
    if (nums[j] !== 0) {
      // Swap using array destructuring (JS idiom for std::swap)
      [nums[i], nums[j]] = [nums[j], nums[i]];
      i++;
    }
  }
}

/*
    =====================================================
    FIND THE MISSING NUMBER IN AN ARRAY
    =====================================================

    Problem: Given an integer N and an array of size N-1 containing N-1
    numbers between 1 to N. Find the number (between 1 to N) not present.

    =====================================================
    INTUITION:
    =====================================================

    Approach 1: SUM FORMULA
    - Sum of 1..N = N * (N + 1) / 2. Subtract the array sum to get the missing number.
    - Simple, but can overflow for very large N in fixed-width languages.
      (In JavaScript all numbers are 64-bit doubles, so overflow is far less of a concern
      until values exceed Number.MAX_SAFE_INTEGER = 2^53 - 1.)

    Approach 2: XOR (Preferred)
    - XOR properties: a ^ a = 0, a ^ 0 = a, and XOR is associative & commutative.
    - XOR of 1..N XORed with XOR of all array elements leaves only the missing number.

    EXAMPLE: N = 5, Array = [1, 2, 4, 5] → missing is 3

    =====================================================
    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
    =====================================================
*/

// Method 1: Using Sum Formula
function missingNumberSum(nums, n) {
  const expectedSum = (n * (n + 1)) / 2;
  let actualSum = 0;
  for (const num of nums) {
    actualSum += num;
  }
  return expectedSum - actualSum;
}

// Method 2: Using XOR (Preferred)
// JavaScript note: the ^ operator works on 32-bit integers, which is fine here since the
// values 1..N are small. XOR both ranges; matching numbers cancel, leaving the missing one.
function missingNumberXOR(nums, n) {
  let xor1 = 0; // XOR of 1 to N
  let xor2 = 0; // XOR of array elements

  for (let i = 1; i <= n; i++) {
    xor1 ^= i;
  }
  for (const num of nums) {
    xor2 ^= num;
  }
  return xor1 ^ xor2;
}

// Driver code
const arr = [0, 1, 0, 3, 12];
moveZeroes(arr);
console.log("Move zeroes:", arr.join(" ")); // 1 3 12 0 0

console.log("Missing (sum):", missingNumberSum([1, 2, 4, 5], 5)); // 3
console.log("Missing (xor):", missingNumberXOR([1, 2, 4, 5], 5)); // 3
