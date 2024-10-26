// Write a function for Kadan's algorithm that finds the maximum sum of a subarray in an array of integers.

// Basically, the algorithm is to keep track of the current sum of the subarray and the maximum sum of the subarray.
// If the current sum is less than 0, then we reset the current sum to 0.
// If the current sum is greater than the maximum sum, then we update the maximum sum.

// +ve + +ve = +ve
// Big(+ve) + Small(-ve) = +ve
// Big(-ve) + Small(+ve) = -ve.  So, we reset the current sum to 0.

#include <iostream>
#include <vector>

using namespace std;

int kadane(vector<int>& nums) {
    int currentSum = 0;
    int maxSum = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        currentSum = currentSum + nums[i];
        maxSum = max(maxSum, currentSum);
        if (currentSum < 0) {
            currentSum = 0;
        }
    }
    return maxSum;
}

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << kadane(nums) << endl;
    return 0;
}