// Given a binary matrix matrix[][] filled with 0s and 1s, find the area of the largest rectangle containing only 1s.

// Example:
// Input:
// [
//   ['1','0','1','0','0'],
//   ['1','0','1','1','1'],
//   ['1','1','1','1','1'],
//   ['1','0','0','1','0']
// ]

// Output: 6, The maximal rectangle is formed by the 2×3 block of 1s in the third row and second to fourth columns.

// Intuition:
// 1. Convert each row into a "histogram" where the height at each column is the number of consecutive 1s above (including the current row).
// 2. For each histogram row, use the Largest Rectangle in Histogram technique (with PSE and NSE or monotonic stack) to compute the largest area.
// 3. Keep track of the maximum area found.


// 1. Initialize a heights[] array of size equal to number of columns, initialized to 0.
// 2. For every row:
//    a.  For every column:
//      a1. If matrix[row][col] is '1', increment heights[col] by 1.
//      a2. Else, reset heights[col] to 0.
//    b.  Use the Largest Rectangle in Histogram on heights[] to get area for that row.
//    c.  Update maxArea.

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// Helper function to find largest rectangle in histogram
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);
    stack<int> st;

    // Previous Smaller Element (PSE)
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && heights[st.top()] >= heights[i])
            st.pop();
        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Next Smaller Element (NSE)
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && heights[st.top()] >= heights[i])
            st.pop();
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        int width = right[i] - left[i] - 1;
        int area = heights[i] * width;
        maxArea = max(maxArea, area);
    }

    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;

    int maxArea = 0;
    int rows = matrix.size(), cols = matrix[0].size();
    vector<int> heights(cols, 0); // Initialize height array with 0s

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Build up the histogram
            if (matrix[i][j] == '1')
                heights[j] += 1;
            else
                heights[j] = 0;
        }
        // Apply largest rectangle in histogram
        maxArea = max(maxArea, largestRectangleArea(heights));
    }

    return maxArea;
}

int main() {
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };

    cout << "Maximal Rectangle Area: " << maximalRectangle(matrix) << "\n";
    return 0;
}
