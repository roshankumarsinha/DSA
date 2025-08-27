// Write a function to find the peak index in a mountain array. It is guaranteed that the input array is a mountain array.

// You're given a mountain array, i.e. an array where: Elements first strictly increase, then Strictly decrease.
// So, there's a peak element somewhere in the middle. You need to find the index of the peak element.

// Video link : https://www.youtube.com/watch?v=RjxD6UXGlhc&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=19

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
