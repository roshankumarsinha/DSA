// Write a function to find the maximum profit by buying and selling. One can buy and sell only once.

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
