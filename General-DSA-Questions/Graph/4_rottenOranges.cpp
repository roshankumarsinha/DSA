// Write a C== function to find minimum time required to rot all oranges in a grid.
// We have a grid (matrix) where:
//  0 → Empty cell
//  1 → Fresh orange
//  2 → Rotten orange
// Rules:
// A rotten orange can rot adjacent fresh oranges (up, down, left, right) in 1 minute.
// We need to find the minimum time to rot all oranges.
// If there is at least one orange that can’t be rotten, return -1.

// Approach: BFS (Breadth-First Search)
// 1. Use a queue to perform BFS.
// 2. Push all initially rotten oranges into a queue (multi-source BFS starting points).
// 3. Count total fresh oranges at the start.
// 4. Perform BFS:
//    a. For each rotten orange, check its adjacent cells.
//    b. If an adjacent cell has a fresh orange, rot it and push it into the queue.
//    c. Decrease the count of fresh oranges.
// 5. Keep track of time taken (levels in BFS).
// 6. If all fresh oranges are rotten, return the time taken; otherwise, return -1.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int minTimeToRotAllOranges(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    queue<pair<int, int>> q; // Queue to store positions of rotten oranges, pair of (row, col)
    int freshCount = 0; // Count of fresh oranges

    // Step 1: Initialize the queue with all rotten oranges and count fresh oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) { // If the orange is rotten
                q.push({i, j}); // Push its position into the queue
            } else if (grid[i][j] == 1) { // If the orange is fresh
                freshCount++; // Increment the count of fresh oranges
            }
        }
    }

    // If there are no fresh oranges, return 0 (no time needed)
    if (freshCount == 0) return 0;

    int time = 0; // Time taken to rot all oranges

    // Directions for adjacent cells (up, down, left, right)
    // Move Down:   row + 1, col stays the same
    // Move Up:     row - 1, col stays the same
    // Move Right:  row stays the same, col + 1
    // Move Left:   row stays the same, col - 1
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Step 2: Perform BFS
    while (!q.empty()) {
        int size = q.size(); // Number of rotten oranges at the current level
        bool hasRotten = false; // Flag to check if any fresh orange is rotted in this level

        for (int i = 0; i < size; i++) {
            // Get the position of the rotten orange
            int rowRotten = q.front().first;
            int colRotten = q.front().second;
            q.pop(); // Remove it from the queue
            
            // Check all four directions
            for (int d = 0; d < 4; d++) {
                int newRow = rowRotten + directions[d].first;
                int newCol = colRotten + directions[d].second;

                // Check if the new position is within bounds and has a fresh orange
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 1) {
                    grid[newRow][newCol] = 2; // Rot the fresh orange
                    q.push({newRow, newCol}); // Add it to the queue
                    freshCount--; // Decrease the count of fresh oranges
                    hasRotten = true; // Mark that we have rotted at least one orange
                }
            }
        }

        // If we rotted any orange in this level, increase the time
        if (hasRotten) {
            time++;
        }
    }

    // If there are still fresh oranges left, return -1
    return freshCount > 0 ? -1 : time;
}

// Example usage
int main() {
    vector<vector<int>> grid = {
        {2, 1, 0},
        {1, 1, 0},
        {0, 1, 2}
    };

    int result = minTimeToRotAllOranges(grid);
    cout << "Minimum time to rot all oranges: " << result << endl; // Output: 2

    return 0;
}
// Example grid:
// 2 1 0
// 1 1 0
// 0 1 2
// In this example, it takes 2 minutes to rot all oranges.
// The first minute, the rotten oranges at (0,0) and (2,2) rot their adjacent fresh oranges.
// The second minute, the remaining fresh orange at (1,1) is rotted.

    