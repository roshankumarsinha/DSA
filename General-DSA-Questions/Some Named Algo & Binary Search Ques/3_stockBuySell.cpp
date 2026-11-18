// Write a function to find the maximum profit by buying and selling. One can buy and sell only once.
// Given an array of prices where prices[i] is the price of a stock on day i, find the maximum profit by buying on one day and selling on another later day.
// You can make only one transaction (buy once, sell once).

// Video link : https://www.youtube.com/watch?v=WBzZCm46mFo&list=PLfqMhTWNBTe137I_EPQd34TsgV6IO55pt&index=13
// Example:
// Input: prices = [7, 1, 5, 3, 6, 4]
// Output: 5
// Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), max profit = 6 - 1 = 5.


// 🧠 Why It Works (Intuition)
// 1.   You want to buy at the lowest point and sell at a later higher point.
// 2.   So, you track:
//      a.  minPrice as the lowest price seen so far.
//      b.  value - minPrice as today's potential profit if you sold today.
// 3.   Keep updating the maxProfit.

#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
    int maxProfit = 0;
    int minPrice = INT_MAX;
    for (int value : prices) {
        minPrice = min(minPrice, value);
        maxProfit = max(maxProfit, value - minPrice);
    }
    return maxProfit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << maxProfit(prices) << endl;
    return 0;
}

// How does it work?
// Let's take an example: {7, 1, 5, 3, 6, 4}
// We are assuming that at each iteration, we are selling the stock.
// So, at the first iteration, we are buying the stock at 7 and selling it at 7. So, the profit is 0. maxProfit = 0. minPrice = 7.
// At the second iteration, we are selling the stock at 1. So, the profit is -6. maxProfit = 0. minPrice = 1.
// At the third iteration, we are selling the stock at 5. So, the profit is 4. maxProfit = 4. minPrice = 1.
// At the fourth iteration, we are selling the stock at 3. So, the profit is 2. maxProfit = 4. minPrice = 1.
// At the fifth iteration, we are selling the stock at 6. So, the profit is 5. maxProfit = 5. minPrice = 1.
// At the sixth iteration, we are selling the stock at 4. So, the profit is 3. maxProfit = 5. minPrice = 1.
// So, the maximum profit is 5.
