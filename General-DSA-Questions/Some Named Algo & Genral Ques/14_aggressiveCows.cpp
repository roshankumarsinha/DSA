// 🧩 Problem Statement
// You are given:
//  1.  An array stalls[] representing positions of n stalls along a straight line.
//  2.  An integer k representing the number of cows.
// Goal: Place k cows in these stalls such that the minimum distance between any two cows is maximized.

// Notes link : https://takeuforward.org/data-structure/aggressive-cows-detailed-solution/
// Video link : https://www.youtube.com/watch?v=R_Mfw4ew-Vo&list=PLgUwDviBIf0pMFMWuuvDNMAkoQFi-h0ZF&index=18

// Example:
// Input: stalls[] = {0, 3, 4, 7, 10, 9}, k = 4
// Output: 3
// The maximum possible minimum distance between any two cows will be 3 when 4 cows are placed at positions {0, 3, 7, 10}.
// Here the distances between cows are 3, 4, and 3 respectively.


// To arrange the cows in a consecutive manner while ensuring a certain distance between them, the initial step is to sort the stalls based on their positions.
// In a sorted array, the minimum distance will always be obtained from any two consecutive cows.
// Arranging the cows in a consecutive manner does not necessarily mean placing them in consecutive stalls.

// Now this problem is also similar to the "Allocate Minimum Number of Pages" problem, because we have to maximize the minimum distance between cows.


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int countCows(vector<int>& stalls, int minDist) {
    int count = 1; // Start with the first cow placed at the first stall, it represents the number of cows placed
    int lastPosition = stalls[0]; // Last position where a cow was placed
    for (int i = 1; i < stalls.size(); i++) { // Start from the second stall
        if (stalls[i] - lastPosition >= minDist) { // If the distance from the last placed cow is greater than or equal to minDist
            count++; // Place a cow here. Place new cow
            lastPosition = stalls[i]; // Update the last position to the current stall
        }
    }
    return count; // Return the total number of cows placed
}

int aggressiveCows(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end()); // Sort the stalls to ensure we can place cows in increasing order of positions
    int left = 1; // Minimum possible distance (at least 1)
    int right = stalls.back() - stalls.front(); // Maximum possible distance (distance between first and last stall)
    int result = 0; // To store the maximum minimum distance found
    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate the mid distance
        int cowsPlaced = countCows(stalls, mid); // Count how many cows can be placed with this minimum distance
        if (cowsPlaced >= k) { // If we can place at least k cows, this can be a valid solution
            result = mid; // Update the result to this mid distance
            left = mid + 1; // Try for a larger minimum distance, since we want to maximize it
        } else {
            right = mid - 1; // If not enough cows can be placed, try a smaller distance
        }
    }
    return result; // Return the maximum minimum distance found
}

int main() {
    vector<int> stalls = {0, 3, 4, 7, 10, 9}; // Example input
    int k = 4; // Number of cows
    cout << aggressiveCows(stalls, k) << endl; // Output the result
    return 0;
}

// Time Complexity: O(N log N) + O(N * log(maxDistance))
// - O(N log N) for sorting the stalls.
// - O(N * log(maxDistance)) for the binary search where maxDistance is the difference between the first and last stall.
// Space Complexity: O(1) - We are using a constant amount of space for variables.
