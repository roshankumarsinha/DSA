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
//
// TRACE for [2,3,6,7], target=7:
// -------------------------------
// solve(t=7, idx=0, []) 
//   -> Pick 2: solve(t=5, idx=0, [2])
//        -> Pick 2: solve(t=3, idx=0, [2,2])
//             -> Pick 2: solve(t=1, idx=0, [2,2,2]) -> 2>1, 3>1, 6>1, 7>1, return
//             -> Pick 3: solve(t=0, idx=1, [2,2,3]) -> ✅ Found [2,2,3]
//        -> Pick 3: solve(t=2, idx=1, [2,3]) -> 3>2, 6>2, 7>2, return
//   -> Pick 7: solve(t=0, idx=3, [7]) -> ✅ Found [7]
//
// Final Result: [[2,2,3], [7]]
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void solve(vector<int>& candidates, int target, int index, vector<int>& current, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(current);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            if (candidates[i] <= target) {
                current.push_back(candidates[i]);
                solve(candidates, target - candidates[i], i, current, result);
                current.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        solve(candidates, target, 0, current, result);
        return result;
    }
};

// =====================================================================================
// APPROACH 2: Pick / Not-Pick Pattern
// =====================================================================================
//
// INTUITION:
// -----------
// Think of standing in front of each candidate and asking yourself two questions:
//   1. "Should I take this item?" (PICK)
//   2. "Should I skip this item forever?" (NOT-PICK)
//
// This is a classic recursion pattern used in many problems like subset sum,
// knapsack, etc. The beauty is that it breaks down the problem into binary choices.
//
// WHY BINARY DECISIONS?
// ---------------------
// At each index, we have exactly 2 choices:
//   - PICK: Add current element to combination, but STAY at same index
//           (because we can pick it again - unlimited use allowed)
//   - NOT-PICK: Move to next index, meaning we'll NEVER use this element again
//
// This is different from Approach 1 where we use a for-loop to try all elements.
// Here, we explicitly make a binary decision at each step.
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
// This prevents duplicates and ensures we explore all unique combinations.
//
// BASE CASE DIFFERENCE FROM APPROACH 1:
// -------------------------------------
// - Approach 1: target == 0 means found (checked at start of function)
// - Approach 2: ind == arr.size() means we've made decisions for all elements
//               Then check if target == 0 to validate the combination
//
// ALGORITHM:
// ----------
// 1. Base case: If ind == arr.size()
//    - If target == 0, add current combination to result
//    - Return (we've considered all elements)
// 2. PICK: If arr[ind] <= target
//    - Add arr[ind] to current combination
//    - Recurse with SAME index (ind) and reduced target
//    - Backtrack: remove arr[ind]
// 3. NOT-PICK: Recurse with NEXT index (ind+1) and same target
//
// Time Complexity: O(2^t) where t = target/min(candidates)
// Space Complexity: O(t) for recursion stack
//
// RECURSION TREE for candidates = [2, 3], target = 6:
// ----------------------------------------------------
//
//                          solve(ind=0, target=6, ds=[])
//                          /                          \
//                    PICK 2                        NOT-PICK
//          solve(ind=0, t=4, ds=[2])         solve(ind=1, t=6, ds=[])
//              /              \                    /            \
//         PICK 2          NOT-PICK            PICK 3         NOT-PICK
// solve(ind=0,t=2,[2,2])  solve(ind=1,t=4,[2])  solve(ind=1,t=3,[3])  solve(ind=2,t=6,[])
//      /        \              ...                  /        \           ind==size, t!=0 ❌
//  PICK 2    NOT-PICK                          PICK 3     NOT-PICK
// solve(t=0,[2,2,2])  solve(ind=1,t=2,[2,2])  solve(t=0,[3,3])  ind==size, t!=0 ❌
//  ✅ FOUND!              /        \           ✅ FOUND!
//                    PICK 3     NOT-PICK
//                   3>2 SKIP   ind==size, t!=0 ❌
//
// Result: [[2,2,2], [3,3]]
//
// TRACE for [2,3,6,7], target=7:
// -------------------------------
// solve(ind=0, t=7, [])
//   -> PICK 2: solve(ind=0, t=5, [2])
//        -> PICK 2: solve(ind=0, t=3, [2,2])
//             -> PICK 2: solve(ind=0, t=1, [2,2,2])
//                  -> PICK 2: 2>1, skip
//                  -> NOT-PICK: solve(ind=1, t=1, [2,2,2])
//                       -> PICK 3: 3>1, skip
//                       -> NOT-PICK: ... eventually fails
//             -> NOT-PICK: solve(ind=1, t=3, [2,2])
//                  -> PICK 3: solve(ind=1, t=0, [2,2,3]) -> ✅ Found [2,2,3]
//   -> NOT-PICK: solve(ind=1, t=7, [])
//        -> ... eventually finds [7] via NOT-PICK path to index 3
//
// Final Result: [[2,2,3], [7]]
//
// COMPARISON OF BOTH APPROACHES:
// ------------------------------
// | Aspect          | Approach 1 (For-Loop)      | Approach 2 (Pick/Not-Pick) |
// |-----------------|----------------------------|----------------------------|
// | Decision Type   | "Which one to pick next?"  | "Pick this or skip?"       |
// | Branching       | Multiple branches (loop)   | Binary branches            |
// | Base Case       | target == 0                | ind == size && target == 0 |
// | Code Style      | Iterative feel             | Pure recursive feel        |
// | When to use     | More intuitive for some    | Classic DP/recursion style |

class Solution2 {
public:
    void solve(int ind, int target, vector<int>& arr, vector<vector<int>>& ans, vector<int>& ds) {
        if (ind == arr.size()) {
            if (target == 0) {
                ans.push_back(ds);
            }
            return;
        }

        // PICK: Include current element if it doesn't exceed target
        if (arr[ind] <= target) {
            ds.push_back(arr[ind]);
            solve(ind, target - arr[ind], arr, ans, ds);  // Stay at same index
            ds.pop_back();  // Backtrack
        }

        // NOT-PICK: Skip current element, move to next index
        solve(ind + 1, target, arr, ans, ds);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> ds;
        solve(0, target, candidates, ans, ds);
        return ans;
    }
};