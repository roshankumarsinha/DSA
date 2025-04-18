// Write a function to find the kth largest sum of a subarray in an array.

// Given an array arr[] of size n and an integer k, find the kth largest sum of any contiguous subarray.
// Example:
// Input: arr[] = {20, -5, -1} , k = 3
// Contiguous subarrays and their sums are:
// 1. {20} -> 20
// 2. {20, -5} -> 15
// 3. {20, -5, -1} -> 14
// 4. {-5} -> -5
// 5. {-5, -1} -> -6
// 6. {-1} -> -1
// Sorting the sums gives us: {20, 15, 14, -1, -5, -6}
// The 3rd largest sum is 14.

// Approach: (Brute Force)
// 1. Generate all possible contiguous subarrays and calculate their sums.
// 2. Sort the sums in descending order.
// 3. Return the kth largest sum.
// 4. Time Complexity: O(N^2 log N) for generating subarrays and sorting.
// 5. Space Complexity: O(N) for storing the sums.

// Another Approach: (using min-heap):
// 1. Iterate all possible subarrays using two loops.
// 2. Compute their sum.
// 3. Maintain a min heap of size k:
//    a.  If heap size < k, push the sum.
//    b.  Else, compare and replace smallest if current sum is larger.
// 4. This way, after processing all subarrays, the top of the heap is the Kth largest.
// 5. Time Complexity: O(N^2 log K) for generating subarrays and maintaining the heap.
// 6. Space Complexity: O(K) for storing the k largest sums in the min-heap.

#include <iostream>
#include <queue>
using namespace std;

// Function to find the kth largest sum of a subarray
int kthLargestSumSubarray(int arr[], int n, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap to store the k largest sums

    // Iterate through all possible subarrays
    for (int i = 0; i < n; i++) {
        int sum = 0; // Initialize sum for the current subarray
        for (int j = i; j < n; j++) {
            sum += arr[j]; // Calculate the sum of the current subarray

            // If heap size is less than k, push the sum
            if (minHeap.size() < k) {
                minHeap.push(sum);
            } else if (sum > minHeap.top()) { // If current sum is larger than the smallest in the heap
                minHeap.pop(); // Remove the smallest sum
                minHeap.push(sum); // Add the current sum
            }
        }
    }

    return minHeap.top(); // The top of the min-heap is the kth largest sum
}

int main() {
    int arr[] = {20, -5, -1}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; // Find the 3rd largest sum

    int result = kthLargestSumSubarray(arr, n, k);
    cout << "The " << k << "rd largest sum of a subarray is: " << result << endl;

    return 0;
}
