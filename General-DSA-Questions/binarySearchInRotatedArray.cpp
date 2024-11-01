// Write a function for binary search in a rotated array.

#include <iostream>
#include <vector>

using namespace std;

int binarySearchInRotatedArray(vector<int> &num, int target) {
    int left = 0;
    int right = num.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) / 2);
        if (num[mid] == target) {
            return mid;
        } else if (num[left] <= num[mid]) {
            if (num[left] <= target && target <= num[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (num[mid] <+target && target <= num[right]) {
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

// How this works :
// 1. If it is a rotated array, then one half of the array must be sorted.
// 2. If the left half is sorted, then check if the target lies in the left half. If it does, then search in the left half, else search in the right half.
// 2a. Assuming target lies in left half : Searching in left half is just like normal binary search.
// 3. If the right half is sorted, then check if the target lies in the right half. If it does, then search in the right half, else search in the left half.
// 3a. Assuming target lies in right half : Searching in right half is just like normal binary search.