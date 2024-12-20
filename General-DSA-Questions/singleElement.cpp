// Write a function to find single element in a sorted array where every element appears twice except for one element which appears only once.

#include <iostream>
#include <vector>

using namespace std;

int singleElement(vector<int> &nums) {
    int length = nums.size();

    // If there’s a single element in array
    if (length == 1) 
        return nums[0];
    int start = 0;
    int end = length - 1;
    while (start <= end) {
        int mid = start + ((end - start) / 2);

        // If single element is first element, We are doing this because we have to use (mid - 1) index
        if (mid == 0 && nums[mid] != nums[1])
            return nums[mid];

        // If single element is last element, We are doing this because we have to use (mid + 1) index
        else if (mid == length - 1 && nums[mid] != nums[length - 2])
            return nums[mid];

        // If Single elememt is found
        else if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
            return nums[mid];

        // There can be 2 case :
        // 1st : When mid is even, and there are even no. of elements on both sides of mid.
        else if (mid % 2 == 0) {
        // If mid && mid - 1 are equal, then single element will definitely be on left side
            if (nums[mid] == nums[mid - 1]) {
                end = mid - 1;
                // Else on right side
            } else {
                start = mid + 1;
            }
        // 2nd : When mid is odd, and there are odd no. of elements on both sides of mid.
        } else {
            // If mid && mid - 1 are equal, then single element will definitely be on right side
            if (nums[mid] == nums[mid - 1]) {
                start = mid + 1;
                // Else on left side
            } else {
                end = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << singleElement(nums) << endl;
    return 0;
}

// How this works :
// 1. We are using binary search to find the single element.
// 2. We are checking if the single element is at the first or last index.
// 3. We are checking if the single element is at the mid index.