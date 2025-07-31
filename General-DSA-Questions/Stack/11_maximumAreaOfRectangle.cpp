// Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in histogram.

// Notes : https://takeuforward.org/data-structure/area-of-largest-rectangle-in-histogram/

// Example :
// Input:  [2, 1, 5, 6, 2, 3]
// Output: 10

// Explanation:
// The largest rectangle is formed using heights[2] and heights[3] → bars of height 5 and 6:
// - Height = 5
// - Width = 2 (index 2 to 3)
// - Area = 5 * 2 = 10


// Intuition:
// 1. We will use Next Smaller Element (NSE) and Previous Smaller Element (PSE) to find the width of the rectangle for each bar.
// 2. For each bar, the width of the rectangle is determined by the distance to the next smaller bar on the right and the previous smaller bar on the left.
// 3. The area of the rectangle is then calculated as height * width for each bar, and we keep track of the maximum area found.

// For each bar at index i with height h[i]:
// PSE[i]: index of the closest bar to the left of i that is smaller than h[i].
// If none exists, we set it to -1.

// NSE[i]: index of the closest bar to the right of i that is smaller than h[i].
// If none exists, we set it to n (where n is the number of bars).

// After that width for each bar can be calculated as:
// width[i] = NSE[i] - PSE[i] - 1

// Area for each bar can be calculated as:
// area[i] = height[i] * width[i]



#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> pse(n), nse(n); // Previous Smaller Element and Next Smaller Element
    stack<int> s;

    // Fill Previous Smaller Element (PSE)
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        pse[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    // Clear the stack for Next Smaller Element (NSE)
    while (!s.empty()) {
        s.pop();
    }

    // Fill Next Smaller Element (NSE)
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
        }
        nse[i] = s.empty() ? n : s.top();
        s.push(i);
    }

    // Calculate maximum area
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        int width = nse[i] - pse[i] - 1;
        int area = heights[i] * width;
        maxArea = max(maxArea, area);
    }

    return maxArea;
}
