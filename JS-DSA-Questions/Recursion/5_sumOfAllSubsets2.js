// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
// The solution set must not contain duplicate subsets. Return the solution in any order.

// Video link : https://www.youtube.com/watch?v=RIn3gOkbhQE&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=13

// =====================================================================================
// PROBLEM UNDERSTANDING
// =====================================================================================
//
// This is "Subsets II" - the array may contain DUPLICATES, but we need UNIQUE subsets.
//
// Example: nums = [1, 2, 2]
// All subsets (with duplicates): [], [1], [2], [2], [1,2], [1,2], [2,2], [1,2,2]
// Unique subsets: [], [1], [2], [1,2], [2,2], [1,2,2]  (6 subsets, not 8)
//
// KEY CHALLENGE: How to avoid generating duplicate subsets?

// =====================================================================================
// APPROACH 1: Backtracking with For-Loop + Skip Duplicates
// =====================================================================================
//
// INTUITION:
// -----------
// Similar to Combination Sum II! The key insight is:
//   1. SORT the array to bring duplicates together
//   2. At each recursion level, if we've already picked a value, skip its duplicates
//
// WHY COLLECT AT EVERY STEP (not just at base case)?
// --------------------------------------------------
// Here we want ALL subsets, so we add the current subset to result at EVERY step:
//   - Empty subset (added at the start)
//   - Partial subsets (added as we build them)
//   - Complete subsets (when we've considered all elements)
//
// ALGORITHM:
// ----------
// 1. Sort the array (to group duplicates together)
// 2. At each call, add current subset to result
// 3. For each element from 'index' to end:
//    a. Skip if current === previous at same level (i > index && nums[i] === nums[i-1])
//    b. Add element, recurse with index = i+1, then backtrack
//
// Time Complexity: O(2^n * n) - 2^n subsets, each taking O(n) to copy
// Space Complexity: O(n) for recursion stack + O(2^n * n) for storing subsets
//
// Result for [1,2,2]: [[], [1], [1,2], [1,2,2], [2], [2,2]]

// JavaScript note: push a COPY ([...current]) into result. Pushing the shared `current`
// array directly would store a reference that later push()/pop() would mutate.
function subsetsWithDup(nums) {
  const result = [];
  const current = [];
  nums.sort((a, b) => a - b); // Sort to handle duplicates

  function solve(index) {
    // Add current subset to result (collect at every step)
    result.push([...current]);

    for (let i = index; i < nums.length; i++) {
      // Skip duplicates at the same recursion level
      if (i > index && nums[i] === nums[i - 1]) {
        continue;
      }
      current.push(nums[i]);
      solve(i + 1);
      current.pop(); // Backtrack
    }
  }

  solve(0);
  return result;
}

// =====================================================================================
// APPROACH 2: Pick / Not-Pick Pattern
// =====================================================================================
//
// INTUITION:
// -----------
//   1. PICK: Include current element, move to next index
//   2. NOT-PICK: Skip ALL occurrences of current element (same as Combination Sum II)
//
// WHY SKIP ALL DUPLICATES ON NOT-PICK?
// If we decide NOT to include element X, we must skip ALL of X's duplicates, otherwise
// we'd generate the same subset multiple times.
//
// WHY COLLECT AT BASE CASE (index === n)?
// In pick/not-pick, we build the complete subset through the recursion path.
// We only add it when we've made decisions for ALL elements (reached the end).
//
// | Aspect              | For-Loop Approach        | Pick/Not-Pick Approach    |
// |---------------------|--------------------------|---------------------------|
// | When to add subset  | At every recursive call  | Only at base case (ind==n)|
// | Skip duplicates     | i > index && same value  | Skip all dups on NOT-PICK |
// | Tree structure      | Multi-way branching      | Binary branching          |
function subsetsWithDupPickNotPick(nums) {
  const ans = [];
  const ds = [];
  nums.sort((a, b) => a - b);

  function solve(ind) {
    // Base case: processed all elements
    if (ind === nums.length) {
      ans.push([...ds]);
      return;
    }

    // PICK: Include current element
    ds.push(nums[ind]);
    solve(ind + 1);
    ds.pop(); // Backtrack

    // NOT-PICK: Skip all duplicates of current element
    let nextInd = ind + 1;
    while (nextInd < nums.length && nums[nextInd] === nums[ind]) {
      nextInd++;
    }
    solve(nextInd);
  }

  solve(0);
  return ans;
}

// =====================================================================================
// KEY DIFFERENCES FROM RELATED PROBLEMS:
// =====================================================================================
// | Problem              | Duplicates in Input | Element Reuse | Skip Logic              |
// |----------------------|---------------------|---------------|-------------------------|
// | Subsets I            | No                  | No            | None needed             |
// | Subsets II (this)    | Yes                 | No            | Skip dups at same level |
// | Combination Sum I    | No                  | Unlimited     | None needed             |
// | Combination Sum II   | Yes                 | No            | Skip dups at same level |

// Driver code
console.log("All unique subsets of [1, 2, 2]:");
for (const subset of subsetsWithDup([1, 2, 2])) {
  console.log(`[ ${subset.join(" ")} ]`);
}

console.log("\nTest with [4, 4, 4, 1, 4]:");
for (const subset of subsetsWithDup([4, 4, 4, 1, 4])) {
  console.log(`[ ${subset.join(" ")} ]`);
}
