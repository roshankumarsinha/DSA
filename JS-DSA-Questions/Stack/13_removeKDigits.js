// Given a string num representing a non-negative integer and an integer k, find the smallest
// possible integer after removing k digits from num.

// Notes link : https://takeuforward.org/data-structure/remove-k-digits

// Example:
// num = "541892", k = 2 → "1892"
// num = "1002991", k = 3 → "21"

// Intuition:
// Use a stack to build the smallest number. For each digit, while we can still remove digits
// (k > 0) and the stack top is greater than the current digit, pop the top (removing a larger
// leading digit yields a smaller number). Push the current digit. If k remains, remove from the
// end. Finally strip leading zeros.

// JavaScript note: characters are single-char strings, so comparing st[top] > digit compares them
// lexicographically — which for digit characters '0'-'9' matches numeric order. A plain array is
// the stack.
function removeKDigits(num, k) {
  const st = [];

  for (const digit of num) {
    while (st.length > 0 && k > 0 && st[st.length - 1] > digit) {
      st.pop();
      k--;
    }
    st.push(digit);
  }

  // Remove any remaining digits from the end
  while (k > 0 && st.length > 0) {
    st.pop();
    k--;
  }

  // Build the result and strip leading zeros
  let result = st.join("");
  let i = 0;
  while (i < result.length && result[i] === "0") i++;
  result = result.slice(i);

  return result.length === 0 ? "0" : result;
}

console.log(`Result after removing 2 digits from 541892: ${removeKDigits("541892", 2)}`); // 1892
console.log(`Result after removing 3 digits from 1002991: ${removeKDigits("1002991", 3)}`); // 21

// Time Complexity: O(n). Space Complexity: O(n).
