// Given an array of distinct integers and a target, you have to return the list of all unique combinations where the chosen
// numbers sum to target. You may return the combinations in any order. The same number may be chosen from the given array an unlimited number of times.
// Two combinations are unique if the frequency of at least one of the chosen numbers is different.

// Video link : https://www.youtube.com/watch?v=OyZFFqQtu98&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=10

// There are 2 Approaches to solve this problem :-
//
// =====================================================================================
// APPROACH 1: Backtracking with For-Loop
// =====================================================================================
//
// INTUITION:
// -----------
// Think of it like filling a shopping cart where you can buy unlimited quantities
// of each item. At each step, you look at items from a certain position onwards
// and decide which one to add to your cart.
//
// The key insight is: once you decide to stop buying item X, you never go back to it.
// This prevents counting [2,3] and [3,2] as different combinations.
//
// WHY FOR-LOOP?
// -------------
// The for-loop naturally explores "which item do I pick next?" At each recursion level,
// we try picking each candidate one by one. After picking, we recurse to pick more items.
//
// WHY PASS 'i' (not 'i+1')?
// -------------------------
// Since same number can be used unlimited times, we stay at index 'i' after picking it.
// This allows: [2] -> [2,2] -> [2,2,2] (picking 2 three times)
//
// WHY START LOOP FROM 'index'?
// ----------------------------
// If we always start from 0, we'd get both [2,3] and [3,2].
// By starting from 'index', once we move past an element, we never revisit it.
// This ensures combinations are generated in non-decreasing order of indices.
//
// ALGORITHM:
// ----------
// 1. Base case: If target == 0, we found a valid combination, add it to result
// 2. For each candidate from 'index' to end:
//    a. If candidate <= target (can be used):
//       - Add candidate to current combination
//       - Recurse with same index 'i' (allow reuse) and reduced target
//       - Backtrack: remove the candidate (try other options)
//
// Time Complexity: O(2^t) where t = target/min(candidates)
// Space Complexity: O(t) for recursion stack
//
// RECURSION TREE for candidates = [2, 3], target = 6:
// ----------------------------------------------------
//
//                        solve(target=6, idx=0, curr=[])
//                        /                            \
//               Pick 2                                Pick 3
//        solve(target=4, idx=0, curr=[2])     solve(target=3, idx=1, curr=[3])
//              /              \                          |
//         Pick 2           Pick 3                    Pick 3
// solve(t=2,idx=0,[2,2])  solve(t=1,idx=1,[2,3])  solve(t=0,idx=1,[3,3])
//        /        \              |                    ✅ FOUND!
//    Pick 2    Pick 3         3>1, SKIP
// solve(t=0,[2,2,2])  3>2, SKIP
//   ✅ FOUND!
//
// Result: [[2,2,2], [3,3]]

// NOTE ON JAVASCRIPT: C++ used a class with member functions. In JS we just use plain
// functions. The one thing to remember: when we store a solution, we push a COPY
// ([...current]) because `current` is a shared array mutated by push()/pop() during
// backtracking. C++ `push_back(current)` copied the vector automatically.
function combinationSum(candidates, target) {
  const result = [];
  const current = [];

  function solve(target, index) {
    if (target === 0) {
      result.push([...current]); // push a copy of the current combination
      return;
    }

    for (let i = index; i < candidates.length; i++) {
      if (candidates[i] <= target) {
        current.push(candidates[i]);
        solve(target - candidates[i], i); // stay at index i to allow reuse
        current.pop(); // backtrack
      }
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
// Think of standing in front of each candidate and asking yourself two questions:
//   1. "Should I take this item?" (PICK)  -> stay at same index (unlimited use)
//   2. "Should I skip this item forever?" (NOT-PICK) -> move to next index
//
// WHY STAY AT SAME INDEX ON PICK?
// -------------------------------
// When we pick an element, we might want to pick it again (unlimited use).
// So we don't increment index. Example: target=6, arr=[2]
//   - Pick 2 (stay at idx=0) -> Pick 2 again -> Pick 2 again -> [2,2,2] ✅
//
// WHY MOVE TO NEXT INDEX ON NOT-PICK?
// -----------------------------------
// When we decide NOT to pick an element, we're saying "I don't want ANY more
// of this element in my combination". So we move to the next index forever.
//
// BASE CASE DIFFERENCE FROM APPROACH 1:
// - Approach 1: target == 0 means found (checked at start of function)
// - Approach 2: ind == arr.length means we've made decisions for all elements,
//               then check if target == 0 to validate the combination
//
// Time Complexity: O(2^t) where t = target/min(candidates)
// Space Complexity: O(t) for recursion stack
//
// COMPARISON OF BOTH APPROACHES:
// | Aspect          | Approach 1 (For-Loop)      | Approach 2 (Pick/Not-Pick) |
// |-----------------|----------------------------|----------------------------|
// | Decision Type   | "Which one to pick next?"  | "Pick this or skip?"       |
// | Branching       | Multiple branches (loop)   | Binary branches            |
// | Base Case       | target == 0                | ind == size && target == 0 |
function combinationSumPickNotPick(candidates, target) {
  const ans = [];
  const ds = [];

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
      solve(ind, target - candidates[ind]); // Stay at same index
      ds.pop(); // Backtrack
    }

    // NOT-PICK: Skip current element, move to next index
    solve(ind + 1, target);
  }

  solve(0, target);
  return ans;
}

console.log(combinationSum([2, 3, 6, 7], 7)); // [[2,2,3],[7]]
console.log(combinationSumPickNotPick([2, 3, 6, 7], 7)); // [[2,2,3],[7]]
