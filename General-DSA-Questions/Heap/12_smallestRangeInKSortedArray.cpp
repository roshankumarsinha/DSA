// Write a function to find the smallest range that includes at least one element from each of the k sorted arrays.

// Given K sorted arrays, each with N integers, you need to find the smallest range that includes at least one element from each of the K arrays.

// Approach 1: (using multiple pointers)
// 1. Initialize K pointers, one for each array (all at index 0).
// 2. Loop until one of the pointers reaches the end of its respective array.
// 3. In each loop:
//    a.  Get current elements at all pointers.
//    b. Find the min and max among these.
//    c. Update the smallest range.
//    d. Move the pointer of the array which has the minimum element.
// 4. Return the smallest range.
// 5. Time Complexity: O(K * N) for iterating through all elements and O(K) for finding min and max. so, Total: O(K * N * K) = O(K^2 * N)
// 6. Space Complexity: O(K) for storing the pointers.

// pair<int, int> smallestRange(vector<vector<int>>& nums) {
//     int k = nums.size();
//     vector<int> ptr(k, 0);  // Pointers for each array

//     int rangeStart = 0, rangeEnd = INT_MAX;
//     bool done = false;

//     while (!done) {
//         int currentMin = INT_MAX, currentMax = INT_MIN;
//         int minIndex = -1;

//         // Find min and max among current elements
//         for (int i = 0; i < k; ++i) {
//             if (ptr[i] == nums[i].size()) {
//                 done = true; // One array is exhausted
//                 break;
//             }

//             int val = nums[i][ptr[i]];
//             if (val < currentMin) {
//                 currentMin = val;
//                 minIndex = i;
//             }
//             currentMax = max(currentMax, val);
//         }

//         // Update the result range if better
//         if (!done && (currentMax - currentMin < rangeEnd - rangeStart)) {
//             rangeStart = currentMin;
//             rangeEnd = currentMax;
//         }

//         // Move pointer for the array with the minimum element
//         if (!done) {
//             ptr[minIndex]++;
//         }
//     }

//     return {rangeStart, rangeEnd};
// }


// We can optimize this using a min-heap.
// Approach 2: (using min-heap)
// 1. Insert the first element of each array into a min-heap
// 2. Keep track of the current maximum of these inserted elements
// 3. Calculate range = [minHeap.top().val, currentMax]
// 4. Try to improve the range by replacing the min element with the next element from the same array
// 5. Stop when any one of the arrays is exhausted
// 6. Return the smallest range
// 7. Time Complexity: O(N log K) for inserting N elements into the min-heap, where K is the number of arrays. Each insertion takes O(log K) time.
// 8. Space Complexity: O(K) for storing the k elements in the min-heap.

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Node {
    int value; // Value of the element
    int rowIndex; // Index of the array
    int columnIndex; // Index of the element in that array

    // Constructor to initialize the node
    Node(int val, int row, int col) : value(val), rowIndex(row), columnIndex(col) {}
};

// Custom comparator for the min-heap
struct Compare {
    bool operator()(Node a, Node b) {
        return a.value > b.value; // Min-heap based on value
    }
};

// Function to find the smallest range that includes at least one element from each of the k sorted arrays
pair<int, int> smallestRange(vector<vector<int>>& nums) {
    // Calculate the number of arrays
    int k = nums.size();  // k is the number of arrays
    priority_queue<Node, vector<Node>, Compare> minHeap; // Min-heap to store the elements
    int currentMax = INT_MIN; // Initialize current maximum

    // Insert the first element of each array into the min-heap
    for (int i = 0; i < k; ++i) {
        minHeap.push(Node(nums[i][0], i, 0)); // Push the first element along with its array and index
        currentMax = max(currentMax, nums[i][0]); // Update current maximum
    }

    int rangeStart = 0, rangeEnd = INT_MAX; // Initialize range

    // While the min-heap is not empty
    while (!minHeap.empty()) {
        Node currentNode = minHeap.top(); // Get the smallest element
        minHeap.pop(); // Remove it from the heap

        int currentMin = currentNode.value; // The minimum value in the current range

        // Update the result range if better
        if (currentMax - currentMin < rangeEnd - rangeStart) {
            rangeStart = currentMin;
            rangeEnd = currentMax;
        }

        // If we can move to the next element in the same array
        if (currentNode.columnIndex + 1 < nums[currentNode.rowIndex].size()) {
            int nextValue = nums[currentNode.rowIndex][currentNode.columnIndex + 1];
            minHeap.push(Node(nextValue, currentNode.rowIndex, currentNode.columnIndex + 1)); // Push the next element into the heap
            currentMax = max(currentMax, nextValue); // Update current maximum
        } else {
            break; // One of the arrays is exhausted, break out of the loop
        }
    }

    return {rangeStart, rangeEnd}; // Return the smallest range
}

int main() {
    vector<vector<int>> nums = {
      {4, 10, 15, 24, 26},
      {0, 9, 12, 20},
      {5, 18, 22, 30}
    };

    pair<int, int> result = smallestRange(nums);
    cout << "Smallest range: [" << result.first << ", " << result.second << "]" << endl;

    return 0;
}

// Output:
// Smallest range: [20, 24] because (24 - 20) = 4 is the smallest range that includes at least one element from each of the k sorted arrays.