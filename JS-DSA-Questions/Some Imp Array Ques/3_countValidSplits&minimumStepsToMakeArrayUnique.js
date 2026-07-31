/*
    =====================================================
    COUNT NUMBER OF VALID SPLITS IN AN ARRAY
    =====================================================

    Problem: Given a 0-indexed integer array nums of length n, count the
    number of valid splits where:
    1. The sum of the first (i + 1) elements >= sum of the remaining elements.
    2. There must be at least one element on the right side (i.e., i < n - 1).

    Example:
    Input: nums = [10, 4, -8, 7] → Output: 2
    Input: nums = [2, 3, 1, 0]   → Output: 2

    =====================================================
    INTUITION:
    =====================================================
    Brute Force: For each split point, compute left and right sums → O(n²). Too slow!

    Optimal: Use PREFIX SUM.
    - totalSum = leftSum + rightSum, so rightSum = totalSum - leftSum
    - Condition leftSum >= rightSum simplifies to 2 * leftSum >= totalSum

    So we just:
    1. Compute totalSum once
    2. Maintain a running leftSum
    3. Check leftSum >= (totalSum - leftSum) at each valid split point

    =====================================================
    TIME COMPLEXITY:  O(n)
    SPACE COMPLEXITY: O(1)
    =====================================================
*/

// JavaScript note: C++ used `long long` to avoid overflow while summing. JS numbers are
// 64-bit doubles (safe integers up to 2^53 - 1), so a plain number is fine for typical inputs.
function waysToSplitArray(nums) {
  const n = nums.length;

  let totalSum = 0;
  for (const num of nums) {
    totalSum += num;
  }

  let leftSum = 0;
  let count = 0;

  for (let i = 0; i < n - 1; i++) {
    leftSum += nums[i];
    const rightSum = totalSum - leftSum;
    if (leftSum >= rightSum) {
      count++;
    }
  }

  return count;
}

/*
    =====================================================
    MINIMUM INCREMENT OPERATIONS TO MAKE ARRAY UNIQUE
    =====================================================

    Problem: In one operation you can choose an index i and increment arr[i] by 1.
    Return the minimum number of operations needed to make every value unique.

    Example:
    Input: arr = [1, 1, 2, 3]         → Output: 3
    Input: arr = [3, 2, 1, 2, 1, 7]   → Output: 6

    =====================================================
    APPROACH 1: SORTING - O(n log n)
    =====================================================
    Key Insight: We can only INCREMENT, never decrement. So smaller duplicates should
    stay, and larger duplicates must be pushed forward.

    After sorting, for each element that is not strictly greater than the previous element,
    we must increment it to (previous + 1). The difference is the number of operations.

    =====================================================
    APPROACH 2: COUNTING - O(n + maxVal)
    =====================================================
    1. Build a frequency map: freq[x] = how many times x appears
    2. Sweep from 0 to maxVal + n:
       - If freq[i] > 1, there are (freq[i] - 1) duplicates at value i
       - Push those duplicates to i+1: operations += (freq[i]-1), freq[i+1] += (freq[i]-1)
    Why maxVal + n? Worst case all elements equal, cascading up to n-1 slots beyond max.
*/

// Method 1: Sorting Approach - O(n log n) time, O(1) space
// JavaScript note: sort numbers with a comparator (a, b) => a - b.
function minIncrementForUniqueSort(arr) {
  arr.sort((a, b) => a - b);

  let operations = 0;

  for (let i = 1; i < arr.length; i++) {
    if (arr[i] <= arr[i - 1]) {
      const needed = arr[i - 1] + 1;
      operations += needed - arr[i];
      arr[i] = needed;
    }
  }

  return operations;
}

// Method 2: Counting Approach - O(n + maxVal) time and space
// JavaScript note: C++ used unordered_map<int,int>. Here a Map works well; missing keys
// return undefined, so we default with `|| 0`.
function minIncrementForUnique(arr) {
  const freqMap = new Map();
  let maxVal = 0;

  for (const num of arr) {
    freqMap.set(num, (freqMap.get(num) || 0) + 1);
    maxVal = Math.max(maxVal, num);
  }

  let operations = 0;
  // Fixed upper bound: maxVal + n covers worst case (all elements same value)
  for (let i = 0; i < maxVal + arr.length; i++) {
    const freq = freqMap.get(i) || 0;
    if (freq > 1) {
      const duplicates = freq - 1; // Number of duplicates at value i
      operations += duplicates; // Each duplicate needs 1 operation to move to next value
      freqMap.set(i + 1, (freqMap.get(i + 1) || 0) + duplicates); // Push duplicates forward
    }
  }
  return operations;
}

// Driver code
console.log(waysToSplitArray([10, 4, -8, 7])); // 2
console.log(minIncrementForUniqueSort([1, 1, 2, 3])); // 3
console.log(minIncrementForUnique([3, 2, 1, 2, 1, 7])); // 6
