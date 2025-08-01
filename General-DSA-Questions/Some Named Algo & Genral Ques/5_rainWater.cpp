// Write a function which takes an array of integers(height) and returns the maximum stored rainwater in that array.

// Given an array height[], where each element represents the height of a vertical line drawn at that index,
// find two lines that together with the x-axis form a container, such that the container holds the most water.

// Video link : https://www.youtube.com/watch?v=EbkMABpP52U&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=14

// Input: height = [1,8,6,2,5,4,8,3,7]
// Output: 49

// Explanation:
// - Pick height[1] = 8 and height[8] = 7
// - Width = 8 - 1 = 7
// - Height = min(8, 7) = 7
// - Area = 7 * 7 = 49

// Intuition:
// 1. The area is determined by the shorter line and the distance between them.
// 2. To maximize the area, we need to consider all pairs of lines.
// 3. Instead of checking all pairs, we can use a two-pointer approach:
//    a. Start with two pointers at the ends of the array.
//    b. Calculate the area.
//    c. Move the pointer that has the shorter height inward. Why? Because moving the taller one inward can't help (height is limited by the shorter line),
//       but the shorter one might be replaced by a taller one, increasing area.


#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) {
    int maxStoredWater = 0;
    int leftPointer = 0;
    int rightPointer = height.size() - 1;
    while (leftPointer < rightPointer) {
        int widthLen = rightPointer - leftPointer;
        int heightLen = min(height[leftPointer], height[rightPointer]);
        maxStoredWater = max(maxStoredWater, widthLen * heightLen);
        if (height[leftPointer] < height[rightPointer]) {
            leftPointer++;
        } else {
            rightPointer--;
        }
    }
    return maxStoredWater;
}

int main() {
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << maxArea(height) << endl;
    return 0;
}

// How does it work?
// We are using two pointers, leftPointer and rightPointer.
// We have to move the pointer which has the smaller height.