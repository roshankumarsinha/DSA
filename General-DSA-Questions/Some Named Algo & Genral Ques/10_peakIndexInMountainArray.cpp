// Write a function to find the peak index in a mountain array. It is guaranteed that the input array is a
// mountain array(mountain array means that there will be at-least 3 elements). In this case ther will be always one peak element.

// You're given a mountain array, i.e. an array where: Elements first strictly increase, then Strictly decrease.
// So, there's a peak element somewhere in the middle. You need to find the index of the peak element.

// Video link : https://www.youtube.com/watch?v=cXxmbemS6XM
// Notes link : https://takeuforward.org/data-structure/peak-element-in-array

// Example :
// Input: num = [1, 2, 3, 4, 5, 4, 3, 2]
// Output: 4


// How this works :
// 1. A mountain array is an array that increases from the first element to some peak element, after which it decreases.
// 2. We can find the peak element by using binary search.
// 3. We start left from 1 and right from num.size() - 2 because:
//      3a. The peak element can't be at the first or last index, as it is guaranteed that the input array is a mountain array.
//      3b. We can't start left from 0 because we need to compare num[mid] with num[mid - 1] and num[mid + 1], which will cause an out of bounds exception.
// 4. We find the mid element and check if it is greater than its previous and next element. If it is, then it is the peak element.
// 5. If num[mid] < num[mid + 1], then the peak element is on the right side of mid, so we move left to mid + 1.
// 6. If num[mid] > num[mid + 1], then the peak element is on the left side of mid, so we move right to mid - 1.
// 7. We keep doing this until we find the peak element.
// 8. The time complexity of this solution is O(log n) because we are using binary search.

#include <iostream>
#include <vector>

using namespace std;

int peakIndexInMountainArray(vector<int> &num) {
    int left = 1;   // Start from index 1, as the peak can't be at index 0
    int right = num.size() - 2; // Start from the second last index, as the peak can't be at the last index
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (num[mid] > num[mid - 1] && num[mid] > num[mid + 1]) {   // If mid is greater than its previous and next element, then it is the peak element
            return mid;
        } else if (num[mid] < num[mid + 1]) {   // If mid is less than its next element, then the peak element is on the right side of mid, you're on the ascending slope
            // Search in the right half
            left = mid + 1;
        } else {    // If mid is greater than its next element, then the peak element is on the left side of mid, you're on the descending slope
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> num = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << peakIndexInMountainArray(num) << endl;
    return 0;
}


// There is one more modified version of this question which is :-
// Given an array of length N, peak element is defined as the element greater than both of its neighbors.
// Formally, if arr[i] is the peak element, arr[i - 1] < arr[i] and arr[i + 1] < arr[i]. Find the index(0-based) of a peak element in the array.
// If there are multiple peak numbers, return the index of any peak number. You may imagine that nums[-1] = nums[n] = -∞.
// In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

// Intiution:
// 1. Almost same as above question.
// 2. First we will check if there is only one element in the array, if yes then return 0 as the index of peak element.
//    As both the neighbours are out of bound and have value as -∞.
// 3. Then we will check if the first element is greater than the second element, if yes then return 0 as the index of peak element.
// 4. Then we will check if the last element is greater than the second last element, if yes then return n-1 as the index of peak element.
// 5. 3rd and 4th step we are doing it becasue, we need to check arr[i-1] and arr[i+1]. So, if we discard 1st and last
//    element from search space then accessing arr[i-1] and arr[i+1] won't give any error.
// 6. Now, the rest of code will remain same, because for multiple peak elements also, we can apply binary search, beacuse the
//    condition will fulfill atleast for 1 of the peak and we need to return any peak index.


int peakElementInArray(vector<int> &arr) {
    int n = arr.size();
    // Edge case: If there is only one element, it is the peak
    if (n == 1) return 0;

    // Check if the first element is a peak
    if (arr[0] > arr[1]) return 0;

    // Check if the last element is a peak
    if (arr[n - 1] > arr[n - 2]) return n - 1;

    int left = 1;   // Start from index 1
    int right = n - 2; // End at index n-2

    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {   // If mid is greater than its previous and next element, then it is the peak element
            return mid;
        } else if (arr[mid] < arr[mid + 1]) {   // If mid is less than its next element, then the peak element is on the right side of mid
            left = mid + 1;
        } else {    // If mid is greater than its next element, then the peak element is on the left side of mid
            right = mid - 1;
        }
    }
    return -1;  // This line will never be reached because there is always a peak in the array
}

