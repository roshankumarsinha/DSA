// Check if the parentheses in a string are balanced.

// Notes : https://takeuforward.org/data-structure/check-for-balanced-parentheses/

// The string can contain '(', ')', '{', '}', '[' and ']'.
// It is balanced if every opening bracket has a matching closing bracket in the correct order.

// Approach:
// 1. Use a stack to keep track of opening brackets.
// 2. For each character:
//    - If it's an opening bracket, push it.
//    - If it's a closing bracket, the stack top must be the matching opening bracket; otherwise
//      the string is unbalanced.
// 3. At the end, the string is balanced iff the stack is empty.

// JavaScript note: a plain array is used as the stack (push()/pop(), and arr[arr.length-1] as top).
function isValid(s) {
  const st = [];
  for (const ch of s) {
    if (ch === "(" || ch === "{" || ch === "[") {
      st.push(ch);
    } else {
      if (st.length === 0) return false;
      const top = st.pop();
      if (
        (ch === ")" && top === "(") ||
        (ch === "]" && top === "[") ||
        (ch === "}" && top === "{")
      ) {
        continue;
      } else {
        return false;
      }
    }
  }
  return st.length === 0;
}

console.log(isValid("()[{}()]") ? "True" : "False"); // True
