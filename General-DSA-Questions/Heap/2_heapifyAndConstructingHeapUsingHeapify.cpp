// Write a Heapify function to maintain the max-heap property and construct a max-heap from an array.

// Heapify: Convert an arbitrary array into a heap.
// Heapify will convert array with given index into a heap. So, if index is the root then tree with root as index will be heapified.
// Goal of Heapify is to maintain the Max-Heap property from a given index downwards.
// Approach (max-heap):
// 1. Start from index i and move downwards.
// 2. Compare the element at index i with its children.
// 3. If the element at index i is smaller than either child, swap it with the larger child.
// 4. Repeat steps 2 and 3 until the element at index i is in the correct position.
// 5. Time Complexity: O(log N) for heapifying the entire array.

// Heapify is a recursive function that will be called for each node in the tree.

// To construct a max-heap from an array, we can use the heapify function.
// 1. We start from the last non-leaf node and call heapify on each node in reverse level order.
// 2. The last non-leaf node is at index n/2. The leaf nodes are at index n/2 + 1 to n for a 1-based index.
// 3. We call heapify on each node from n/2 down to 1.

// Time Complexity: O(N) for constructing the heap from an array.
// Time Complexity is O(N) instead of O(N log N) because :-
// 1. Not all heapify calls will take log N time.
// 2. Nodes near bottom of the tree will take less time to heapify.
// 3. Only few nodes at top will take log N time.
// 4. Visualizing Heap Strucure :
//    Height (h)	  Nodes at that height	  Max heapify work per node
//    0 (leaves)	      ~n/2	                        0
//      1	              ~n/4	                        1
//      2	              ~n/8	                        2
//      3	              ~n/16	                        3
//      ...	             ...	                      ...
//     log n	            1	                        log n

// 5. Total work done = n/2 * 0 + n/4 * 1 + n/8 * 2 + n/16 * 3 + ... + 1 * log n
// 6. This is a geometric series and can be simplified to O(N).


#include <iostream>
using namespace std;

// Function for Heapify
void heapify(int* arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int leftChildIndex = 2 * i; // Calculate left child index
    int rightChildIndex = 2 * i + 1; // Calculate right child index

    // Check if left child exists and is greater than current largest
    if (leftChildIndex <= n && arr[leftChildIndex] > arr[largest]) {
        largest = leftChildIndex;
    }

    // Check if right child exists and is greater than current largest
    if (rightChildIndex <= n && arr[rightChildIndex] > arr[largest]) {
        largest = rightChildIndex;
    }

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected subtree
    }
}

// Function to build the max-heap from an array
void buildHeap(int* arr, int n) {
    // Start from the last non-leaf node and heapify each node, we are taking 1-based indexing
    // We are skipping all leaf node which is from n/2 + 1 to n
    for (int i = n / 2; i > 0; i--) {
        heapify(arr, n, i);
    }
}

int main() {
    int arr[] = {-1, 10, 20, 5, 6, 1, 8}; // Example array (1-based indexing)
    int n = 6; // Size of the array

    buildHeap(arr, n); // Build the max-heap

    cout << "Max-Heap array: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " "; // Print the max-heap
    }
    cout << endl;

    return 0;
}