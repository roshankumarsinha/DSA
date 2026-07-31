// Given an array of asteroids (integers), determine their state after all collisions.
// |value| = size, sign = direction (+ right, - left). On collision the smaller explodes; if equal,
// both explode. Asteroids moving the same direction never collide.

// Notes link : https://takeuforward.org/data-structure/asteroid-collision

// Examples:
// [5, 10, -5] → [5, 10]
// [8, -8] → []
// [4, 7, 1, 1, 2, -3, -7, 17, 15, -16] → [4, 17]

// Intuition:
// Use a stack of surviving asteroids. A collision happens only when the current asteroid moves
// left (negative) and the stack top moves right (positive). Pop smaller right-movers; if equal,
// both explode; otherwise the current asteroid survives (push it).

// JavaScript note: a plain array is the stack; Math.abs replaces C++ abs.
function asteroidCollision(asteroids) {
  const st = [];

  for (const asteroid of asteroids) {
    if (asteroid > 0) {
      st.push(asteroid); // moving right
    } else {
      // moving left; resolve collisions with right-moving asteroids on top
      while (st.length > 0 && st[st.length - 1] > 0 && st[st.length - 1] < Math.abs(asteroid)) {
        st.pop(); // right-mover is smaller → explodes
      }
      if (st.length > 0 && st[st.length - 1] === Math.abs(asteroid)) {
        st.pop(); // equal size → both explode
      } else if (st.length === 0 || st[st.length - 1] < 0) {
        st.push(asteroid); // no collision → survives
      }
      // else: current asteroid is smaller and explodes (do nothing)
    }
  }

  return st;
}

console.log("Final state:", asteroidCollision([4, 7, 1, 1, 2, -3, -7, 17, 15, -16]).join(" ")); // 4 17

// Time Complexity: O(n). Space Complexity: O(n).
