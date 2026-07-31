// Gas Station / Circular Tour problem.
// Given gas[] (gas available at each station) and cost[] (cost to travel to the next station),
// starting with an empty tank, return the index of the starting station from which you can travel
// the full circle clockwise, or -1 if impossible.

// Example:
// Input: gas = [1, 2, 3, 4, 5], cost = [3, 4, 5, 1, 2] → Output: 3

// Approach / Key Observations:
// 1. If total gas < total cost, the tour is impossible.
// 2. If you run out of gas partway, none of the stations from the current start up to here can be
//    the answer — skip them all.
//
// Track:
//  - balance: current fuel in the tank
//  - deficit: accumulated shortfall when balance goes negative
//  - start: current candidate starting station
// Add (gas[i] - cost[i]) to balance. If balance < 0, add it to deficit, move start to i+1, reset
// balance. Finally, if balance + deficit >= 0, start is the answer; else -1.

function circularTour(gas, cost) {
  let deficit = 0;
  let balance = 0;
  let start = 0;
  const n = gas.length;

  for (let i = 0; i < n; i++) {
    balance += gas[i] - cost[i];

    // Can't start from 'start'; reset
    if (balance < 0) {
      deficit += balance;
      start = i + 1;
      balance = 0;
    }
  }

  return balance + deficit >= 0 ? start : -1;
}

const gas = [4, 6, 7, 4];
const cost = [6, 5, 3, 5];
const startIndex = circularTour(gas, cost);
console.log(startIndex !== -1 ? `Starting gas station index: ${startIndex}` : "No valid starting gas station found.");

// Time Complexity: O(n). Space Complexity: O(1).
