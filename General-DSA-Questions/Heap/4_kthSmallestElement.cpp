// Write a function to find the kth smallest element in a array using heap.

// Given an array of n elements, find the Kth smallest element using a heap.

// The basic approach is to sort the array and return the kth element.
// However, this approach has a time complexity of O(N log N) due to sorting.
// We can optimize this using a max-heap to find the kth smallest element in O(N log K) time.

// Approach:
// 1. Create a max-heap of size k.
// 2. Insert the first k elements into the max-heap.
// 3. For each remaining element in the array, compare it with the root of the max-heap.
// 4. If the current element is smaller than the root, replace the root with the current element and heapify.
// 5. The root of the max-heap will be the kth smallest element after processing all elements because we are maintaining the k smallest elements in the heap so that the root will be the largest among them.
// 6. Time Complexity: O(N log K) for finding the kth smallest element using a max-heap.
// 7. Space Complexity: O(K) for storing the k smallest elements in the max-heap.

// This approach is efficient for large arrays and small values of k.

#include <iostream>
#include <queue>
using namespace std;

// Function to find the kth smallest element in an array using a max-heap
int kthSmallest(int arr[], int n, int k) {
    // Create a max-heap using priority queue
    priority_queue<int> maxHeap;

    // Insert the first k elements into the max-heap
    for (int i = 0; i < k; i++) {
        maxHeap.push(arr[i]);
    }

    // For each remaining element in the array
    for (int i = k; i < n; i++) {
        // If the current element is smaller than the root of the max-heap
        if (arr[i] < maxHeap.top()) {
            maxHeap.pop(); // Remove the largest element from the heap
            maxHeap.push(arr[i]); // Insert the current element into the heap
        }
    }

    // The root of the max-heap is the kth smallest element
    return maxHeap.top();
}

int main() {
  int arr[] = {7, 10, 4, 3, 20, 15};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 3; // Find the 3rd smallest element
  cout << "The " << k << "rd smallest element is " << kthSmallest(arr, n, k) << endl;
  return 0;
}

// Output: The 3rd smallest element is 7