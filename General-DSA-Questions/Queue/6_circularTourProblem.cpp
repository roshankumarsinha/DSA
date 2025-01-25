// There are some gas stations along a circular route. You are given two integer arrays gas[] denoted as the amount of gas present at each station and cost[] denoted as the cost of travelling to the next station. You have a car with an unlimited gas tank. You begin the journey with an empty tank from one of the gas stations. Return the index of the starting gas station if it's possible to travel around the circuit without running out of gas at any station in a clockwise direction. If there is no such starting station exists, return -1.

// Approach:
// Key Observations:

// 1. The total gas available in all stations must be greater than or equal to the total cost for the journey; otherwise, completing the tour is impossible.
// 2. If you run out of gas at a particular station, it means that no station between the current starting station and this station can be the solution. Hence, you can skip all those stations.

#include <iostream>
#include <vector>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalGas = 0;    // Total surplus gas for the entire route
    int currentGas = 0;  // Current surplus gas for the current segment
    int startIndex = 0;  // Potential starting index
    int netGas = 0;      // Net gas for the current segment

    for (int i = 0; i < gas.size(); i++) {
        netGas = gas[i] - cost[i];
        totalGas += netGas;
        currentGas += netGas;

        // If currentGas is negative, reset the starting station
        if (currentGas < 0) {
            startIndex = i + 1;
            currentGas = 0;
        }
    }

    // If totalGas is negative, no solution exists
    return totalGas >= 0 ? startIndex : -1;
}

int main() {
    vector<int> gas = {1, 2, 3, 4, 5};
    vector<int> cost = {3, 4, 5, 1, 2};

    int result = canCompleteCircuit(gas, cost);
    if (result != -1) {
        cout << "The starting gas station index is: " << result << endl;
    } else {
        cout << "It's not possible to complete the circuit." << endl;
    }

    return 0;
}

// Explaination of Example step by step in each iteration:
// gas = [1, 2, 3, 4, 5], cost = [3, 4, 5, 1, 2]
// totalGas = 0, currentGas = 0, startIndex = 0, netGas = 0
// i = 0: netGas = 1 - 3 = -2, totalGas = -2, currentGas = -2. Reset startIndex = i(0) + 1 = 1, currentGas = 0 as currentGas is negative.
// i = 1: netGas = 2 - 4 = -2, totalGas = -4, currentGas = -2. Reset startIndex = i(1) + 1 = 2, currentGas = 0 as currentGas is negative.
// i = 2: netGas = 3 - 5 = -2, totalGas = -6, currentGas = -2. Reset startIndex = i(2) + 1 = 3, currentGas = 0 as currentGas is negative.
// i = 3: netGas = 4 - 1 = 3, totalGas = -3, currentGas = 3. currentGas is positive, so continue.
// i = 4: netGas = 5 - 2 = 3, totalGas = 0, currentGas = 6. currentGas is positive, so continue.
// The total gas available is greater than or equal to the total cost. Hence, the starting gas station index is 3.

