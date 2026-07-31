// Given an array print all the sum of the subset generated from it, in the increasing order.
// Output should be printed in increasing order of sum.

// Video link : https://www.youtube.com/watch?v=rYkfBRtMJr8&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=12

// =====================================================================================
// PROBLEM UNDERSTANDING
// =====================================================================================
//
// Given an array, we need to find the SUM of each subset (not the subset itself).
// Then return all these sums in SORTED order.
//
// Example: arr = [2, 3]
// Subsets: [], [2], [3], [2,3]
// Sums:     0,   2,   3,    5
// Output: [0, 2, 3, 5] (already sorted)
//
// Example: arr = [5, 2, 1]
// Subsets: [], [5], [2], [1], [5,2], [5,1], [2,1], [5,2,1]
// Sums:     0,   5,   2,   1,    7,     6,     3,      8
// Output: [0, 1, 2, 3, 5, 6, 7, 8] (sorted)

// =====================================================================================
// APPROACH: Pick / Not-Pick Pattern
// =====================================================================================
//
// INTUITION:
// -----------
// This is the simplest subset problem - we don't need to track the actual subset,
// just the running SUM. At each index, we make a binary decision:
//   1. PICK: Add current element to sum
//   2. NOT-PICK: Don't add, keep sum as is
//
// Since we only care about sums (not the actual subsets), we just pass the
// cumulative sum through recursion instead of maintaining a subset array.
//
// BASE CASE:
// ----------
// When we reach index === n (processed all elements), the current sum
// represents one complete subset's sum. Add it to the result.
//
// ALGORITHM:
// ----------
// 1. Start with index=0 and sum=0
// 2. At each index:
//    a. PICK: Recurse with (index+1, sum + arr[index])
//    b. NOT-PICK: Recurse with (index+1, sum)
// 3. Base case: When index === n, add sum to result
// 4. Sort the result at the end
//
// Time Complexity: O(2^n * n) for generating + sorting
// Space Complexity: O(2^n) to store all subset sums + O(n) recursion stack
//
// RECURSION TREE for arr = [2, 3]:
//                        solve(idx=0, sum=0)
//                        /                \
//                   PICK 2              NOT-PICK
//            solve(idx=1, sum=2)     solve(idx=1, sum=0)
//              /          \            /          \
//         PICK 3      NOT-PICK    PICK 3      NOT-PICK
//    solve(idx=2,sum=5) solve(idx=2,sum=2) solve(idx=2,sum=3) solve(idx=2,sum=0)
//         |                  |                  |                  |
//    Add 5              Add 2              Add 3              Add 0
//
// Result before sorting: [5, 2, 3, 0] -> after sorting: [0, 2, 3, 5]

// JavaScript note: remember to sort numerically with (a, b) => a - b, otherwise
// Array.prototype.sort() would compare the numbers as strings.
function subsetSums(arr) {
  const result = [];

  function solve(index, sum) {
    // Base case: processed all elements
    if (index === arr.length) {
      result.push(sum);
      return;
    }

    // PICK: Include current element in subset
    solve(index + 1, sum + arr[index]);

    // NOT-PICK: Exclude current element from subset
    solve(index + 1, sum);
  }

  solve(0, 0);
  result.sort((a, b) => a - b); // Sort in increasing order
  return result;
}

console.log(subsetSums([2, 3])); // [0, 2, 3, 5]
console.log(subsetSums([5, 2, 1])); // [0, 1, 2, 3, 5, 6, 7, 8]
