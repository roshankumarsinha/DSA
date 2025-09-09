// The 3 Sum problem asks you to find all unique triplets in an array that sum up to a given target value (usually zero).


// Approach and Intuition:(Fix one element and use two pointer approach for the other two elements)
// 1. Sorting:
//    a.  First, sort the array to help easily skip duplicate elements and apply a two-pointer approach efficiently.
// 2. Iterate with a fixed element:
//    a.  The idea is to fix one element of the triplet (nums[i]), and then find the remaining two numbers that sum up
//        to -nums[i] (because we are aiming for the sum to be zero). We do this using the two-pointer technique.
// 3. Two-pointer technique:
//    a.  After fixing one element, use two pointers (left and right) to find pairs whose sum is equal to -nums[i].
//        The pointers start at the next index (left = i + 1) and the end of the array (right = n - 1).
//        a1. If the sum of nums[i] + nums[left] + nums[right] is less than zero, we need a larger sum,
//            so we move the left pointer to the right (left++).
//        a2. If the sum is greater than zero, we need a smaller sum, so we move the right pointer to the left (right--).
//        a3. If the sum is exactly zero, we record the triplet and move both pointers inward to avoid duplicates.
// 4. Avoid duplicates:
//    a.  After finding a valid triplet, skip over any duplicate values for nums[i], nums[left], and nums[right] to ensure uniqueness.


#include <iostream>
#include <vector>
#include <algorithm>  // For sort method
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    
    // Step 1: Sort the array
    sort(nums.begin(), nums.end());
    
    // Step 2: Iterate through the array
    for (int i = 0; i < n - 2; i++) {   // We need at least 3 elements to form a triplet, so we go up to n-2
        // Skip duplicate elements for the first element of the triplet
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        // Step 3: Use two-pointer technique to find the other two elements
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum < 0) {
                left++;  // We need a larger sum
            } else if (sum > 0) {
                right--; // We need a smaller sum
            } else {
                // Found a triplet
                result.push_back({nums[i], nums[left], nums[right]});
                
                // Skip duplicate elements for the second element of the triplet
                while (left < right && nums[left] == nums[left - 1]) left++;
                // Skip duplicate elements for the third element of the triplet
                while (left < right && nums[right] == nums[right + 1]) right--;
                
                // Move both pointers inward
                left++;
                right--;
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> triplets = threeSum(nums);
    
    cout << "Unique triplets that sum to zero are:\n";
    for (const auto& triplet : triplets) {
        cout << "[";
        for (size_t i = 0; i < triplet.size(); i++) {
            cout << triplet[i];
            if (i < triplet.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    return 0;
}
// Time Complexity: O(n^2) - Sorting the array takes O(n log n)
// and the two-pointer technique takes O(n) for each of the n elements.
// Space Complexity: O(1) - We are using only a constant amount of extra space (not counting the output storage).

// 4 Sum Problem is also similar to this problem but there we fix two elements and then use two pointer approach for the other two elements.