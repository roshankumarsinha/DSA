// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
// Each number in candidates may only be used once in the combination. Note: The solution set must not contain duplicate combinations.

// Video link : https://www.youtube.com/watch?v=G1fRTGRxXU8&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=11

// KEY DIFFERENCES FROM COMBINATION SUM I:
// ----------------------------------------
// 1. Each element can be used ONLY ONCE (not unlimited times)
// 2. Candidates array may contain DUPLICATES
// 3. We must avoid duplicate combinations in the result

// There are 2 Approaches to solve this problem :-
//
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
// The condition `i > index && candidates[i] == candidates[i-1]` means:
//   - i > index: We're not at the first element of this recursion level
//   - candidates[i] == candidates[i-1]: Current element equals previous
//   - If both true, skip this element to avoid duplicate combinations
//
// WHY i > index (not i > 0)?
// --------------------------
// We only skip duplicates at the SAME recursion level, not across levels.
// Example: [1,1,2], target=4. We want [1,1,2] to be valid.
//   - At level 0: Pick first 1 (index=0)
//   - At level 1: Pick second 1 (index=1) - this is ALLOWED (different level)
//   - At level 0 again: Skip second 1 because i=1 > index=0 and arr[1]==arr[0]
//
// ALGORITHM:
// ----------
// 1. Sort the candidates array (to group duplicates together)
// 2. Base case: If target == 0, add current combination to result
// 3. For each candidate from 'index' to end:
//    a. Skip if current == previous at same level (i > index && arr[i] == arr[i-1])
//    b. If candidate <= target:
//       - Add candidate to current combination
//       - Recurse with NEXT index (i+1) - element used only once
//       - Backtrack: remove the candidate
//
// Time Complexity: O(2^n) where n = number of candidates
// Space Complexity: O(n) for recursion stack
//
// RECURSION TREE for candidates = [1, 1, 2], target = 3 (after sorting):
// -----------------------------------------------------------------------
//
//                     solve(target=3, idx=0, curr=[])
//                     /           |              \
//              Pick 1(idx=0)   Skip 1(idx=1)    Pick 2
//           solve(t=2,idx=1,[1])  (duplicate!)   solve(t=1,idx=2,[2])
//              /        \                              |
//         Pick 1      Pick 2                     No more candidates
//    solve(t=1,idx=2,[1,1])  solve(t=0,idx=3,[1,2])      ❌
//           |              ✅ FOUND!
//       Pick 2
//    solve(t=-1) ❌ (2>1)
//
// Wait, let me redo this more accurately:
//
//                     solve(target=3, idx=0, curr=[])
//                            /          \
//                     Pick arr[0]=1    Pick arr[2]=2 (skip arr[1]=1, duplicate)
//              solve(t=2, idx=1, [1])   solve(t=1, idx=3, [2])
//                    /        \               |
//           Pick arr[1]=1   Pick arr[2]=2   idx >= size, return
//      solve(t=1,idx=2,[1,1])  solve(t=0,idx=3,[1,2])
//              |                  ✅ FOUND [1,2]
//         Pick arr[2]=2
//       2>1, can't pick
//
// Hmm, let me trace more carefully with target=4:
//
// candidates = [1,1,2], target = 4 (sorted)
// -----------------------------------------
//                     solve(target=4, idx=0, curr=[])
//                     /                    \
//              Pick 1 (idx=0)           Skip to 2 (skip dup 1)
//         solve(t=3, idx=1, [1])         solve(t=2, idx=2, [2])
//              /        \                      |
//       Pick 1(idx=1)  Pick 2(idx=2)      No valid picks (idx>=size after)
//   solve(t=2,idx=2,[1,1])  solve(t=1,idx=3,[1,2])
//          |                    idx>=size, t!=0 ❌
//     Pick 2(idx=2)
//   solve(t=0,idx=3,[1,1,2])
//      ✅ FOUND [1,1,2]
//
// Result: [[1,1,2]]
//
// TRACE for [10,1,2,7,6,1,5], target=8 (sorted: [1,1,2,5,6,7,10]):
// -----------------------------------------------------------------
// Found combinations: [[1,1,6], [1,2,5], [1,7], [2,6]]

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    void solve(vector<int>& candidates, int target, int index, vector<int>& current, vector<vector<int>>& result) {
        if (target == 0) {
            result.push_back(current);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            // Skip duplicates at the same recursion level
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            // Optimization: if current element > target, no point checking further (array is sorted)
            if (candidates[i] > target) {
                break;
            }

            current.push_back(candidates[i]);
            solve(candidates, target - candidates[i], i + 1, current, result);  // i+1: each element used once
            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        sort(candidates.begin(), candidates.end());  // Sort to handle duplicates
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
// Same binary decision pattern as Combination Sum I, but with modifications:
//   1. PICK: After picking, move to NEXT index (ind+1) since each element used once
//   2. NOT-PICK: Skip ALL occurrences of current element to avoid duplicates
//
// WHY SKIP ALL DUPLICATES ON NOT-PICK?
// ------------------------------------
// When we decide NOT to pick an element, we should skip all its duplicates too.
// Otherwise, we'd generate the same combination multiple times.
//
// Example: [1,1,2], target=3
// If at index 0 we decide NOT to pick 1, we should also skip index 1 (also 1)
// Otherwise:
//   - NOT-PICK at idx=0 -> Pick at idx=1 gives [1,2]
//   - PICK at idx=0 -> NOT-PICK at idx=1 -> Pick at idx=2 gives [1,2]
//   - These are duplicates!
//
// By skipping all duplicates on NOT-PICK, we ensure:
//   - If we pick element X, we can pick its duplicates too (in subsequent calls)
//   - If we don't pick element X, we skip ALL of its duplicates
//
// ALGORITHM:
// ----------
// 1. Sort the candidates array
// 2. Base case: If ind == arr.size()
//    - If target == 0, add current combination to result
//    - Return
// 3. PICK: If arr[ind] <= target
//    - Add arr[ind] to current combination
//    - Recurse with NEXT index (ind+1) - element used only once
//    - Backtrack: remove arr[ind]
// 4. NOT-PICK: Skip all duplicates of current element, then recurse
//    - While (ind+1 < size && arr[ind] == arr[ind+1]) ind++
//    - Recurse with ind+1
//
// Time Complexity: O(2^n) where n = number of candidates
// Space Complexity: O(n) for recursion stack
//
// RECURSION TREE for candidates = [1, 1, 2], target = 4 (after sorting):
// -----------------------------------------------------------------------
//
//                        solve(ind=0, target=4, ds=[])
//                        /                         \
//                   PICK 1                      NOT-PICK (skip all 1s)
//          solve(ind=1, t=3, ds=[1])          solve(ind=2, t=4, ds=[])
//              /              \                       |
//         PICK 1           NOT-PICK              PICK 2
//   solve(ind=2,t=2,[1,1])  solve(ind=2,t=3,[1])  solve(ind=3,t=2,[2])
//        |                        |                   |
//    PICK 2                   PICK 2              ind>=size ❌
//  solve(ind=3,t=0,[1,1,2])  solve(ind=3,t=1,[1,2])
//    ✅ FOUND!               ind>=size, t!=0 ❌
//
// Result: [[1,1,2]]
//
// TRACE for [1,1,2,5,6,7,10], target=8:
// -------------------------------------
// solve(ind=0, t=8, [])
//   -> PICK 1: solve(ind=1, t=7, [1])
//        -> PICK 1: solve(ind=2, t=6, [1,1])
//             -> PICK 2: solve(ind=3, t=4, [1,1,2]) -> no valid path
//             -> PICK 5: solve(ind=4, t=1, [1,1,5]) -> no valid path  
//             -> PICK 6: solve(ind=5, t=0, [1,1,6]) -> ✅ Found [1,1,6]
//        -> NOT-PICK: solve(ind=2, t=7, [1])
//             -> PICK 2: solve(ind=3, t=5, [1,2])
//                  -> PICK 5: solve(ind=4, t=0, [1,2,5]) -> ✅ Found [1,2,5]
//             -> PICK 7: solve(ind=6, t=0, [1,7]) -> ✅ Found [1,7]
//   -> NOT-PICK (skip all 1s): solve(ind=2, t=8, [])
//        -> PICK 2: solve(ind=3, t=6, [2])
//             -> PICK 6: solve(ind=5, t=0, [2,6]) -> ✅ Found [2,6]
//
// Final Result: [[1,1,6], [1,2,5], [1,7], [2,6]]
//
// COMPARISON WITH COMBINATION SUM I:
// ----------------------------------
// | Aspect              | Combination Sum I        | Combination Sum II           |
// |---------------------|--------------------------|------------------------------|
// | Element reuse       | Unlimited                | Once only                    |
// | Duplicate elements  | No duplicates in input   | May have duplicates          |
// | After PICK          | Stay at same index (i)   | Move to next index (i+1)     |
// | Skip duplicates     | Not needed               | Required to avoid dup combos |
// | Sorting             | Optional                 | Required                     |

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
            solve(ind + 1, target - arr[ind], arr, ans, ds);  // Move to next index
            ds.pop_back();  // Backtrack
        }

        // NOT-PICK: Skip all duplicates of current element
        int nextInd = ind + 1;
        while (nextInd < arr.size() && arr[nextInd] == arr[ind]) {
            nextInd++;
        }
        solve(nextInd, target, arr, ans, ds);
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> ds;
        sort(candidates.begin(), candidates.end());  // Sort to handle duplicates
        solve(0, target, candidates, ans, ds);
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    vector<vector<int>> result = sol.combinationSum2(candidates, target);

    cout << "Combinations that sum to " << target << ":" << endl;
    for (auto& combination : result) {
        cout << "[ ";
        for (int num : combination) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}