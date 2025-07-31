// There are some gas stations along a circular route. You are given two integer arrays gas[] denoted as the amount of gas present at each station and cost[] denoted as the cost of travelling to the next station.
// You have a car with an unlimited gas tank. You begin the journey with an empty tank from one of the gas stations.
// Return the index of the starting gas station if it's possible to travel around the circuit without running out of gas at any station in a clockwise direction. If there is no such starting station exists, return -1.

// Approach:
// Key Observations:

// 1. The total gas available in all stations must be greater than or equal to the total cost for the journey; otherwise, completing the tour is impossible.
// 2. If you run out of gas at a particular station, it means that no station between the current starting station and this station can be the solution. Hence, you can skip all those stations.

// Intuition:
// Think of:
//  1.  balance: as your current fuel tank
//  2.  deficit: as the fuel shortfall when you realize you can't continue
//  3.  start: the current candidate starting point
// We simulate going around the circle and:
//  1.  Add (petrol - distance) to our balance.
//  2.  If at any point, balance < 0 → we cannot start from current start. So we:
//      a.  Move start to the next station (i+1)
//      b.  Accumulate the shortfall (deficit)
//      c.  Reset the balance
// Finally:
//  1.  If balance + deficit >= 0, then starting from start allows full tour.
//  2.  Else, return -1.


#include <iostream>
#include <vector>
using namespace std;

int circularTour(const vector<int>& gas, const vector<int>& cost) {
    int deficit = 0; // Total deficit encountered
    int balance = 0; // Current balance of gas
    int start = 0;   // Starting index of the gas station
    int n = gas.size(); // Number of gas stations

    for(int i = 0; i < n; i++) {
        balance += gas[i] - cost[i]; // Update balance with gas and cost at station i

        // If balance goes negative, we cannot start from 'start', we need to reset
        if (balance < 0) {
            deficit += balance;  // Accumulate the deficit
            start = i + 1;       // Move start to the next station
            balance = 0;         // Reset balance
        }
    }

    // If total balance is enough to cover the deficit, we can complete the tour
    if (balance + deficit >= 0) {
        return start; // Return the starting index
    } else {
        return -1; // Not possible to complete the tour
    }
}

int main() {
    vector<int> gas = {4, 6, 7, 4};
    vector<int> cost = {6, 5, 3, 5};

    int startIndex = circularTour(gas, cost);
    if (startIndex != -1) {
        cout << "Starting gas station index: " << startIndex << endl;
    } else {
        cout << "No valid starting gas station found." << endl;
    }

    return 0;
}
// Time Complexity: O(n) - We traverse the gas stations once.
// Space Complexity: O(1) - We use a constant amount of space for variables.


// Why it works:
// 1. If we can complete the tour starting from a station, it means that the total gas available is sufficient to cover the total cost.
// 2. The algorithm efficiently finds the starting station by skipping over stations that cannot be part of a valid tour, ensuring we only check each station once.
// 3. The balance and deficit tracking allows us to determine if the remaining gas can cover the shortfall encountered during the journey.

