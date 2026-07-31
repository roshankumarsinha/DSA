// Find the celebrity in a party of n people.

// You are given an n x n matrix M where:
//  M[i][j] === 1 means person i knows person j
//  M[i][j] === 0 means person i does not know person j
// A celebrity is known by everyone else but knows no one.

// Example:
// M = [[0,1,0],[0,0,0],[0,1,0]] → Person 1 is the celebrity.

// Intuition:
// There can be at most one celebrity. Eliminate candidates down to one, then verify.

// helper: does person a know person b?
function knows(M, a, b) {
  return M[a][b] === 1;
}

// Approach 1: Using a Stack
// 1. Push all people onto a stack.
// 2. Pop two at a time: if a knows b, a can't be a celebrity (push b back); else push a back.
// 3. One candidate remains; verify it.
// Time: O(n). Space: O(n).
function findCelebrityStack(M, n) {
  const st = [];
  for (let i = 0; i < n; i++) st.push(i);

  while (st.length > 1) {
    const a = st.pop();
    const b = st.pop();
    if (knows(M, a, b)) {
      st.push(b); // a is not a celebrity
    } else {
      st.push(a); // b is not a celebrity
    }
  }

  const candidate = st.pop();

  // Verify: candidate knows no one and is known by everyone
  for (let i = 0; i < n; i++) {
    if (i !== candidate) {
      if (knows(M, candidate, i)) return -1; // candidate knows someone
      if (!knows(M, i, candidate)) return -1; // someone doesn't know candidate
    }
  }

  return candidate;
}

// Approach 2: Using Two Pointers (O(1) extra space)
// 1. i = 0, j = n-1. If i knows j, i can't be celeb (i++); else j can't be celeb (j--).
// 2. Candidate is where they meet; verify it.
function findCelebrityTwoPointer(M, n) {
  let i = 0;
  let j = n - 1;

  while (i < j) {
    if (knows(M, i, j)) {
      i++; // i knows j → i not a celeb
    } else {
      j--; // i doesn't know j → j not a celeb
    }
  }

  const candidate = i;

  for (let k = 0; k < n; k++) {
    if (k !== candidate) {
      if (M[candidate][k] === 1 || M[k][candidate] === 0) {
        return -1;
      }
    }
  }

  return candidate;
}

// Driver code
const M = [
  [0, 1, 0],
  [0, 0, 0],
  [0, 1, 0],
];
const n = M.length;
const result = findCelebrityStack(M, n);
console.log(result === -1 ? "No celebrity found." : `Celebrity is person ${result}.`); // 1
