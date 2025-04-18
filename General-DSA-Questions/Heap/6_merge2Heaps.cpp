// Write a function to merge two heaps into a single heap.

// Approach:
// 1. Combine both heap arrays into a single array.
// 2. Build a max-heap from the combined array using the heapify function.
// 3. The resulting array will be a valid max-heap.
// 4. Time Complexity: O(N + M) for merging two heaps of sizes N and M.
// 5. Space Complexity: O(N + M) for storing the combined array.

#include <iostream>
#include <vector>
using namespace std;

// Function to heapify a subtree rooted at index i
void heapify(vector<int>& arr, int n, int i) {
    // Using 0-based indexing
    int largest = i; // Initialize largest as root
    int leftChildIndex = 2 * i + 1; // Calculate left child index
    int rightChildIndex = 2 * i + 2; // Calculate right child index

    // Check if left child exists and is greater than current largest
    if (leftChildIndex < n && arr[leftChildIndex] > arr[largest]) {
        largest = leftChildIndex;
    }

    // Check if right child exists and is greater than current largest
    if (rightChildIndex < n && arr[rightChildIndex] > arr[largest]) {
        largest = rightChildIndex;
    }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected subtree
    }
}

// Function to build a max-heap from an array
void buildHeap(vector<int>& arr, int n) {
    // Start from the last non-leaf node and heapify each node
    // For 0-based indexing, the last non-leaf node is at index n/2 - 1
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Merge 2 max-heaps
vector<int> mergeHeaps(vector<int>& heap1, vector<int>& heap2) {
    // Combine both heaps into a single array
    vector<int> mergedHeap = heap1;
    mergedHeap.insert(mergedHeap.end(), heap2.begin(), heap2.end());

    // Build a max-heap from the combined array
    buildHeap(mergedHeap, mergedHeap.size());

    return mergedHeap; // Return the merged max-heap
}

int main() {
    vector<int> heap1 = {10, 5, 6, 2}; // Example max-heap 1
    vector<int> heap2 = {12, 7, 9}; // Example max-heap 2

    vector<int> mergedHeap = mergeHeaps(heap1, heap2); // Merge the two heaps

    cout << "Merged Max-Heap: ";
    for (int i : mergedHeap) {
        cout << i << " "; // Print the merged max-heap
    }
    cout << endl;

    return 0;
}

// Output:
// Merged Max-Heap: 12 10 9 2 7 5 6

// If we use priority queue to merge two heaps, we can do it in O(N + M) time complexity.
// Function to merge two heaps using priority queue
// vector<int> mergeHeapsUsingPriorityQueue(vector<int>& heap1, vector<int>& heap2) {
//     // Create a max-heap using priority queue
//     priority_queue<int> maxHeap;
//
//     // Insert elements from both heaps into the max-heap
//     for (int i : heap1) {
//         maxHeap.push(i);
//     }
//     for (int i : heap2) {
//         maxHeap.push(i);
//     }
//
//     // Create a vector to store the merged heap
//     vector<int> mergedHeap;
//     while (!maxHeap.empty()) {
//         mergedHeap.push_back(maxHeap.top()); // Add the root of the max-heap to the merged heap
//         maxHeap.pop(); // Remove the root from the max-heap
//     }
//
//     return mergedHeap; // Return the merged max-heap
// }