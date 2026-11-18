// Write a function to calculate power(x, n) where x is a number and n is an integer.

// Intuition:
// Any integer power n can be broken down using its binary representation, because binary
// represents a number as a sum of powers of 2:
//      n = (b_k * 2^k) + ... + (b_1 * 2^1) + (b_0 * 2^0), where each b_i is 0 or 1.
// So x^n = product of x^(2^i) for every bit i that is set.
// Instead of multiplying x by itself n times, we square the base repeatedly and multiply into the
// result only when the current binary bit is 1. This is "fast exponentiation" — O(log n).

// JavaScript note: C++ used `long` to hold n (to safely negate INT_MIN). JS numbers are 64-bit
// doubles, so plain numbers work here. (JS also has the built-in ** operator, e.g. x ** n, but
// we implement it manually to show the algorithm.)
function power(x, n) {
  let binaryForm = n;
  let result = 1;

  if (binaryForm < 0) {
    binaryForm = -binaryForm; // x^(-n) = 1 / x^n
    x = 1 / x;
  }

  while (binaryForm > 0) {
    // O(log n)
    if (binaryForm % 2 === 1) {
      // If the last bit is 1, multiply the result by the current x
      result = result * x;
    }
    x = x * x; // square the base: x^2, x^4, x^8, ...
    binaryForm = Math.floor(binaryForm / 2);
  }

  return result;
}

console.log(power(3, 13)); // 1594323

// Time Complexity: O(log n). Space Complexity: O(1).
// Example: x = 3, n = 13 = 1101(binary), so 3^13 = 3^8 * 3^4 * 3^1 = 6561 * 81 * 3 = 1594323.
