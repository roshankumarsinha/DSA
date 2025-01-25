// Write a function that takes an array and a number k as input and returns the first negative number in every window of size k. If there is no negative number in a window, return 0. The function should have the following signature:-
// vector<int> firstNegativeInWindowK(vector<int> arr, int K);

// Approach to solve the problem
// 1. Use a queue to store the indices of negative integers in the current window of size k.
// 2. Slide the window one element at a time, and:
//    a. Add the current index to the queue if the element is negative.
//    b. Remove indices from the queue that are out of the current window.
// 3. For each window, the first index in the queue corresponds to the first negative integer. If the queue is empty, there is no negative integer in the window.

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void firstNegativeInteger(vector<int>& arr, int k) {
    int n = arr.size();
    deque<int> negatives; // Queue to store indices of negative numbers
    vector<int> result;   // Result to store the first negative numbers for each window

    // Process the first window, and add the indices of negative numbers to the queue
    for (int i = 0; i < k; i++) {
        if (arr[i] < 0) {
          negatives.push_back(i);
        }
    }

    // Push the first negative number in the first window to the result
    if (negatives.empty()) {
        result.push_back(0);
    } else {
        result.push_back(arr[negatives.front()]);
    }

    // Process the remaining windows
    for (int i = k; i < n; i++) {
        // First pop out the index of the element which is out of the current window
        if (!negatives.empty() && (i - negatives.front() >= k)) {
            negatives.pop_front();
        }

        // Add the index of the current element if it is negative
        if (arr[i] < 0) {
            negatives.push_back(i);
        }

        // If there is no negative number in the window, add 0 to the result
        if (negatives.empty()) {
            result.push_back(0);
        } else {
            result.push_back(arr[negatives.front()]);
        }
    }

    // Print the first negative numbers in each window
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

}

int main() {
    vector<int> arr = {12, -1, -7, 8, -15, 30, 16, 28};
    int k = 3;

    cout << "First negative integers in every window of size " << k << ":" << endl;
    firstNegativeInteger(arr, k);

    return 0;
}

// The above approach has a time complexity of O(n) and a space complexity of O(k), where n is the number of elements in the array and k is the window size. The algorithm uses a deque to store the indices of negative numbers in the current window.

// We can solve this problem with space complexity of O(1) using a two-pointer approach. The idea is to maintain two pointers, start and end, to represent the current window. We will iterate over the array and slide the window one element at a time. At each step, we will check if the current element is negative and update the result accordingly.

// void firstNegativeInteger(vector<int>& arr, int k) {
//     int n = arr.size();
//     int firstNegativeIndex = -1; // To track the index of the first negative integer in the current window

//     for (int i = 0; i <= n - k; i++) {
//         // Move the firstNegativeIndex to ensure it's within the current window
//         if (firstNegativeIndex < i) {
//             firstNegativeIndex = -1; // Reset the index if it's out of the window
//             // Find the next negative integer in the current window
//             for (int j = i; j < i + k; j++) {
//                 if (arr[j] < 0) {
//                     firstNegativeIndex = j;
//                     break;
//                 }
//             }
//         }

//         // Output the first negative integer in the current window
//         if (firstNegativeIndex != -1 && firstNegativeIndex < i + k) {
//             cout << arr[firstNegativeIndex] << " ";
//         } else {
//             cout << 0 << " "; // No negative integer in the window
//         }
//     }
//     cout << endl;
// }
