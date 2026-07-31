// Theory of Recursion

// There can be 2 types of question for recursion:-
// 1. Top -> Down (Forward (Parameter Passing)):-
//  a. You pass the answer forward into the next call.
//  b. Idea : Carry the partial answer with you.
//  c. Structure :
//      function solve(n, answerSoFar) {
//          if (base) {
//              console.log(answerSoFar);
//              return;
//          }
//          solve(n - 1, updatedAnswer);
//      }
//  d. Used when :-
//      d1. ✔ No work while coming back
//      d2. ✔ Everything done while going down
// 2. Bottom -> Top (Backtracking (Return Building))
//  a.  You build the answer while returning.
//  b.  Idea : Ask child to solve first, then use their answer.
//  c.  Structure :
//          function f(n) {
//              if (base) return something;
//              const smallAns = f(n - 1);
//              return combine(n, smallAns);
//          }
//  d. Used when :-
//      d1. ✔ Needs backtracking
//      d2. ✔ Stack frames hold unfinished work
//      d3. ✔ Used in Trees, DFS, DP

// Note : For recursion always try to make recursion tree. This will help a lot. For 1 recursion call, the recursion tree will
// be in one direction, which is vertically.

// Theory for multiple recursion call :-
// Note : For multiple recursion call, the recursion tree will be in form of tree, which grows horizontally and vertically.

// Let's take example of fibonacci using recursion :-
// function fib(n) {
//     if (n === 0) return 0;     // Base Case : if n is 0, return 0
//     if (n === 1) return 1;     // Base Case : if n is 1, return 1
//     const last = fib(n - 1);
//     const secondLast = fib(n - 2);
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
// Subsequence -> A continuous/non-continuous sequence, without changing the order of remaining elements.
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

// In JavaScript, arrays are passed by reference just like a C++ vector<int>&, so the same
// push()/pop() backtracking pattern works:
//
// function printSubsequence(idx, arr, temp) {
//     // Base Case: if we processed all elements
//     if (idx === arr.length) {
//         console.log(temp.length === 0 ? "{}" : temp.join(" "));
//         return;
//     }
//     // 1️⃣ Take current element
//     temp.push(arr[idx]);
//     printSubsequence(idx + 1, arr, temp);
//     // Backtrack, and remove the current element so that it is skipped
//     temp.pop();
//     // 2️⃣ Skip current element
//     printSubsequence(idx + 1, arr, temp);
// }
// printSubsequence(0, [3, 1, 2], []);

// You can write in another approach as well : This is more good. Mostly try to use this approach.
// function printSubsequence(idx, arr, temp, res) {
//     res.push([...temp]);   // push a COPY, since temp is mutated during backtracking
//     for (let i = idx; i < arr.length; i++) {
//         temp.push(arr[i]);
//         printSubsequence(i + 1, arr, temp, res);
//         temp.pop();
//     }
// }
//
// IMPORTANT JavaScript note: when storing the current subsequence into the result array,
// always push a COPY ([...temp] or temp.slice()). Pushing `temp` directly stores a reference,
// and later pop()/push() calls would mutate every stored subsequence. In C++ `push_back(ds)`
// copies the vector automatically, so this pitfall is unique to JS reference semantics.

// Time Complexity : n*(2^n), n is to print all the elements in array, so we will be having 2^n arrays.

// After this please study from Learn All Patterns of Subsequences (Theory).
// Link : https://takeuforward.org/data-structure/learn-all-patterns-of-subsequences-theory

// Question : Find all the subsequence which adds upto a target value.
// example : [1,2,1] target: 2
// Output : [1,1], [2]
// Video link : https://www.youtube.com/watch?v=eQCS_v3bw0Q&list=PLgUwDviBIf0rGlzIn_7rsaR2FQ5e6ZOL9&index=7

// Approach will be almost same as printing all subsequence.
// For questions like printing combinations or subsequences, the first thing that should strike your mind is recursion.
// Whenever the problem is related to picking up elements from an array to form a combination, start thinking about the "pick and non-pick" approach.
// At every step, we have two choices:
//  Pick the element at the current index:
//      Increase the sum
//      Check if sum becomes equal to target
//  Not pick the element:
//      Remove the element, and decrease the sum by that element as that element is not picked
//      Check if sum becomes equal to target
//
// function findCombination(ind, target, sum, arr, ans, ds) {
//     // Base case: if we have considered all elements in the array
//     if (ind === arr.length) {
//         // If the target is equal to sum, we have found a valid combination
//         if (target === sum) {
//             ans.push([...ds]);  // Add a COPY of the current combination to the result
//         }
//         return;
//     }
//     // Pick the element and add it to current combination
//     ds.push(arr[ind]);
//     sum = sum + arr[ind];
//     findCombination(ind + 1, target, sum, arr, ans, ds); // Recursive call for picking
//     // We are skipping so, remove the current element from combination
//     ds.pop();
//     sum = sum - arr[ind];
//     findCombination(ind + 1, target, sum, arr, ans, ds); // Recursive call for skipping
// }
// function combinationSum(nums, target) {
//     const ans = [];
//     findCombination(0, target, 0, nums, ans, []);
//     return ans;
// }

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

// Question : Modify above question, print/return only whether there EXISTS a subsequence with sum K.
// Change the base condition to return true if answer is found otherwise return false.
//
// function findCombination(ind, target, sum, arr) {
//     if (ind === arr.length) {
//         return target === sum;   // true if found, false otherwise
//     }
//     // Pick
//     const isAnsInPick = findCombination(ind + 1, target, sum + arr[ind], arr);
//     if (isAnsInPick) return true;    // short-circuit: no need to check skip
//     // Skip
//     const isAnsInSkip = findCombination(ind + 1, target, sum, arr);
//     if (isAnsInSkip) return true;
//     return false;
// }

// Question : One more modified version — count how many subsequences match the target.
// Change the base condition to return 1 if answer found else return 0.
//
// function findCombination(ind, target, sum, arr) {
//     if (ind === arr.length) {
//         return target === sum ? 1 : 0;
//     }
//     const countInPick = findCombination(ind + 1, target, sum + arr[ind], arr);
//     const countInSkip = findCombination(ind + 1, target, sum, arr);
//     return countInPick + countInSkip;
// }

// For all the above time complexity will be 2^n
