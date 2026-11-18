// Write a function for Moore's algorithm that finds the majority element in an array of integers.
// A majority element appears more than n/2 times where n is the size of the array.

// Example:
// Input: arr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4} → Output: 4 (appears 5 times, > n/2)

// Video link : https://www.youtube.com/watch?v=_xqIp2rj8bo&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=11

// ✅ Intuition:
// If an element appears more than half the times, it will "outvote" all other elements combined.
// So we make one pass to find a candidate, and another to verify it.

// ✅ Steps:
// Candidate Selection Phase:
//  1.  Initialize count = 0 and candidate = null.
//  2.  For each element:
//      a.  If count == 0, set candidate = current element.
//      b.  If current element == candidate → count++
//      c.  Else → count--
// Validation Phase (optional): count occurrences of candidate; if > n/2, it's the majority.

function moore(nums) {
  let candidate = 0;
  let count = 0;
  for (const value of nums) {
    if (value === candidate) {
      count++;
    } else if (count === 0) {
      candidate = value;
      count = 1;
    } else {
      count--;
    }
  }

  // Optional: Validate the candidate
  count = 0;
  for (const value of nums) {
    if (value === candidate) {
      count++;
    }
  }
  // JavaScript note: use Math.floor for n/2 since JS division is floating point.
  if (count <= Math.floor(nums.length / 2)) {
    return -1; // No majority element found
  }
  return candidate;
}

// =====================================================
// MAJORITY ELEMENTS (> N/3 times) - EXTENDED MOORE'S VOTING ALGORITHM
// =====================================================
/*
    Problem: Given an array of size n, find all elements that appear more than n/3 times.

    Example:
    Input: nums = [3, 2, 3]                    → Output: [3]
    Input: nums = [1, 1, 1, 3, 3, 2, 2, 2]     → Output: [1, 2]

    INTUITION (Relation to Moore's Algorithm):
    - Standard Moore (n/2): at most 1 element can appear > n/2 times → track 1 candidate.
    - Extended Moore (n/3): at most 2 elements can appear > n/3 times (3 elements each > n/3
      would total > n, impossible) → track 2 candidates with 2 counters.

    APPROACH:
    Phase 1: Find candidates with modified voting (2 candidates, 2 counters).
    Phase 2: Validate by counting actual occurrences; keep those with count > n/3.

    TIME: O(n)   SPACE: O(1)
*/

function majorityElementN3(nums) {
  const n = nums.length;

  // Phase 1: Find potential candidates
  let cand1 = 0;
  let cand2 = 0;
  let cnt1 = 0;
  let cnt2 = 0;

  for (const num of nums) {
    // Important: check equality first before checking counts
    if (num === cand1) {
      cnt1++;
    } else if (num === cand2) {
      cnt2++;
    } else if (cnt1 === 0) {
      cand1 = num;
      cnt1 = 1;
    } else if (cnt2 === 0) {
      cand2 = num;
      cnt2 = 1;
    } else {
      // Different from both candidates → cancel one vote from each
      cnt1--;
      cnt2--;
    }
  }

  // Phase 2: Validate candidates
  cnt1 = 0;
  cnt2 = 0;
  for (const num of nums) {
    if (num === cand1) cnt1++;
    else if (num === cand2) cnt2++;
  }

  const result = [];
  if (cnt1 > n / 3) result.push(cand1);
  if (cnt2 > n / 3) result.push(cand2);

  return result;
}

console.log(moore([3, 3, 4, 2, 4, 4, 2, 4, 4])); // 4
console.log(majorityElementN3([1, 1, 1, 3, 3, 2, 2, 2])); // [1, 2]
