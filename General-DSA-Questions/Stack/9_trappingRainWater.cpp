// Given n non-negative integers representing the elevation map (heights of bars), compute how much water can be trapped after raining.

// Notes : https://takeuforward.org/data-structure/trapping-rainwater/
// Video link : https://www.youtube.com/watch?v=ZI2z5pq0TqA

// Example:
// Input: heightInput = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6. Water is trapped between the bars. Total = 6 units

// Water can be trapped at index i only if:
//    There is a taller bar on the left
//    And a taller bar on the right

// The amount of water that can be trapped at index i is:
//    min(maxLeft[i], maxRight[i]) - heightInput[i]

// Approach 1 : (Using Two Arrays for Left and Right Max Heights)
// 1. Create two arrays, maxLeft and maxRight, to store the maximum heights to the left and right of each index.
//    a. maxLeft[i] contains height of tallest bar to the left of index i (including i).
//    b. maxRight[i] contains height of tallest bar to the right of index i (including i).
// 2. Traverse the heightInput array from left to right to fill maxLeft.
// 3. Traverse the heightInput array from right to left to fill maxRight.
// 4. For each index i, calculate the water trapped as min(maxLeft[i], maxRight[i]) - heightInput[i].
// 5. Sum up the water trapped at each index to get the total water trapped.

// int trapRainWater(vector<int>& height) {
//   int n = height.size();
//   if (n == 0) return 0;

//   vector<int> leftMax(n), rightMax(n);
//   leftMax[0] = height[0];
//   rightMax[n - 1] = height[n - 1];

//   // Fill leftMax
//   for (int i = 1; i < n; ++i) {
//       leftMax[i] = max(leftMax[i - 1], height[i]);
//   }

//   // Fill rightMax
//   for (int i = n - 2; i >= 0; --i) {
//       rightMax[i] = max(rightMax[i + 1], height[i]);
//   }

//   int water = 0;
//   for (int i = 0; i < n; ++i) {
//       water += min(leftMax[i], rightMax[i]) - height[i];
//   }

//   return water;
// }


// Approach 2 : (Using Two Pointers), here space complexity is O(1)
// Intiuition:
// 1. We only need minimum of maxLeft and maxRight at each index because we are calculating water trapped at that index.
// 2. We need a minimum of leftMax and rightMax.So if we take the case when height[l]<=height[r] we increase l++, so we can surely say that there is a block with a height more than height[l] to the right of l.
//    And for the same reason when height[r]<=height[l] we can surely say that there is a block to the left of r which is at least of height[r]. So by traversing these cases and using two pointers approach the time complexity can be decreased without using extra space.
// 3. Move the pointer with the smaller height, because only then can you guarantee how much water can be trapped.

#include <iostream>
#include <vector>
using namespace std;

int trapRainWater(vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;

    int left = 0, right = n - 1;  // These pointers will traverse the height array. One from the left and one from the right.
    int leftMax = 0, rightMax = 0, water = 0; // Initialize leftMax and rightMax to 0, and water to 0.

    while (left < right) {  // Continue until the two pointers meet
        // If the height at left pointer is less than the height at right pointer,
        // it means we can only trap water based on the left side.
        if (height[left] < height[right]) {
            if (height[left] >= leftMax)  // If the current height is greater than or equal to leftMax, update leftMax.
                leftMax = height[left];
            else
                water += leftMax - height[left];  // Otherwise, we can trap water based on the leftMax.
            ++left; // Move the left pointer to the right
        } else {  // Otherwise, we can only trap water based on the right side.
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                water += rightMax - height[right];
            --right;  // Move the right pointer to the left
        }
    }

    return water;
}

int main() {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "Trapped Water: " << trapRainWater(height) << " units\n";
    return 0;
}


// Time Complexity: O(n) - We traverse the height array once.
// Space Complexity: O(1) - We use only a constant amount of extra space for variables.