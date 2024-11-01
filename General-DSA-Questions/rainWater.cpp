// Write a function which takes an array of integers(height) and returns the maximum stored rainwater in that array.

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