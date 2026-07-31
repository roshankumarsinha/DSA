// Find the sum of the minimum and maximum elements of all subarrays of window size k.

// Example:
// Input: arr = {2, 5, -1, 7, -3, -1, -2}, k = 3 → Output: 14

// Approach (monotonic deques):
// 1. Use two deques of INDICES:
//    a. maxi keeps indices with values in decreasing order — front is the window maximum.
//    b. mini keeps indices with values in increasing order — front is the window minimum.
// 2. For each window: remove indices that fell out of the window, maintain the deque orders by
//    popping from the back, then read the front of each deque.
// 3. Add (max + min) for each window to the running sum.
// Time Complexity: O(n) — each index is pushed/popped at most once. Space: O(k).

// JavaScript note: C++ used std::deque with pop_front/pop_back. Here a plain array is the deque:
// push()/pop() for the back, and shift() for the front. We store indices, not values.
function sumMinMaxInKSizeWindow(arr, k) {
  const n = arr.length;
  if (n < k) return 0;

  const maxi = []; // indices, values decreasing
  const mini = []; // indices, values increasing
  let sum = 0;

  // Process the first k elements
  for (let i = 0; i < k; i++) {
    while (maxi.length > 0 && arr[maxi[maxi.length - 1]] <= arr[i]) maxi.pop();
    maxi.push(i);
    while (mini.length > 0 && arr[mini[mini.length - 1]] >= arr[i]) mini.pop();
    mini.push(i);
  }

  sum += arr[maxi[0]] + arr[mini[0]];

  // Process the rest
  for (let i = k; i < n; i++) {
    // Remove out-of-window indices
    if (maxi.length > 0 && maxi[0] <= i - k) maxi.shift();
    while (maxi.length > 0 && arr[maxi[maxi.length - 1]] <= arr[i]) maxi.pop();
    maxi.push(i);

    if (mini.length > 0 && mini[0] <= i - k) mini.shift();
    while (mini.length > 0 && arr[mini[mini.length - 1]] >= arr[i]) mini.pop();
    mini.push(i);

    sum += arr[maxi[0]] + arr[mini[0]];
  }

  return sum;
}

const arr = [1, 3, -1, -3, 5, 3, 6, 7];
const k = 3;
console.log(`Sum of min and max in all subarrays of size ${k}:`, sumMinMaxInKSizeWindow(arr, k));
