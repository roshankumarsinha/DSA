// Given n non-negative integers representing an elevation map (bar heights), compute how much
// water can be trapped after raining.

// Notes : https://takeuforward.org/data-structure/trapping-rainwater/
// Video link : https://www.youtube.com/watch?v=ZI2z5pq0TqA

// Example: height = [0,1,0,2,1,0,1,3,2,1,2,1] → 6

// Water at index i = min(maxLeft[i], maxRight[i]) - height[i], and only if both sides are taller.

// Approach 1 (two arrays, O(n) space):
// function trapRainWater(height) {
//   const n = height.length;
//   if (n === 0) return 0;
//   const leftMax = new Array(n), rightMax = new Array(n);
//   leftMax[0] = height[0];
//   for (let i = 1; i < n; i++) leftMax[i] = Math.max(leftMax[i - 1], height[i]);
//   rightMax[n - 1] = height[n - 1];
//   for (let i = n - 2; i >= 0; i--) rightMax[i] = Math.max(rightMax[i + 1], height[i]);
//   let water = 0;
//   for (let i = 0; i < n; i++) water += Math.min(leftMax[i], rightMax[i]) - height[i];
//   return water;
// }

// Approach 2 (two pointers, O(1) space):
// Move the pointer at the smaller height. Because the other side is taller, the smaller side's
// running max determines how much water sits above the current bar.
function trapRainWater(height) {
  const n = height.length;
  if (n === 0) return 0;

  let left = 0;
  let right = n - 1;
  let leftMax = 0;
  let rightMax = 0;
  let water = 0;

  while (left < right) {
    if (height[left] < height[right]) {
      if (height[left] >= leftMax) leftMax = height[left];
      else water += leftMax - height[left];
      left++;
    } else {
      if (height[right] >= rightMax) rightMax = height[right];
      else water += rightMax - height[right];
      right--;
    }
  }

  return water;
}

console.log("Trapped Water:", trapRainWater([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]), "units"); // 6

// Time Complexity: O(n). Space Complexity: O(1).
