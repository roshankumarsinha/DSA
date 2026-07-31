// Given an array arr[] of size n, for each element arr[i], find the next greater element to its
// right. If none exists, use -1.

// Notes : https://takeuforward.org/data-structure/next-greater-element-using-stack/

// Intuition: Use a monotonic decreasing stack (top holds the smallest of the larger elements seen).
// 1. Process from right to left so future values are already seen.
// 2. The stack holds candidates for the next greater element.
// 3. Pop elements <= current, since they can never be the NGE for anything to the left.
// 4. The stack top (if any) is the next greater element for the current element.

// JavaScript note: a plain array is the stack (push()/pop(), arr[arr.length-1] as top).
// Array(n).fill(-1) is the result initialized to -1.
function nextGreaterElements(arr) {
  const n = arr.length;
  const result = new Array(n).fill(-1);
  const s = [];

  for (let i = n - 1; i >= 0; i--) {
    // Pop all elements smaller than or equal to the current
    while (s.length > 0 && s[s.length - 1] <= arr[i]) {
      s.pop();
    }

    if (s.length > 0) {
      result[i] = s[s.length - 1];
    }

    s.push(arr[i]);
  }

  return result;
}

console.log("Next Greater Elements:", nextGreaterElements([4, 5, 2, 10, 8]).join(" ")); // 5 10 -1 -1 -1

// Time Complexity: O(n). Space Complexity: O(n).
