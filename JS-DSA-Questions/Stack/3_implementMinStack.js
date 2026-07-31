// Design a stack that supports push, pop, top, and retrieving the minimum element in O(1) time.

// Notes : https://takeuforward.org/data-structure/implement-min-stack-o2n-and-on-space-complexity/

// Approach 1 (using pairs to store value and min-so-far):
// Store each entry as [value, minSoFar]. getMin() reads the top's minSoFar. Uses O(n) extra space.
//
// class MinStackPairs {
//   constructor() { this.st = []; }
//   push(x) {
//     const min = this.st.length === 0 ? x : Math.min(this.st[this.st.length - 1][1], x);
//     this.st.push([x, min]);
//   }
//   pop() { this.st.pop(); }
//   top() { return this.st[this.st.length - 1][0]; }
//   getMin() { return this.st[this.st.length - 1][1]; }
// }

// Approach 2 (single stack, O(1) extra space using an encoding trick):
// 1. push: if x < mini, push the modified value (2*x - mini) and update mini = x; else push x.
// 2. getMin: return mini.
// 3. top: if the stored top < mini, the real top is mini (top was encoded); else return the top.
// 4. pop: if the top < mini, it was an encoded value → restore previous min: mini = 2*mini - top.
//
// Why the formula works: when x < mini we store (2x - mini) which is < x < mini, marking it as
// "encoded". On pop, previousMin = 2*mini - storedTop recovers the earlier minimum.

// JavaScript note: C++ used INT_MAX to initialize mini; here we use Infinity. A plain array is the
// underlying stack.
class SpecialStack {
  constructor() {
    this.s = [];
    this.mini = Infinity;
  }

  push(data) {
    if (this.s.length === 0) {
      this.s.push(data);
      this.mini = data;
    } else if (data < this.mini) {
      this.s.push(2 * data - this.mini); // store modified value
      this.mini = data;
    } else {
      this.s.push(data); // store normal value
    }
  }

  pop() {
    if (this.s.length === 0) return -1;

    const curr = this.s.pop();
    if (curr > this.mini) {
      return curr; // not modified
    } else {
      // modified value → restore previous minimum
      const prevMin = this.mini;
      this.mini = 2 * this.mini - curr;
      return prevMin;
    }
  }

  top() {
    if (this.s.length === 0) return -1;
    const curr = this.s[this.s.length - 1];
    return curr < this.mini ? this.mini : curr;
  }

  isEmpty() {
    return this.s.length === 0;
  }

  getMin() {
    if (this.s.length === 0) return -1;
    return this.mini;
  }
}

// Driver code
const st = new SpecialStack();
st.push(5);
st.push(3);
st.push(7);
console.log("Min:", st.getMin()); // 3
console.log("Top:", st.top()); // 7
st.pop();
st.pop();
console.log("Min after pops:", st.getMin()); // 5
