// Write a program to implement a heap data structure (min-heap or max-heap) using an array. Include functions for insertion, deletion, and heapify operations.

// Insertion: Add a new element to the heap while maintaining the heap property.
// Approach (max-heap):
// 1. Insert the new element at the end of the heap.
// 2. Bubble up the new element to maintain the heap property.
//    2a. Find the parent index of the new element. parentIndex = index / 2, as we are using 1-based indexing.
//    2b. If the new element is greater than its parent, swap them.
//    2c. Repeat steps 2a and 2b until the new element is in the correct position.
// 3. Time Complexity: O(log N) for insertion.

// Deletion: Remove the root element from the heap while maintaining the heap property.
// Approach (max-heap):
// 1. Replace the root element with the last element in the heap. We will move the last element to the root or first index.
// 2. Decrease the size of the heap.
// 3. Bubble down the new root element to maintain the heap property.
//    3a. Find the left and right child indices of the new root.
//    3b. Compare the new root with its children.
//    3c. If the new root is smaller than either child, swap it with the larger child.
//    3d. Repeat steps 3a, 3b, and 3c until the new root is in the correct position.
// 4. Time Complexity: O(log N) for deletion.


#include <iostream>
using namespace std;

class MaxHeap {
private:
    int* heap; // Array to store the heap elements
    int capacity; // Maximum size of the heap
    int size; // Current number of elements in the heap
public:
    MaxHeap(int capacity) {
        this->capacity = capacity;
        heap = new int[capacity];
        heap[0] = -1; // Not used, as we are using 1-based indexing
        size = 0;
    }

    // Function to insert a new element into the max-heap
    void insertion(int value) {
        if (size == capacity) {
            cout << "Heap is full. Cannot insert " << value << endl;
            return;
        }

        size = size + 1; // Increase the size of the heap, as we are adding a new element, and we are using 1-based indexing
        heap[size] = value; // Insert the new element at the end of the heap
        int index = size; // Start from the last index

        // Bubble up the new element to maintain the max-heap property, where bubbling up means moving the element up the heap until the max-heap property is satisfied
        while (index > 1) {
            int parentIndex = index / 2; // Calculate the parent index
            if (heap[parentIndex] < heap[index]) {
                swap(heap[parentIndex], heap[index]); // Swap the parent and child if the child is greater
                index = parentIndex; // Move up to the parent index
            } else {
                break; // If the max-heap property is satisfied, break the loop
            }
        }
    }

    // Function to delete the root element (maximum element) from the max-heap
    int deletion() {
        if (size == 0) {
            cout << "Heap is empty. Cannot delete." << endl;
            return -1; // Return -1 if the heap is empty
        }

        // Store the root element to return later
        int root = heap[1];
        heap[1] = heap[size]; // Move the last element to the root, and now we have to find correct position for this elemen
        size = size - 1; // Decrease the size of the heap, since we are removing the root element

        // Bubble down the new root to maintain the max-heap property
        int index = 1; // Start from the root index
        while (index < size) {
            int leftChildIndex = 2 * index; // Calculate the left child index
            int rightChildIndex = 2 * index + 1; // Calculate the right child index
            int largestIndex = index; // Assume the current index is the largest

            // Find the largest among children, whether it is left or right child
            // Whichever is greater, we will swap with that child

            // Check if left child exists and is greater than current largest
            if (leftChildIndex < size && heap[leftChildIndex] > heap[largestIndex]) {
                largestIndex = leftChildIndex;
            }

            // Check if right child exists and is greater than current largest
            if (rightChildIndex < size && heap[rightChildIndex] > heap[largestIndex]) {
                largestIndex = rightChildIndex;
            }

            // If largest is not current index, swap and continue bubbling down
            if (largestIndex != index) {
                swap(heap[index], heap[largestIndex]);
                index = largestIndex; // Move down to the largest child's index
            } else {
                break; // If max-heap property is satisfied, break the loop
            }
        }

        return root; // Return the deleted root element
    }

    // Function to display the heap elements    
    void display() {
        cout << "Heap elements: ";
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    ~MaxHeap() {
        delete[] heap; // Free the allocated memory
    }
};

int main() {
    MaxHeap maxHeap(10); // Create a max-heap with a capacity of 10

    maxHeap.insertion(50);
    maxHeap.insertion(30);
    maxHeap.insertion(40);
    maxHeap.insertion(10);
    maxHeap.insertion(20);
    maxHeap.insertion(60);


    maxHeap.display(); // Display the heap elements

    cout << "Deleted root element: " << maxHeap.deletion() << endl; // Delete the root element (maximum element)
    maxHeap.display(); // Display the heap elements after deletion
    cout << "Deleted root element: " << maxHeap.deletion() << endl; // Delete the root element (maximum element)
    maxHeap.display(); // Display the heap elements after deletion

    return 0;
}

// Tree Structure:
//         60
//        /  \
//       30   50
//      /  \  /
//     10  20 40