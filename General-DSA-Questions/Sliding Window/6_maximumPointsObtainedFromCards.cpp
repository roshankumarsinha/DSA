// Given N cards arranged in a row, each card has an associated score denoted by the cardScore array.
// Choose exactly k cards. In each step, a card can be chosen either from the beginning or the end of the row.
// The score is the sum of the scores of the chosen cards. Find the maximum score possible.

// Notes link : https://takeuforward.org/data-structure/maximum-point-you-can-obtain-from-cards

// Intuition:
// 1. Instead of choosing k cards from the beginning or the end, we can think of it as removing n-k cards from the array
//    such that the sum of the remaining k cards is maximized.
// 2. This is equivalent to finding a subarray of size n-k with the minimum sum, because removing the subarray with the
//    minimum sum will leave us with the maximum sum of the remaining cards.
// Approach:
// 1. Calculate the total sum of all card scores.
// 2. Use the sliding window technique to find the subarray of size n-k with the minimum sum.
// 3. Subtract the minimum sum of the subarray from the total sum to get the maximum score possible by choosing k cards from the beginning or the end.
// 4. Return the maximum score.

// Explanation with example cardPoints = [1,2,3,4,5,6,1], k = 3:
// - Total sum of cardPoints = 1 + 2 + 3 + 4 + 5 + 6 + 1 = 22
// - We need to find a subarray of size n-k = 7-3 = 4 with the minimum sum.
// - First window of size 4: [1,2,3,4], sum = 10
// - Slide the window:
//   - New window: [2,3,4,5], sum = 14
//   - New window: [3,4,5,6], sum = 18
//   - New window: [4,5,6,1], sum = 16
// - Minimum sum of subarray of size 4 is 10.
// - Maximum score = Total sum - Minimum sum of subarray = 22 - 10 = 12.


#include <iostream>
#include <vector>
#include <climits>  // for INT_MAX
using namespace std;

int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();  // Total number of cards
    int totalSum = 0;   // Total sum of all card scores

    // Calculate the total sum of all card scores
    for (int score : cardPoints) {
        totalSum += score;
    }

    // If k is equal to the number of cards, return the total sum
    if (k == n) {
        return totalSum;
    }

    int windowSize = n - k; // Size of the subarray to find with minimum sum
    int currentWindowSum = 0;   // Current sum of the sliding window

    // Calculate the sum of the first window of size n-k
    for (int i = 0; i < windowSize; i++) {
        currentWindowSum += cardPoints[i];
    }

    int minWindowSum = currentWindowSum;

    // Slide the window across the array to find the minimum sum subarray of size n-k
    for (int i = windowSize; i < n; i++) {
        currentWindowSum = currentWindowSum + cardPoints[i] - cardPoints[i - windowSize];   // Update the window sum, adding the new element and removing the old element
        minWindowSum = min(minWindowSum, currentWindowSum);
    }

    // The maximum score is total sum minus the minimum sum of the subarray of size n-k
    return totalSum - minWindowSum;
}

int main() {
    vector<int> cardPoints = {1, 2, 3, 4, 5, 6, 1};
    int k = 3;
    cout << "Maximum score possible: " << maxScore(cardPoints, k) << endl; // Output: 12
    return 0;
}

// The above approach has a time complexity of O(n) and a space complexity of O(1), where n is the number of cards.
// The algorithm uses a sliding window technique to efficiently find the subarray with the minimum sum.