// Given an integer array arr of size N, sorted in ascending order (with distinct values), the array is rotated at any index which is unknown.
// Find the minimum element in the array.

// Generally pivot element is the minimum element in the rotated sorted array.

// Intiution:
// 1. In a rotated sorted array, one half is always sorted.
// 2. First, we will find out which half is sorted by comparing left and mid element.
// 3. In the sorted part the first element is the smallest one, so we will be store the first element of the sorted part as a potential answer.
// 4. Then we can discard that half and continue searching in the other half.
// 5. We will repeat this until left pointer is less than or equal to right pointer.


#include <iostream>
#include <vector>
using namespace std;

int findMinInRotatedArray(vector<int> &arr) {
    int left = 0; // Left pointer
    int right = arr.size() - 1; // Right pointer
    int ans = INT_MAX; // Initialize answer to maximum integer value

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate mid index

        // Check if the left half is sorted
        if (arr[left] <= arr[mid]) {
            ans = min(ans, arr[left]); // Update answer with the first element of the sorted left half
            left = mid + 1; // Discard the left half and search in the right half
        } else { // Right half is sorted
            ans = min(ans, arr[mid]); // Update answer with the first element of the sorted right half
            right = mid - 1; // Discard the right half and search in the left half
        }
    }

    return ans; // Return the minimum element found
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2}; // Example rotated sorted array
    cout << "The minimum element in the rotated sorted array is: " << findMinInRotatedArray(arr) << endl;
    return 0;
}

// Time Complexity: O(log N), where N is the number of elements in the array.
// Space Complexity: O(1), as we are using only constant extra space.