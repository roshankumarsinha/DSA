// Write a function for binary search in a rotated array.

// You are given a sorted array that has been rotated at an unknown pivot.
// Given a target value, return its index if found; otherwise return -1.

// Input: nums = [4,5,6,7,0,1,2], target = 0  
// Output: 4  

// Video link : https://www.youtube.com/watch?v=6WNZQBHWQJs&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=18

// 🧠 Intuition:
// Even though the array is rotated, at least one half (left or right) of the array is always sorted.
// We can use that fact to decide where to search.

// How this works :
// 1. If it is a rotated array, then one half of the array must be sorted.
// 2. If the left half is sorted, then check if the target lies in the left half. If it does, then search in the left half, else search in the right half.
//    a. Assuming target lies in left half : Searching in left half is just like normal binary search.
// 3. If the right half is sorted, then check if the target lies in the right half. If it does, then search in the right half, else search in the left half.
//    a. Assuming target lies in right half : Searching in right half is just like normal binary search.

#include <iostream>
#include <vector>

using namespace std;

int binarySearchInRotatedArray(vector<int> &num, int target) {
    int left = 0;   // Left pointer
    int right = num.size() - 1; // Right pointer
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (num[mid] == target) {   // If the middle element is the target, return its index
            return mid;
        } else if (num[left] <= num[mid]) { // If the left half is sorted
            if (num[left] <= target && target <= num[mid]) {    // If target is in the left half
                // Search in the left half
                right = mid - 1;
            } else {    // If target is not in the left half, search in the right half
                // Search in the right half
                left = mid + 1;
            }
        } else {    // If the right half is sorted
            if (num[mid] < target && target <= num[right]) {    // If target is in the right half
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    vector<int> num = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    cout << binarySearchInRotatedArray(num, target) << endl;
    return 0;
}


// There is one more question that is similar to this one, which is to search in a rotated sorted array with duplicates.
// The logic is the same, but you have to handle one edge case where there are duplicates in the array and left, mid, and right elements are equal.
// We cannot determine which side is sorted. In that case, you can just increment the left pointer and decrement the right pointer to avoid infinite loop.
// Example:
// Input: nums = [2, 2, 2, 3, 4, 2], target = 3
// Output: 3

// Notes : https://takeuforward.org/arrays/search-element-in-rotated-sorted-array-ii/

// How to handle duplicates in rotated sorted array:
// 1. If left, mid, and right elements are equal, increment left and decrement right.
// 2. If the left half is sorted, check if the target lies in the left half. If it does, search in the left half; otherwise, search in the right half.
// 3. If the right half is sorted, check if the target lies in the right half. If it does, search in the right half; otherwise, search in the left half.

// //Edge case: Add this condition after checking if target == num[mid] and before checking if left half is sorted.
// if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
//     low = low + 1;   // Increment low to avoid infinite loop
//     high = high - 1; // Decrement high to avoid infinite loop
//     continue;
// }