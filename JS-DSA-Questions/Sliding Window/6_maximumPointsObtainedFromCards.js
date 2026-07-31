// Given N cards in a row, each with a score in cardPoints[]. Choose exactly k cards, each taken
// from either the beginning or the end of the row. Return the maximum total score.

// Notes link : https://takeuforward.org/data-structure/maximum-point-you-can-obtain-from-cards

// Intuition:
// 1. Choosing k cards from the two ends is the same as REMOVING a contiguous block of (n-k)
//    cards from the middle.
// 2. To maximize the score of the kept cards, we remove the middle window of size (n-k) that has
//    the MINIMUM sum. maxScore = totalSum - minWindowSum.

// Approach:
// 1. Compute totalSum. If k === n, return totalSum (we take everything).
// 2. Use a fixed-size sliding window of size (n-k) to find the minimum window sum.
// 3. Return totalSum - minWindowSum.

// Example: cardPoints = [1,2,3,4,5,6,1], k = 3 → 12.

function maxScore(cardPoints, k) {
  const n = cardPoints.length;
  let totalSum = 0;
  for (const score of cardPoints) {
    totalSum += score;
  }

  // If k equals the number of cards, take all of them
  if (k === n) {
    return totalSum;
  }

  const windowSize = n - k; // size of the block we remove
  let currentWindowSum = 0;

  // Sum of the first window of size n-k
  for (let i = 0; i < windowSize; i++) {
    currentWindowSum += cardPoints[i];
  }

  let minWindowSum = currentWindowSum;

  // Slide the window to find the minimum-sum window of size n-k
  for (let i = windowSize; i < n; i++) {
    currentWindowSum += cardPoints[i] - cardPoints[i - windowSize]; // add new, remove old
    minWindowSum = Math.min(minWindowSum, currentWindowSum);
  }

  return totalSum - minWindowSum;
}

console.log("Maximum score possible:", maxScore([1, 2, 3, 4, 5, 6, 1], 3)); // 12

// Time Complexity: O(n). Space Complexity: O(1).
