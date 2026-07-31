// Write a function to find the maximum profit by buying and selling. One can buy and sell only once.
// Given prices[] where prices[i] is the price on day i, find the max profit by buying on one day
// and selling on a later day. Only one transaction (buy once, sell once).

// Video link : https://www.youtube.com/watch?v=WBzZCm46mFo&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=13
// Example:
// Input: prices = [7, 1, 5, 3, 6, 4] → Output: 5 (buy at 1, sell at 6)

// 🧠 Why It Works (Intuition)
// 1. You want to buy at the lowest point and sell at a later higher point.
// 2. Track minPrice (lowest so far) and (value - minPrice) as today's potential profit.
// 3. Keep updating maxProfit.

// JavaScript note: C++ used INT_MAX for the initial minimum price. In JS the equivalent is
// Number.POSITIVE_INFINITY (also writable as Infinity).
function maxProfit(prices) {
  let maxProfit = 0;
  let minPrice = Infinity;
  for (const value of prices) {
    minPrice = Math.min(minPrice, value);
    maxProfit = Math.max(maxProfit, value - minPrice);
  }
  return maxProfit;
}

console.log(maxProfit([7, 1, 5, 3, 6, 4])); // 5
