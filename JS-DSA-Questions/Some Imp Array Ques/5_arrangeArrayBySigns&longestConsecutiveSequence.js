/*
    =====================================================
    REARRANGE ARRAY ELEMENTS BY SIGN
    =====================================================

    Problem: Given an array with equal number of positive and negative elements,
    rearrange them in alternating positive-negative order while maintaining
    their relative order.

    This is almost like "Move All Zeros to End", but instead of zeros we deal with
    positive and negative numbers, and we preserve relative order.

    Example:
    Input:  [3, 1, -2, -5, 2, -4]
    Output: [3, -2, 1, -5, 2, -4]

    =====================================================
    INTUITION:
    =====================================================
    Alternating pattern starting with positive:
    - Positive elements go to even indices: 0, 2, 4, ...
    - Negative elements go to odd indices: 1, 3, 5, ...

    Use TWO POINTERS: posIndex = 0, negIndex = 1, each incremented by 2.

    =====================================================
    TIME COMPLEXITY:  O(n)   SPACE COMPLEXITY: O(n) - result array
    =====================================================
*/

// JavaScript note: `new Array(n).fill(0)` pre-sizes the result array like C++ vector<int>(n).
function rearrangeBySign(arr) {
  const n = arr.length;
  const result = new Array(n).fill(0);

  let posIndex = 0; // Positions: 0, 2, 4, ...
  let negIndex = 1; // Positions: 1, 3, 5, ...

  for (const num of arr) {
    if (num > 0) {
      result[posIndex] = num;
      posIndex += 2;
    } else {
      result[negIndex] = num;
      negIndex += 2;
    }
  }

  return result;
}

/*
    =====================================================
    LONGEST CONSECUTIVE SEQUENCE IN AN ARRAY
    =====================================================

    Problem: Given an unsorted array of integers, find the length of the
    longest consecutive elements sequence.

    Example:
    Input: nums = [100, 4, 200, 1, 3, 2]              → Output: 4  ([1,2,3,4])
    Input: nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]      → Output: 9

    =====================================================
    INTUITION:
    =====================================================
    Brute force with sorting is O(n log n). Optimal uses a Set for O(1) lookups.

    Key Insight: A number is the START of a sequence only if (num - 1) does NOT exist.
    We only count sequence length starting from these "sequence starters".

    IMPORTANT (Avoiding TLE): iterate over the UNIQUE values in the set, not the original
    array, so duplicates don't cause redundant work.

    =====================================================
    WHY O(n)? Each element is visited at most twice (start-check + counting).
    TIME: O(n)   SPACE: O(n)
    =====================================================
*/

// JavaScript note: C++ used unordered_map<int,bool>. The natural JS structure for "does this
// value exist?" is a Set, with O(1) .has(). We iterate the set itself to avoid duplicate work.
function longestConsecutive(nums) {
  if (nums.length === 0) return 0;

  // Step 1: Insert all elements into a Set (handles duplicates automatically)
  const numSet = new Set(nums);

  let maxLen = 0;

  // Step 2: Iterate over UNIQUE values in the set
  for (const num of numSet) {
    // Check if this is the start of a sequence
    if (!numSet.has(num - 1)) {
      let currentNum = num;
      let currentLen = 1;

      // Count consecutive elements
      while (numSet.has(currentNum + 1)) {
        currentNum++;
        currentLen++;
      }

      maxLen = Math.max(maxLen, currentLen);
    }
  }

  return maxLen;
}

// Driver code
console.log(rearrangeBySign([3, 1, -2, -5, 2, -4]).join(" ")); // 3 -2 1 -5 2 -4
console.log(longestConsecutive([100, 4, 200, 1, 3, 2])); // 4
console.log(longestConsecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1])); // 9
