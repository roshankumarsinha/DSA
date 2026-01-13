// Theory of Recursion

// There can be 2 types of question for recursion:-
// 1. Top -> Down (Forward (Parameter Passing)):-
//  a. You pass the answer forward into the next call.
//  b. Idea : Carry the partial answer with you.
//  c. Structure : 
//      void solve(n, answerSoFar){
//          if(base) {
//              print(answerSoFar);
//              return;
//          }
//          solve(n-1, updatedAnswer);
//      }
//  d. Used when :-
//      d1. ✔ No work while coming back
//      d2. ✔ Everything done while going down
// 2. Bottom -> Top (Backtracking (Return Building))
//  a.  You build the answer while returning.
//  b.  Idea : Ask child to solve first, then use their answer.
//  c.  Structure : 
//          return f(n) {
//              if(base) return something;
//              smallAns = f(n-1);
//              return combine(n, smallAns);
//          }
//  d. Used when :-
//      d1. ✔ Needs backtracking
//      d2. ✔ Stack frames hold unfinished work
//      d3. ✔ Used in Trees, DFS, DP

// Note : For recursion always try to make recursion tree. This will help a lot. For 1 recursion call, the recursion tree will
// be in one direction, which is vertically.



// Theory for multiple recursion call :-
// Note : For multiple recursion call, the recursion tree will be in for of tree, which is grow horizontally and vertically.

// Let's take example of fibonacci using recursion :-
// int fib(int n){
//     if(n == 0) return 0;     Base Case : if n is 0, return 0
//     if(n == 1) return 1;     Base Case : if n is 1, return 1
//     int last = fib(n-1);
//     int secondLast = fib(n-2);
//     return last + secondLast;
// }

// When we make recursion tree, note first everytime fib(n-1) will run and then only fib(n-2) will run.
// Recursion tree :-
//                               fib(5)=5
//                            /             \
//                      fib(4)=3              fib(3)=2
//                    /        \              /        \
//              fib(3)=2      fib(2)=1   fib(2)=1      fib(1)=1
//             /      \        /      \   /      \
//        fib(2)=1   fib(1)=1 fib(1)=1 fib(0)=0 fib(1)=1 fib(0)=0
//        /     \
//   fib(1)=1 fib(0)=0

// Time Complexity is 2^n. Because each one is calling twice. Each recursion calls 2 sub-recursion calls.

// Recursion on Subsequence.
// Subsequence -> A continous/non-continous sequences, without changing the order of remaining elements.
// ✔ You can skip elements
// ✔ You cannot change the order
// Example :- Total subsequence of [3, 1, 2] are :-
// [], [3], [1], [2], [3,1], [3,2], [1,2], [3,1,2]. Total = 8. Note: [3,2,1] is not subsequence because it violates the order rule.

// Question :- Print all the subsequence
// Video link : https://www.youtube.com/watch?v=AxNNVECce8c&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=6
// Notes : https://takeuforward.org/data-structure/power-set-print-all-the-possible-subsequences-of-the-string
// At every element you have 2 choices: Include OR Exclude the elements

// Example : [3,1,2]
//                                     idx=0 , temp = { }
//                                /                           \
//                         take 3                               skip 3
//                    idx=1 , temp={3}                     idx=1 , temp={ }
//                      /                \                   /               \
//               take 1                   skip 1        take 1               skip 1
//        idx=2 , temp={3,1}         idx=2 , temp={3}  idx=2 , temp={1}    idx=2 , temp={ }
//             /        \                /       \        /       \           /       \
//      take 2       skip 2        take 2      skip 2 take 2    skip 2    take 2     skip 2
// idx=3,temp={3,1,2} idx=3,{3,1} idx=3,{3,2} idx=3,{3} idx=3,{1,2} idx=3,{1} idx=3,{2} idx=3,{ }

// #include <bits/stdc++.h>
// using namespace std;

// void printSubsequence(int idx, vector<int> &arr, vector<int> &temp)
// {
//     // Base Case: if we processed all elements
//     if (idx == arr.size())
//     {
//         // Print one subsequence
//         if (temp.size() == 0) cout << "{}";
//         else
//         {
//             for (int x : temp) cout << x << " ";
//         }
//         cout << endl;
//         return;
//     }

//     // 1️⃣ Take current element
//     temp.push_back(arr[idx]);
//     printSubsequence(idx + 1, arr, temp);

//     // Backtrack, and remove the current element so that it is skipped
//     temp.pop_back();

//     // 2️⃣ Skip current element
//     printSubsequence(idx + 1, arr, temp);
// }

// int main()
// {
//     vector<int> arr = {3, 1, 2};
//     vector<int> temp;
//     printSubsequence(0, arr, temp);
// }

// You can write in another approach as well : This is more good. Mostly try to use this approach.
// void printSubsequence(int idx, vector<int> &arr, vector<int> &temp, vectot<vector<int>> &res) {
//     res.push_back(temp);
//     for(int i = idx; i< arr.size(); i++) {
//         temp.push_back(arr[i]);
//         printSubsequence(i + 1, arr, temp, ans);
//         temp.pop_back();
//     }
// }

// Time Complexity : n*(2^n), n is to print all the elements in vector, so we will be javing 2^n vectors.

// After this please study from Learn All Patterns of Subsequences (Theory).
// Link : https://takeuforward.org/data-structure/learn-all-patterns-of-subsequences-theory


// Question : Find all the subsequence which adds upto a target value.
// example : [1,2,1] target: 2
// Output : [1,1], [2]
// Video link : https://www.youtube.com/watch?v=eQCS_v3bw0Q&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=7

// Approach will be almost same as printing all subsequence.
// For questions like printing combinations or subsequences, the first thing that should strike your mind is recursion.
// Whenever the problem is related to picking up elements from an array to form a combination, start thinking about the “pick and non-pick” approach.
// At every step, we have two choices:
//  Pick the element at the current index:
//      Increase the sum
//      Check if sum becomes equal to target
//  Not pick the element:
//      Remove the element, and decrease the sum by that element as that element is not picked
//      Check if sum becomes equal to target
// class Solution {
//   public:
//     // Function to find all combinations of numbers that sum up to the target
//     void findCombination(int ind, int target, int sum, vector<int>& arr, vector<vector<int>>& ans, vector<int>& ds) {
//         // Base case: if we have considered all elements in the array
//         if (ind == arr.size()) {
//             // If the target is equal to sum, we have found a valid combination
//             if (target == sum) {
//                 ans.push_back(ds);  // Add the current combination to the result
//             }
//             return;
//         }

//         // Recursive case: pick the element if it's less than or equal to the target
//         ds.push_back(arr[ind]);  // Pick the element and add it to current combination
//         sum = sum + arr[ind];    // Increase the sum as we are picking current element
//         findCombination(ind + 1, target, sum, arr, ans, ds); // Recursive call for picking

//         // Skip the current element and move to the next index
//         ds.pop_back(arr[ind]);   // We are skipping so, remove the current element from combination
//         sum = sum - arr[ind];    //  Decrease the sum as we are removing current element
//         findCombination(ind + 1, target, sum, arr, ans, ds); // Recursive call for skipping
//     }

//   public:
//     // Main function to get all combinations
//     vector<vector<int>> combinationSum(vector<int>& nums, int target) {
//         vector<vector<int>> ans;  // To store the result
//         vector<int> ds;  // To store a current combination
//         findCombination(0, target, 0, nums, ans, ds);  // Start the recursive search, (index: 0, target, curr_sum: 0, nums: Given array, ans: to store all vector, ds: to store current vector)
//         return ans;  // Return all valid combinations
//     }
// };

// Recursive tree for above example:
//                                       (0,0,{ })
//                                /                          \
//                         take 1                               skip 1
//                   (1,1,{1})                               (1,0,{ })
//                      /                \                      /                 \
//              take 2                    skip 2          take 2                 skip 2
//         (2,3,{1,2})                 (2,1,{1})      (2,2,{2})               (2,0,{ })
//            /        \                   /      \          /      \              /      \
//     take1        skip1            take1      skip1   take1     skip1       take1     skip1
// (3,4,{1,2,1}) (3,3,{1,2})    (3,2,{1,1}) (3,1,{1}) (3,3,{2,1}) (3,2,{2}) (3,1,{1}) (3,0,{ })
//    ❌            ❌                ✅          ❌          ❌        ✅        ❌        ❌



// Question : Modify above question, with print only 1 subsequence which matches the target. Check if there exists a subsequence with sum K.
// Change the base condition to return true if answer if found otherwise return false.

// class Solution {
//   public:
//     // Function to find all combinations of numbers that sum up to the target
//     bool findCombination(int ind, int target, int sum, vector<int>& arr, vector<int>& ds) {
//         // Base case: if we have considered all elements in the array
//         if (ind == arr.size()) {
//             // If the target is equal to sum, we have found a valid combination
//             if (target == sum) {
//                 return true; // We found the answer, so return true
//             }
//             return false;    // Otherwise return false
//         }

//         // Recursive case: pick the element if it's less than or equal to the target
//         ds.push_back(arr[ind]);  // Pick the element and add it to current combination
//         sum = sum + arr[ind];    // Increase the sum as we are picking current element
//         bool isAnsInPick = findCombination(ind + 1, target, sum, arr, ds); // Recursive call for picking
//         if (isAnsInPick) return true;    // If we found one result in pick then just pass true above and no need to check the skip recursive call

//         // Skip the current element and move to the next index
//         ds.pop_back(arr[ind]);   // We are skipping so, remove the current element from combination
//         sum = sum - arr[ind];    //  Decrease the sum as we are removing current element
//         bool isAnsInSkip = findCombination(ind + 1, target, sum, arr, ds); // Recursive call for skipping
//         if (isAnsInSkip) return true;    // Similarly, if we found one result in skip then just return true to avoid next recursive call.

//         return false;    // If we still didn't get answer then return false to parent, and still check next recursive call
//     }

//   public:
//     // Main function to get all combinations
//     bool combinationSum(vector<int>& nums, int target) {
//         vector<int> ds;  // To store a current combination
//         return findCombination(0, target, 0, nums, ds);  // Start the recursive search, (index: 0, target, curr_sum: 0, nums: Given array, ds: to store current vector)
//     }
// };



// Question : One more modify version of this is to find count of how many subsequence matches the target.
// Chnage the base condition just to return 1 if answer found else return 0 if not found.

// class Solution {
//   public:
//     // Function to find all combinations of numbers that sum up to the target
//     int findCombination(int ind, int target, int sum, vector<int>& arr) {
//         // Base case: if we have considered all elements in the array
//         if (ind == arr.size()) {
//             // If the target is equal to sum, we have found a valid combination
//             if (target == sum) {
//                 return 1; // We found the answer, so return 1, which means it contribute one extra to answer
//             }
//             return 0;    // Otherwise return 0, means it won't increase the count
//         }

//         // Recursive case: pick the element if it's less than or equal to the target
//         sum = sum + arr[ind];    // Increase the sum as we are picking current element
//         int countInPick = findCombination(ind + 1, target, sum, arr); // Recursive call for picking

//         // Skip the current element and move to the next index
//         sum = sum - arr[ind];    //  Decrease the sum as we are removing current element
//         int countInSkip = findCombination(ind + 1, target, sum, arr); // Recursive call for skipping

//         return countInPick + countInSkip;    // Return total count to parent how many counts are being founded.
//     }

//   public:
//     // Main function to get all combinations
//     int combinationSum(vector<int>& nums, int target) {
//         return findCombination(0, target, 0, nums);  // Start the recursive search, (index: 0, target, curr_sum: 0, nums: Given array)
//     }
// };

// For all the above time complexity will be 2^n













