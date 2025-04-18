// Write a function to find the minimum cost to connect N ropes.

// You're given n ropes with different lengths.
// To connect two ropes, it costs sum of their lengths.
// Your task is to connect all ropes into one with minimum total cost.

// Intitution:
// Always combine the two smallest ropes first.
// This is because combining the two smallest ropes will minimize the cost of connecting them.
// We can use a min-heap to efficiently find the two smallest ropes.

// Approach:
// 1. Create a min-heap to store the lengths of the ropes.
// 2. While there is more than one rope in the heap:
//    a. Extract the two smallest ropes from the heap.
//    b. Calculate the cost of connecting them (sum of their lengths).
//    c. Add the cost to the total cost.
//    d. Insert the combined rope back into the heap.
// 3. Return the total cost.
// 4. Time Complexity: O(N log N) for inserting and extracting elements from the heap.
// 5. Space Complexity: O(N) for storing the ropes in the heap.

#include <iostream>
#include <queue>
using namespace std;

// Function to find the minimum cost to connect N ropes
int minCostToConnectRopes(int arr[], int n) {
    // Create a min-heap using priority queue
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Insert all rope lengths into the min-heap
    for (int i = 0; i < n; i++) {
        minHeap.push(arr[i]);
    }

    int totalCost = 0;

    // While there is more than one rope in the heap
    while (minHeap.size() > 1) {
        // Extract the two smallest ropes from the heap
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        // Calculate the cost of connecting them
        int cost = first + second;
        totalCost += cost;

        // Insert the combined rope back into the heap
        minHeap.push(cost);
    }

    return totalCost; // Return the total cost
}

int main() {
    int arr[] = {4, 3, 2, 6}; // Example rope lengths
    int n = sizeof(arr) / sizeof(arr[0]);

    int minCost = minCostToConnectRopes(arr, n);
    cout << "Minimum cost to connect ropes: " << minCost << endl;

    return 0;
}
// Output: Minimum cost to connect ropes: 29