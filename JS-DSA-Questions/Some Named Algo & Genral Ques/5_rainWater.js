// Given an array height[] where each element is the height of a vertical line at that index,
// find two lines that together with the x-axis form a container holding the most water.
// (This is the "Container With Most Water" problem.)

// Video link : https://www.youtube.com/watch?v=EbkMABpP52U&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=14

// Input: height = [1,8,6,2,5,4,8,3,7] → Output: 49
// Explanation: pick index 1 (8) and index 8 (7): width = 7, height = min(8,7) = 7, area = 49.

// Intuition:
// 1. The area is limited by the SHORTER line and the distance between the two lines.
// 2. Use two pointers at the ends of the array.
// 3. Compute the area, then move the pointer at the SHORTER line inward — moving the taller line
//    can't increase the area (still limited by the shorter one), but the shorter line might be
//    replaced by a taller one.

function maxArea(height) {
  let maxStoredWater = 0;
  let leftPointer = 0;
  let rightPointer = height.length - 1;
  while (leftPointer < rightPointer) {
    const widthLen = rightPointer - leftPointer;
    const heightLen = Math.min(height[leftPointer], height[rightPointer]);
    maxStoredWater = Math.max(maxStoredWater, widthLen * heightLen);
    if (height[leftPointer] < height[rightPointer]) {
      leftPointer++;
    } else {
      rightPointer--;
    }
  }
  return maxStoredWater;
}

console.log(maxArea([1, 8, 6, 2, 5, 4, 8, 3, 7])); // 49
