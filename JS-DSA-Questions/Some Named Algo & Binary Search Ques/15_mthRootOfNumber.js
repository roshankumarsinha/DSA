// Given two numbers N and M, find the Nth root of M. The Nth root of M is a number X such that
// X^N === M. If the Nth root is not an integer, return -1.

// Intuition:
// 1. The answer lies between 1 and M.
// 2. We want the largest X with X^N <= M (and equal to M for an exact integer root).
// 3. Brute force scanning 1..M is O(M); binary search on that range is O(log M).

// Notes link : https://takeuforward.org/data-structure/nth-root-of-a-number-using-binary-search

// Approach:
// 1. left = 1, right = M.
// 2. While left <= right: mid = (left + right) / 2, compute mid^N (with early exit if it exceeds M).
//    - If mid^N === M, return mid.
//    - If mid^N < M, left = mid + 1.
//    - If mid^N > M, right = mid - 1.
// 3. If nothing found, return -1.

// JavaScript note: C++ used `long long` in the power helper to avoid overflow. JS numbers are
// 64-bit doubles (safe up to 2^53). We still early-exit once the running product exceeds m, which
// both matches the original and keeps values small.
function power(mid, n, m) {
  let result = 1;
  for (let i = 0; i < n; i++) {
    result *= mid;
    if (result > m) return result; // early exit
  }
  return result;
}

function nthRoot(n, m) {
  let left = 1;
  let right = m;

  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    const midPowerN = power(mid, n, m);

    if (midPowerN === m) {
      return mid; // exact Nth root
    } else if (midPowerN < m) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1; // no integer Nth root
}

const n = 3;
const m = 27;
const res = nthRoot(n, m);
console.log(res !== -1 ? `The ${n}th root of ${m} is: ${res}` : `The ${n}th root of ${m} is not an integer.`); // 3
