// Write a function to merge k sorted arrays into a single sorted array.

// Approach (Brute Force):
// 1. Create a single array to store all elements from the k sorted arrays.
// 2. Sort the combined array.
// 3. Return the sorted array.
// 4. Time Complexity: O(N * k Log(N * k)) for sorting.
// 5. Space Complexity: O(N * k) for storing the combined array.

// Another Approach (Using Min-Heap):
// 1. Create a min-heap.
// 2. Push the first element of each array into the heap along with:
//    a.  The array index (i)
//    b.  The element index (j)
// 3. Pop the smallest element from the heap and add it to the result.
// 4. If the popped element has a next element in its array, push that next element into the heap.
// 5. Repeat until the heap is empty.
// 6. Time Complexity: O(N * k Log k) for merging k sorted arrays.
//    a.  Total elements: N * K
//    b.  Heap operations: log K
// 7. Space Complexity: O(N * k) for storing the N * k elements in the heap.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, pair<int, int>> Node; // To store the value and its array and index, here first int is the array value, second pair is the row and column index

// Function to merge k sorted arrays into a single sorted array
vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
    priority_queue<Node, vector<Node>, greater<Node>> minHeap; // Min-heap to store the elements
    vector<int> result; // Resultant merged array

    // Push the first element of each array into the min-heap
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], {i, 0}}); // Push the element along with its array and row and 1st column index
        }
    }

    // While the min-heap is not empty
    while (!minHeap.empty()) {
        Node current = minHeap.top(); // Get the smallest element
        minHeap.pop(); // Remove it from the heap

        int value = current.first; // The value of the smallest element
        int rowIndex = current.second.first; // The index of the array
        int columnIndex = current.second.second; // The index of the element in that array

        result.push_back(value); // Add the smallest element to the result

        // If there is a next element in the same array, push it into the min-heap
        if (columnIndex + 1 < arrays[rowIndex].size()) {
            minHeap.push({arrays[rowIndex][columnIndex + 1], {rowIndex, columnIndex + 1}});
        }
    }

    return result; // Return the merged sorted array
}

int main() {
    vector<vector<int>> arrays = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };

    vector<int> mergedArray = mergeKSortedArrays(arrays);

    cout << "Merged sorted array: ";
    for (int num : mergedArray) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

// Output:
// Merged sorted array: 1 2 3 4 5 6 7 8 9