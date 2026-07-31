// Given an array of integers arr, return the sum of the minimum value of all subarrays.
// Since the answer can be large, return it modulo 1e9 + 7.

// Notes link : https://takeuforward.org/data-structure/sum-of-subarray-minimums
// Video link : https://www.youtube.com/watch?v=v0e8p9JCgRc

// Example: [3, 1, 2, 4] → 17

// Intuition:
// Each element contributes only when it is the minimum of a subarray. Instead of enumerating all
// subarrays, count how many subarrays have arr[i] as their minimum.
// For each index i, find:
//    PLE[i]: index of the Previous Less Element (closest smaller element to the left).
//    NLE[i]: index of the Next Less Element (closest strictly-smaller element to the right).
// Then:
//    leftCount  = i - PLE[i]
//    rightCount = NLE[i] - i
//    contribution = arr[i] * leftCount * rightCount
// Left and right choices multiply because any left extension pairs with any right extension.

// JavaScript note: C++ used `long long` and a MOD constant to avoid overflow. JS numbers are safe
// up to 2^53; for typical inputs plain arithmetic with % MOD is fine. For very large arr[i]*left*
// right that could exceed 2^53, BigInt would be needed, but we keep it simple here.
const MOD = 1e9 + 7;

function sumSubarrayMins(arr) {
  const n = arr.length;
  const ple = new Array(n); // previous less element indices
  const nle = new Array(n); // next less element indices
  const s = [];

  // Previous Less Element (PLE)
  for (let i = 0; i < n; i++) {
    while (s.length > 0 && arr[s[s.length - 1]] > arr[i]) {
      s.pop();
    }
    ple[i] = s.length === 0 ? -1 : s[s.length - 1];
    s.push(i);
  }

  // Clear the stack to reuse
  s.length = 0;

  // Next Less Element (NLE)
  for (let i = n - 1; i >= 0; i--) {
    while (s.length > 0 && arr[s[s.length - 1]] >= arr[i]) {
      s.pop();
    }
    nle[i] = s.length === 0 ? n : s[s.length - 1];
    s.push(i);
  }

  // Total sum
  let sum = 0;
  for (let i = 0; i < n; i++) {
    const left = i - ple[i];
    const right = nle[i] - i;
    sum = (sum + ((arr[i] * left * right) % MOD)) % MOD;
  }

  return sum;
}

console.log("Sum of Subarray Minimums:", sumSubarrayMins([3, 1, 2, 4])); // 17

// Time Complexity: O(n). Space Complexity: O(n).
