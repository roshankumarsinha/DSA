// Given an array print all the sum of the subset generated from it, in the increasing order.
// Output should be printed in increasing of sum.

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
// WHY PICK/NOT-PICK WORKS PERFECTLY HERE?
// ---------------------------------------
// For an array of n elements, there are exactly 2^n subsets.
// Each element can either be IN the subset or NOT IN the subset.
// This maps perfectly to our binary decision tree!
//
// BASE CASE:
// ----------
// When we reach index == n (processed all elements), the current sum
// represents one complete subset's sum. Add it to the result.
//
// ALGORITHM:
// ----------
// 1. Start with index=0 and sum=0
// 2. At each index:
//    a. PICK: Recurse with (index+1, sum + arr[index])
//    b. NOT-PICK: Recurse with (index+1, sum)
// 3. Base case: When index == n, add sum to result
// 4. Sort the result at the end
//
// Time Complexity: O(2^n + 2^n * log(2^n)) = O(2^n * n) for generating + sorting
// Space Complexity: O(2^n) to store all subset sums + O(n) recursion stack
//
// RECURSION TREE for arr = [2, 3]:
// ---------------------------------
//
//                        solve(idx=0, sum=0)
//                        /                \
//                   PICK 2              NOT-PICK
//            solve(idx=1, sum=2)     solve(idx=1, sum=0)
//              /          \            /          \
//         PICK 3      NOT-PICK    PICK 3      NOT-PICK
//    solve(idx=2,sum=5) solve(idx=2,sum=2) solve(idx=2,sum=3) solve(idx=2,sum=0)
//         |                  |                  |                  |
//    Add 5 to result    Add 2 to result    Add 3 to result    Add 0 to result
//
// Result before sorting: [5, 2, 3, 0]
// Result after sorting: [0, 2, 3, 5]
//
// DETAILED TRACE for arr = [5, 2, 1]:
// ------------------------------------
// solve(idx=0, sum=0)
//   -> PICK 5: solve(idx=1, sum=5)
//        -> PICK 2: solve(idx=2, sum=7)
//             -> PICK 1: solve(idx=3, sum=8) -> Add 8 ✅
//             -> NOT-PICK: solve(idx=3, sum=7) -> Add 7 ✅
//        -> NOT-PICK: solve(idx=2, sum=5)
//             -> PICK 1: solve(idx=3, sum=6) -> Add 6 ✅
//             -> NOT-PICK: solve(idx=3, sum=5) -> Add 5 ✅
//   -> NOT-PICK: solve(idx=1, sum=0)
//        -> PICK 2: solve(idx=2, sum=2)
//             -> PICK 1: solve(idx=3, sum=3) -> Add 3 ✅
//             -> NOT-PICK: solve(idx=3, sum=2) -> Add 2 ✅
//        -> NOT-PICK: solve(idx=2, sum=0)
//             -> PICK 1: solve(idx=3, sum=1) -> Add 1 ✅
//             -> NOT-PICK: solve(idx=3, sum=0) -> Add 0 ✅
//
// Collected sums: [8, 7, 6, 5, 3, 2, 1, 0]
// After sorting: [0, 1, 2, 3, 5, 6, 7, 8]
//
// WHY SORT AT THE END?
// --------------------
// The recursion doesn't generate sums in sorted order (it follows tree traversal).
// We sort once at the end which is O(2^n * log(2^n)) = O(2^n * n).
// Alternative: Use a min-heap or multiset, but sorting is simpler.
//
// COMPARISON WITH COMBINATION SUM PROBLEMS:
// -----------------------------------------
// | Aspect              | Subset Sum              | Combination Sum          |
// |---------------------|-------------------------|--------------------------|
// | What to track       | Only sum                | Actual combination       |
// | Output              | List of sums            | List of combinations     |
// | Element reuse       | No (each used once)     | Depends on variant       |
// | Need backtracking   | No (just passing sum)   | Yes (push/pop elements)  |

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    void solve(int index, int sum, vector<int>& arr, vector<int>& result) {
        // Base case: processed all elements
        if (index == arr.size()) {
            result.push_back(sum);
            return;
        }

        // PICK: Include current element in subset
        solve(index + 1, sum + arr[index], arr, result);

        // NOT-PICK: Exclude current element from subset
        solve(index + 1, sum, arr, result);
    }

    vector<int> subsetSums(vector<int>& arr) {
        vector<int> result;
        solve(0, 0, arr, result);
        sort(result.begin(), result.end());  // Sort in increasing order
        return result;
    }
};

