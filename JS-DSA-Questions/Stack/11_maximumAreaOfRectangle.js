// Given an array heights representing a histogram's bar heights (each width 1), return the area of
// the largest rectangle in the histogram.

// Notes : https://takeuforward.org/data-structure/area-of-largest-rectangle-in-histogram/

// Example: [2, 1, 5, 6, 2, 3] → 10 (bars 5 and 6 → height 5, width 2).

// Intuition:
// For each bar, use Previous Smaller Element (PSE) and Next Smaller Element (NSE) to find how far
// the rectangle of that bar's height can extend.
//   PSE[i]: index of nearest smaller bar to the left (-1 if none).
//   NSE[i]: index of nearest smaller bar to the right (n if none).
//   width[i] = NSE[i] - PSE[i] - 1, area[i] = heights[i] * width[i].

function largestRectangleArea(heights) {
  const n = heights.length;
  const pse = new Array(n);
  const nse = new Array(n);
  const s = [];

  // Previous Smaller Element (PSE)
  for (let i = 0; i < n; i++) {
    while (s.length > 0 && heights[s[s.length - 1]] >= heights[i]) {
      s.pop();
    }
    pse[i] = s.length === 0 ? -1 : s[s.length - 1];
    s.push(i);
  }

  // Clear the stack for NSE
  s.length = 0;

  // Next Smaller Element (NSE)
  for (let i = n - 1; i >= 0; i--) {
    while (s.length > 0 && heights[s[s.length - 1]] >= heights[i]) {
      s.pop();
    }
    nse[i] = s.length === 0 ? n : s[s.length - 1];
    s.push(i);
  }

  // Maximum area
  let maxArea = 0;
  for (let i = 0; i < n; i++) {
    const width = nse[i] - pse[i] - 1;
    const area = heights[i] * width;
    maxArea = Math.max(maxArea, area);
  }

  return maxArea;
}

console.log(largestRectangleArea([2, 1, 5, 6, 2, 3])); // 10
