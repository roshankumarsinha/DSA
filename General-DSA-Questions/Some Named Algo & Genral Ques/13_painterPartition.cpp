// 🧩 Problem Statement
// You are given:
//  1.  n boards of different lengths: arr[]
//  2.  k painters
//  3.  Time taken to paint 1 unit of board = 1 unit (or given as time per unit)
// Each painter can:
//  1.  Only paint contiguous sections of the boards.
//  2.  Start painting immediately after the previous one finishes or simultaneously (parallel painting).
// Goal: Assign boards to k painters so that the time to paint all boards is minimized.

// Notes : https://takeuforward.org/arrays/painters-partition-problem/

// Example:
// Input: arr[] = {10, 20, 30, 40}, k = 2
// Output: 60
// Explanation:
// Painter 1 paints boards of lengths 10 and 20 and 30 (total 60 units).
// Painter 2 paints the board of length 40 (total 40 units).
// The maximum time taken by any painter is 60 units, which is minimized.



// 🧩 Problem Statement
// You are given an array of non-negative integers nums[] and an integer k.
//  1.  Split the array into k non-empty, contiguous subarrays such that the maximum sum among these subarrays is minimized.
// Return this minimized maximum sum.

// Example:
// Input: arr[] = {10, 20, 30, 40}, k = 2
// Output: 60
// Explanation:
// 1st Subarray: [10, 20, 30] → sum = 60
// 2nd Subarray: [40] → sum = 40
// The maximum sum among these subarrays is 60, which is minimized.

// Notes : https://takeuforward.org/arrays/split-array-largest-sum/


// Both the problems are same and it is same as the "Allocate Minimum Number of Pages" problem.
// Whereever in question we have to find Minimize the Maximum Sum, please think about binary search taking example of Allocate Minimum Number of Pages problem.