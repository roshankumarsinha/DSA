// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
// Each number in candidates may only be used once in the combination. Note: The solution set must not contain duplicate combinations.

// Video link : https://www.youtube.com/watch?v=G1fRTGRxXU8&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=11

// KEY DIFFERENCES FROM COMBINATION SUM I:
// ----------------------------------------
// 1. Each element can be used ONLY ONCE (not unlimited times)
// 2. Candidates array may contain DUPLICATES
// 3. We must avoid duplicate combinations in the result

// =====================================================================================
// APPROACH 1: Backtracking with For-Loop + Skip Duplicates
// =====================================================================================
//
// INTUITION:
// -----------
// Similar to Combination Sum I, but with two key changes:
//   1. After picking an element, move to NEXT index (i+1) since each element can be used only once
//   2. Skip duplicate elements at the same recursion level to avoid duplicate combinations
//
// WHY SORT THE ARRAY?
// -------------------
// Sorting brings duplicate elements together. This allows us to easily skip duplicates
// by checking if current element equals the previous element at the same level.
// Example: [1,1,2,5,6,7,10] - both 1s are adjacent after sorting
//
// WHY SKIP DUPLICATES?
// --------------------
// Consider candidates = [1,1,2], target = 3
// Without skipping: We'd get [1,2] twice (once using first 1, once using second 1)
// With skipping: At each recursion level, if we've already tried a value, skip it
//
// The condition `i > index && candidates[i] === candidates[i-1]` means:
//   - i > index: We're not at the first element of this recursion level
//   - candidates[i] === candidates[i-1]: Current element equals previous
//   - If both true, skip this element to avoid duplicate combinations
//
// WHY i > index (not i > 0)?
// --------------------------
// We only skip duplicates at the SAME recursion level, not across levels.
//
// ALGORITHM:
// ----------
// 1. Sort the candidates array (to group duplicates together)
// 2. Base case: If target == 0, add current combination to result
// 3. For each candidate from 'index' to end:
//    a. Skip if current === previous at same level (i > index && arr[i] === arr[i-1])
//    b. If candidate > target: break (array is sorted, no point going further)
//    c. Otherwise pick, recurse with NEXT index (i+1), then backtrack
//
// Time Complexity: O(2^n) where n = number of candidates
// Space Complexity: O(n) for recursion stack
//
// TRACE for [10,1,2,7,6,1,5], target=8 (sorted: [1,1,2,5,6,7,10]):
// Found combinations: [[1,1,6], [1,2,5], [1,7], [2,6]]

// JavaScript note: sort numbers with a comparator, since Array.prototype.sort() sorts
// lexicographically by default (e.g. [10,2] -> [10,2] not [2,10]). Use (a, b) => a - b.
function combinationSum2(candidates, target) {
  const result = [];
  const current = [];
  candidates.sort((a, b) => a - b); // Sort to handle duplicates

  function solve(target, index) {
    if (target === 0) {
      result.push([...current]);
      return;
    }

    for (let i = index; i < candidates.length; i++) {
      // Skip duplicates at the same recursion level
      if (i > index && candidates[i] === candidates[i - 1]) {
        continue;
      }
      // Optimization: sorted array, so no point checking further
      if (candidates[i] > target) {
        break;
      }

      current.push(candidates[i]);
      solve(target - candidates[i], i + 1); // i+1: each element used once
      current.pop();
    }
  }

  solve(target, 0);
  return result;
}

// =====================================================================================
// APPROACH 2: Pick / Not-Pick Pattern
// =====================================================================================
//
// INTUITION:
// -----------
// Same binary decision pattern as Combination Sum I, but with modifications:
//   1. PICK: After picking, move to NEXT index (ind+1) since each element used once
//   2. NOT-PICK: Skip ALL occurrences of current element to avoid duplicates
//
// WHY SKIP ALL DUPLICATES ON NOT-PICK?
// ------------------------------------
// When we decide NOT to pick an element, we should skip all its duplicates too.
// Otherwise, we'd generate the same combination multiple times.
//
// | Aspect              | Combination Sum I        | Combination Sum II           |
// |---------------------|--------------------------|------------------------------|
// | Element reuse       | Unlimited                | Once only                    |
// | Duplicate elements  | No duplicates in input   | May have duplicates          |
// | After PICK          | Stay at same index (i)   | Move to next index (i+1)     |
// | Skip duplicates     | Not needed               | Required to avoid dup combos |
// | Sorting             | Optional                 | Required                     |
function combinationSum2PickNotPick(candidates, target) {
  const ans = [];
  const ds = [];
  candidates.sort((a, b) => a - b);

  function solve(ind, target) {
    if (ind === candidates.length) {
      if (target === 0) {
        ans.push([...ds]);
      }
      return;
    }

    // PICK: Include current element if it doesn't exceed target
    if (candidates[ind] <= target) {
      ds.push(candidates[ind]);
      solve(ind + 1, target - candidates[ind]); // Move to next index
      ds.pop(); // Backtrack
    }

    // NOT-PICK: Skip all duplicates of current element
    let nextInd = ind + 1;
    while (nextInd < candidates.length && candidates[nextInd] === candidates[ind]) {
      nextInd++;
    }
    solve(nextInd, target);
  }

  solve(0, target);
  return ans;
}

// Driver code
const candidates = [10, 1, 2, 7, 6, 1, 5];
const target = 8;
console.log(`Combinations that sum to ${target}:`);
for (const combination of combinationSum2(candidates, target)) {
  console.log(`[ ${combination.join(" ")} ]`);
}
