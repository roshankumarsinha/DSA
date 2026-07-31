// Given a binary matrix filled with 0s and 1s, find the area of the largest rectangle containing
// only 1s.

// Example:
// [
//   ['1','0','1','0','0'],
//   ['1','0','1','1','1'],
//   ['1','1','1','1','1'],
//   ['1','0','0','1','0']
// ]  → 6

// Intuition:
// 1. Convert each row into a histogram: the height at each column is the number of consecutive 1s
//    above (including the current row).
// 2. For each histogram row, run "Largest Rectangle in Histogram" and track the maximum area.

// Helper: largest rectangle in a histogram (see 11_maximumAreaOfRectangle.js).
function largestRectangleArea(heights) {
  const n = heights.length;
  const left = new Array(n);
  const right = new Array(n);
  const st = [];

  // Previous Smaller Element
  for (let i = 0; i < n; i++) {
    while (st.length > 0 && heights[st[st.length - 1]] >= heights[i]) st.pop();
    left[i] = st.length === 0 ? -1 : st[st.length - 1];
    st.push(i);
  }

  st.length = 0;

  // Next Smaller Element
  for (let i = n - 1; i >= 0; i--) {
    while (st.length > 0 && heights[st[st.length - 1]] >= heights[i]) st.pop();
    right[i] = st.length === 0 ? n : st[st.length - 1];
    st.push(i);
  }

  let maxArea = 0;
  for (let i = 0; i < n; i++) {
    const width = right[i] - left[i] - 1;
    maxArea = Math.max(maxArea, heights[i] * width);
  }
  return maxArea;
}

// JavaScript note: the matrix cells here are the character strings '1'/'0' (like the C++
// vector<vector<char>>), so we compare against '1'. Array(cols).fill(0) makes the heights row.
function maximalRectangle(matrix) {
  if (matrix.length === 0) return 0;

  let maxArea = 0;
  const rows = matrix.length;
  const cols = matrix[0].length;
  const heights = new Array(cols).fill(0);

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      // Build up the histogram
      if (matrix[i][j] === "1") heights[j] += 1;
      else heights[j] = 0;
    }
    maxArea = Math.max(maxArea, largestRectangleArea(heights));
  }

  return maxArea;
}

const matrix = [
  ["1", "0", "1", "0", "0"],
  ["1", "0", "1", "1", "1"],
  ["1", "1", "1", "1", "1"],
  ["1", "0", "0", "1", "0"],
];
console.log("Maximal Rectangle Area:", maximalRectangle(matrix)); // 6
