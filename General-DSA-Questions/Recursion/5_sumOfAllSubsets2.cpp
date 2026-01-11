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
//
// DIFFERENCE FROM SUBSETS I (no duplicates):
// - Subsets I: Simple pick/not-pick, all 2^n subsets are unique
// - Subsets II: Must handle duplicates carefully to avoid [1,2] appearing twice

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
// WHY DOES THIS WORK?
// -------------------
// Consider nums = [1, 2, 2] (sorted)
// At any recursion level, if we pick the first '2', we explore all subsets containing
// that 2 at that position. If we then try the second '2' at the SAME level, we'd
// generate the same subsets again!
//
// By skipping duplicates at the same level (i > index && nums[i] == nums[i-1]),
// we ensure each unique subset is generated exactly once.
//
// WHY COLLECT AT EVERY STEP (not just at base case)?
// --------------------------------------------------
// Unlike Combination Sum where we need a specific target, here we want ALL subsets.
// So we add the current subset to result at EVERY step, not just at the end.
// This includes:
//   - Empty subset (added at the start)
//   - Partial subsets (added as we build them)
//   - Complete subsets (when we've considered all elements)
//
// ALGORITHM:
// ----------
// 1. Sort the array (to group duplicates together)
// 2. At each call, add current subset to result
// 3. For each element from 'index' to end:
//    a. Skip if current == previous at same level (i > index && nums[i] == nums[i-1])
//    b. Add element to current subset
//    c. Recurse with index = i+1
//    d. Backtrack: remove the element
//
// Time Complexity: O(2^n * n) - 2^n subsets, each taking O(n) to copy
// Space Complexity: O(n) for recursion stack + O(2^n * n) for storing subsets
//
// RECURSION TREE for nums = [1, 2, 2] (sorted):
// ----------------------------------------------
//
//                           solve(idx=0, curr=[])
//                           Add [] to result
//                     /          |           \
//              Pick 1         Pick 2(idx=1)   Skip 2(idx=2) - duplicate!
//        solve(idx=1,[1])   solve(idx=2,[2])
//        Add [1] to result  Add [2] to result
//          /      \              |
//    Pick 2     Skip 2      Pick 2(idx=2)
// solve(idx=2,[1,2]) (dup!)  solve(idx=3,[2,2])
// Add [1,2] to result        Add [2,2] to result
//      |
//   Pick 2(idx=2)
// solve(idx=3,[1,2,2])
// Add [1,2,2] to result
//
// Result: [[], [1], [1,2], [1,2,2], [2], [2,2]]
//
// DETAILED TRACE for nums = [1, 2, 2]:
// -------------------------------------
// solve(idx=0, curr=[])
//   Add [] ✅
//   i=0: Pick 1 -> solve(idx=1, [1])
//        Add [1] ✅
//        i=1: Pick 2 -> solve(idx=2, [1,2])
//             Add [1,2] ✅
//             i=2: Pick 2 -> solve(idx=3, [1,2,2])
//                  Add [1,2,2] ✅
//                  (no more elements)
//        i=2: Skip 2 (i=2 > idx=1 && nums[2]==nums[1]) ❌
//   i=1: Pick 2 -> solve(idx=2, [2])
//        Add [2] ✅
//        i=2: Pick 2 -> solve(idx=3, [2,2])
//             Add [2,2] ✅
//   i=2: Skip 2 (i=2 > idx=0 && nums[2]==nums[1]) ❌
//
// Final Result: [[], [1], [1,2], [1,2,2], [2], [2,2]]

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    void solve(int index, vector<int>& nums, vector<int>& current, vector<vector<int>>& result) {
        // Add current subset to result (collect at every step)
        result.push_back(current);

        for (int i = index; i < nums.size(); i++) {
            // Skip duplicates at the same recursion level
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }

            current.push_back(nums[i]);
            solve(i + 1, nums, current, result);
            current.pop_back();  // Backtrack
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        sort(nums.begin(), nums.end());  // Sort to handle duplicates
        solve(0, nums, current, result);
        return result;
    }
};

// =====================================================================================
// APPROACH 2: Pick / Not-Pick Pattern
// =====================================================================================
//
// INTUITION:
// -----------
// Same binary decision pattern, but with a twist for handling duplicates:
//   1. PICK: Include current element, move to next index
//   2. NOT-PICK: Skip ALL occurrences of current element (same as Combination Sum II)
//
// WHY SKIP ALL DUPLICATES ON NOT-PICK?
// ------------------------------------
// If we decide NOT to include element X, we must skip ALL of X's duplicates.
// Otherwise, we'd generate the same subset multiple times.
//
// Example: nums = [1, 2, 2]
// If at index 1 we decide NOT to pick first '2':
//   - Bad: Move to index 2, might pick second '2' -> generates subsets we shouldn't
//   - Good: Skip to index 3, no more 2s to consider -> correct unique subsets
//
// WHY COLLECT AT BASE CASE (index == n)?
// --------------------------------------
// In pick/not-pick, we build the complete subset through the recursion path.
// We only add it when we've made decisions for ALL elements (reached the end).
//
// ALGORITHM:
// ----------
// 1. Sort the array
// 2. Base case: If index == n, add current subset to result
// 3. PICK: Add current element, recurse with index+1
// 4. NOT-PICK: Skip all duplicates of current element, then recurse
//
// Time Complexity: O(2^n * n)
// Space Complexity: O(n) recursion stack + O(2^n * n) for storing subsets
//
// RECURSION TREE for nums = [1, 2, 2] (sorted):
// ----------------------------------------------
//
//                        solve(ind=0, ds=[])
//                        /                 \
//                   PICK 1               NOT-PICK
//            solve(ind=1, ds=[1])     solve(ind=1, ds=[])
//              /            \            /            \
//         PICK 2         NOT-PICK   PICK 2         NOT-PICK
//   solve(ind=2,[1,2])  solve(ind=3,[1])  solve(ind=2,[2])  solve(ind=3,[])
//      /        \         Add [1] ✅     /        \         Add [] ✅
//  PICK 2    NOT-PICK              PICK 2    NOT-PICK
// solve(ind=3,[1,2,2]) solve(ind=3,[1,2])  solve(ind=3,[2,2]) solve(ind=3,[2])
//  Add [1,2,2] ✅     Add [1,2] ✅       Add [2,2] ✅      Add [2] ✅
//
// Result: [[1,2,2], [1,2], [1], [2,2], [2], []]
//
// DETAILED TRACE for nums = [1, 2, 2]:
// -------------------------------------
// solve(ind=0, ds=[])
//   -> PICK 1: solve(ind=1, [1])
//        -> PICK 2: solve(ind=2, [1,2])
//             -> PICK 2: solve(ind=3, [1,2,2]) -> Add [1,2,2] ✅
//             -> NOT-PICK (skip all 2s): solve(ind=3, [1,2]) -> Add [1,2] ✅
//        -> NOT-PICK (skip all 2s): solve(ind=3, [1]) -> Add [1] ✅
//   -> NOT-PICK: solve(ind=1, [])
//        -> PICK 2: solve(ind=2, [2])
//             -> PICK 2: solve(ind=3, [2,2]) -> Add [2,2] ✅
//             -> NOT-PICK (skip all 2s): solve(ind=3, [2]) -> Add [2] ✅
//        -> NOT-PICK (skip all 2s): solve(ind=3, []) -> Add [] ✅
//
// Final Result: [[1,2,2], [1,2], [1], [2,2], [2], []]
//
// COMPARISON OF BOTH APPROACHES:
// ------------------------------
// | Aspect              | For-Loop Approach        | Pick/Not-Pick Approach    |
// |---------------------|--------------------------|---------------------------|
// | When to add subset  | At every recursive call  | Only at base case (ind==n)|
// | Skip duplicates     | i > index && same value  | Skip all dups on NOT-PICK |
// | Tree structure      | Multi-way branching      | Binary branching          |
// | Code simplicity     | Slightly simpler         | More explicit decisions   |

class Solution2 {
public:
    void solve(int ind, vector<int>& nums, vector<int>& ds, vector<vector<int>>& ans) {
        // Base case: processed all elements
        if (ind == nums.size()) {
            ans.push_back(ds);
            return;
        }

        // PICK: Include current element
        ds.push_back(nums[ind]);
        solve(ind + 1, nums, ds, ans);
        ds.pop_back();  // Backtrack

        // NOT-PICK: Skip all duplicates of current element
        int nextInd = ind + 1;
        while (nextInd < nums.size() && nums[nextInd] == nums[ind]) {
            nextInd++;
        }
        solve(nextInd, nums, ds, ans);
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> ds;
        sort(nums.begin(), nums.end());  // Sort to handle duplicates
        solve(0, nums, ds, ans);
        return ans;
    }
};

// =====================================================================================
// KEY DIFFERENCES FROM RELATED PROBLEMS:
// =====================================================================================
//
// | Problem              | Duplicates in Input | Element Reuse | Skip Logic              |
// |----------------------|---------------------|---------------|-------------------------|
// | Subsets I            | No                  | No            | None needed             |
// | Subsets II (this)    | Yes                 | No            | Skip dups at same level |
// | Combination Sum I    | No                  | Unlimited     | None needed             |
// | Combination Sum II   | Yes                 | No            | Skip dups at same level |
//
// COMMON PATTERN FOR HANDLING DUPLICATES:
// ----------------------------------------
// 1. SORT the array first
// 2. For-Loop approach: if (i > index && nums[i] == nums[i-1]) continue;
// 3. Pick/Not-Pick: On NOT-PICK, skip ALL duplicates before recursing

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 2};

    vector<vector<int>> result = sol.subsetsWithDup(nums);

    cout << "All unique subsets of [1, 2, 2]:" << endl;
    for (auto& subset : result) {
        cout << "[ ";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    // Test with another example
    cout << "\nTest with [4, 4, 4, 1, 4]:" << endl;
    vector<int> nums2 = {4, 4, 4, 1, 4};
    vector<vector<int>> result2 = sol.subsetsWithDup(nums2);

    for (auto& subset : result2) {
        cout << "[ ";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}

