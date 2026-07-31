// Given a CIRCULAR array arr[], for each element find the next greater element, wrapping around
// to the beginning if needed. If none exists, use -1.

// Approach:
// 1. Same monotonic-stack logic as the linear next-greater-element problem.
// 2. Simulate the circular array by iterating twice (indices 2n-1 down to 0).
// 3. Use i % n to map back to the original index.

// JavaScript note: the stack stores indices; a plain array serves as the stack.
function nextGreaterElementsCircular(nums) {
  const n = nums.length;
  const result = new Array(n).fill(-1);
  const s = []; // stores indices

  for (let i = 2 * n - 1; i >= 0; i--) {
    const idx = i % n;

    // Pop elements <= current
    while (s.length > 0 && nums[s[s.length - 1]] <= nums[idx]) {
      s.pop();
    }

    if (i < n) {
      // Only fill result on the first (real) pass
      if (s.length > 0) {
        result[idx] = nums[s[s.length - 1]];
      }
    }

    s.push(idx);
  }

  return result;
}

console.log("Next Greater in Circular Array:", nextGreaterElementsCircular([1, 2, 1]).join(" ")); // 2 -1 2
