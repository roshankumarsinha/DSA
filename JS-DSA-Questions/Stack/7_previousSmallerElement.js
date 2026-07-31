// Given an array arr[], for each element find the closest smaller element to its left.
// If none exists, use -1.

// Approach:
// 1. Similar to the next-greater-element problem, but we look left for a smaller element.
// 2. Process left to right (we want previous elements).
// 3. Use a monotonic increasing stack (values increase from bottom to top).

function previousSmallerElements(arr) {
  const n = arr.length;
  const result = new Array(n).fill(-1);
  const s = [];

  for (let i = 0; i < n; i++) {
    // Remove elements >= current
    while (s.length > 0 && s[s.length - 1] >= arr[i]) {
      s.pop();
    }

    if (s.length > 0) {
      result[i] = s[s.length - 1];
    }

    s.push(arr[i]);
  }

  return result;
}

console.log("Previous Smaller Elements:", previousSmallerElements([4, 5, 2, 10, 8]).join(" ")); // -1 4 -1 2 2
