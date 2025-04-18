// Write a function to perform heap sort on an array.

// Approach:
// 1. Build a max-heap from the input array.
// 2. The largest element is at the root of the heap. Swap it with the last element of the heap.
// 3. Reduce the size of the heap by one and heapify the root element.
// 4. Repeat steps 2 and 3 until the heap size is reduced to one.
// 5. The array is now sorted in ascending order.
// 6. Time Complexity: O(N log N) for heap sort.

#include <iostream>
using namespace std;

// Function to heapify a subtree rooted at index i
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

// Function to perform heap sort
void heapSort(int* arr, int n) {
    // Build a max-heap from the input array
    for (int i = n / 2; i > 0; i--) {
        heapify(arr, n, i);
    }

    // One by one extract elements from the heap
    for (int i = n; i > 1; i--) {   // Reduce the heap size, we are taking 1-based indexing. Last element is already sorted.
        swap(arr[1], arr[i]); // Move current root to end
        heapify(arr, i - 1, 1); // Heapify the reduced heap, and pass the size of heap as i - 1 because at each iteration we are reducing the size of heap by 1
    }
}

int main() {
    int arr[] = {-1, 10, 20, 5, 6, 1, 8}; // Example array (1-based indexing)
    int n = 6; // Size of the array

    heapSort(arr, n); // Perform heap sort

    cout << "Sorted array: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " "; // Print the sorted array
    }
    cout << endl;

    return 0;
}

// Output:
// Sorted array: 1 5 6 8 10 20


// We can use Priority Queue to implement heap sort.
// As Priority Queue is implemented using heap.
// How to do that?
// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;

// void heapSortDescending(vector<int>& arr) {
//     priority_queue<int> maxHeap;

//     // Step 1: Push all elements into max heap
//     for (int num : arr) {
//         maxHeap.push(num);
//     }

//     // Step 2: Pop from heap and overwrite array
//     for (int i = 0; i < arr.size(); i++) {
//         arr[i] = maxHeap.top();
//         maxHeap.pop();
//     }
// }

// int main() {
//     vector<int> arr = {20, 10, 30, 5, 7, 25};

//     heapSortDescending(arr);

//     cout << "Sorted (Descending): ";
//     for (int num : arr) {
//         cout << num << " ";
//     }

//     return 0;
// }
