// Write a function for binary search.

// Binary Search is a powerful algorithm used to find an element's position in a sorted array in O(log n) time.

// Video link : https://www.youtube.com/watch?v=TbbSJrY5GqQ&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=17

// How this works :
// 1. Binary search main logics behind it is to divide the array into two halves and check if the target is in the left half or right half and then discard the other half.
// 2. At each iteration, we are discarding half of the array. That's why the time complexity of binary search is O(log n).

#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int> &num, int target) {
    int left = 0;
    int right = num.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) / 2);  // To avoid overflow, we can also write it as (left + right) / 2 but it is not recommended because it can cause overflow if left and right are very large numbers(INT_MAX).
        if (num[mid] == target) {
            return mid;
        } else if (num[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    vector<int> num = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 5;
    cout << binarySearch(num, target) << endl;
    return 0;
}
