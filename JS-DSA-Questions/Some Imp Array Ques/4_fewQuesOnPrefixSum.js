/*
    =====================================================
    LONGEST SUBARRAY WITH SUM K (Positives and Negatives)
    =====================================================

    Video link : https://www.youtube.com/watch?v=frf7qxiN2qU

    Problem: Given an array containing both positive and negative integers
    and a sum k, find the length of the longest subarray that sums to k.

    Example:
    Input: arr = [1, -1, 5, -2, 3], k = 3 → Output: 4  ([1, -1, 5, -2])

    =====================================================
    WHAT IS PREFIX SUM?
    =====================================================
    Prefix Sum is a technique where we precompute cumulative sums.
    For array:    [1, -1, 5, -2, 3]
    Prefix Sum:   [1,  0, 5,  3, 6]
    prefix[i] = arr[0] + arr[1] + ... + arr[i]

    KEY PROPERTY: Sum of subarray from index (i+1) to j = prefix[j] - prefix[i]
    This lets us find the sum of ANY subarray in O(1).

    =====================================================
    INTUITION:
    =====================================================
    If prefix[j] - prefix[i] = k, then subarray (i+1..j) sums to k.
    Rearranging: prefix[j] - k = prefix[i].
    For each j, check if (prefix[j] - k) was seen earlier; if yes, length = j - i.
    Use a Map {prefixSum -> earliest index}. Earliest index → longest subarray.

    Why map.set(0, -1)? If prefixSum itself equals k, we need (prefixSum - k = 0)
    to exist, representing a subarray from index 0.

    =====================================================
    TIME COMPLEXITY:  O(n)   SPACE COMPLEXITY: O(n)
    =====================================================
*/

// JavaScript note: C++ used unordered_map and had to use find() to distinguish a missing key
// from a stored 0 value. A JS Map has .has() which makes this clean and unambiguous.
function longestSubarrayWithSumK(arr, k) {
  const prefixMap = new Map(); // {prefixSum: earliest index}
  prefixMap.set(0, -1); // IMPORTANT: empty prefix with sum 0
  let prefixSum = 0;
  let maxLen = 0;

  for (let i = 0; i < arr.length; i++) {
    prefixSum += arr[i];

    // Check if (prefixSum - k) exists
    const need = prefixSum - k;
    if (prefixMap.has(need)) {
      const len = i - prefixMap.get(need);
      maxLen = Math.max(maxLen, len);
    }

    // Store prefixSum only if not already present (keep earliest index)
    if (!prefixMap.has(prefixSum)) {
      prefixMap.set(prefixSum, i);
    }
  }

  return maxLen;
}

/*
    =====================================================
    COUNT SUBARRAY SUM EQUALS K
    =====================================================

    Problem: Return the total number of subarrays whose sum equals k.
    Video: https://www.youtube.com/watch?v=xvNwoz-ufXA

    Example:
    Input: nums = [1, 1, 1], k = 2 → Output: 2
    Input: nums = [1, 2, 3], k = 3 → Output: 2

    Difference from "Longest": here we store COUNT of each prefix sum (to count all
    occurrences), rather than the earliest index.

    For each prefix sum, ask: "How many times have we seen (prefixSum - k)?"
    Each occurrence is a valid subarray ending at the current index.

    Why map.set(0, 1)? If prefixSum equals k, (prefixSum - k = 0) must be counted once.

    TIME: O(n)   SPACE: O(n)
*/

function subarraySum(nums, k) {
  const prefixCount = new Map(); // {prefixSum: frequency}
  prefixCount.set(0, 1); // Empty prefix with sum 0

  let prefixSum = 0;
  let count = 0;

  for (const num of nums) {
    prefixSum += num;

    // Check how many times (prefixSum - k) occurred
    const need = prefixSum - k;
    if (prefixCount.has(need)) {
      count += prefixCount.get(need);
    }

    // Add current prefixSum to map
    prefixCount.set(prefixSum, (prefixCount.get(prefixSum) || 0) + 1);
  }

  return count;
}

/*
    =====================================================
    COUNT SUBARRAYS WITH EQUAL 0s AND 1s
    =====================================================

    Problem: Given an array of only 0s and 1s, count subarrays having equal 0s and 1s.

    Example:
    Input: arr = [1, 0, 0, 1, 0, 1, 1] → Output: 8
    Input: arr = [1, 0, 1, 0]          → Output: 4

    Key Trick: Replace every 0 with -1. A subarray with equal 0s and 1s then sums to 0.
    So the problem reduces to "Count subarrays with sum = 0": count how many times the
    same prefix sum has appeared before.

    TIME: O(n)   SPACE: O(n)
*/

function countSubarraysWithEqual0sAnd1s(arr) {
  const prefixCount = new Map(); // {prefixSum: frequency}
  prefixCount.set(0, 1); // IMPORTANT: empty prefix with sum 0
  let prefixSum = 0;
  let count = 0;

  for (let i = 0; i < arr.length; i++) {
    // Treat 0 as -1
    prefixSum += arr[i] === 0 ? -1 : 1;

    // If this prefixSum was seen before, all previous occurrences form valid subarrays
    if (prefixCount.has(prefixSum)) {
      count += prefixCount.get(prefixSum);
    }

    prefixCount.set(prefixSum, (prefixCount.get(prefixSum) || 0) + 1);
  }

  return count;
}

/*
    Similarly, "Longest Subarray with Equal 0s and 1s" is just "longest subarray with sum k"
    where we treat 0 as -1 and 1 as +1, then find the longest subarray with sum = 0.
*/

// Driver code
console.log(longestSubarrayWithSumK([1, -1, 5, -2, 3], 3)); // 4
console.log(subarraySum([1, 1, 1], 2)); // 2
console.log(countSubarraysWithEqual0sAnd1s([1, 0, 0, 1, 0, 1, 1])); // 8
