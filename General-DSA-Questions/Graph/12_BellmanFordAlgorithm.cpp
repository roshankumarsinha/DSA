// Write a function to implement Bellman-Ford Algorithm.

// Bellman-Ford Algorithm is also used to find the shortest path in a graph similar to Dijkstra's Algorithm but it can handle negative weights as well,
// which Dijkstra's Algorithm cannot.
// Bellman-Ford Algorithm can also detect negative cycles in the graph.
// Negative Cycle: A cycle is called a negative cycle if the sum of all its weights becomes negative. The following illustration is an example of a negative cycle:
//      1 ----> 2
//      ^  (-2) | 
//   (2) \      | (-1)
//        \     v
//         ---- 3
//      

// It works for both directed and undirected graphs.

// Notes link : https://takeuforward.org/data-structure/bellman-ford-algorithm-g-41/


// Approach:
// 1. Initialize the distance of the source node to 0 and all other nodes to a very large number.
// 2. Relax all edges V-1 times, where V is the number of vertices in the graph.
// 3. For each edge (u, v) with weight w, if the distance to u + w is less than the distance to v, update the distance to v.
// 4. After V-1 iterations, if we can still relax any edge, it means there is a negative cycle in the graph.
// 5. If no negative cycle is found, return the distance array.
// 6. If a negative cycle is found, return vector with -1 for all nodes.

#include <iostream>
#include <vector>
#include <list>
#include <climits> // For INT_MAX
using namespace std;

class Graph {
  public:
    // Function to implement Bellman-Ford Algorithm
    // V is the number of vertices, edges is the list of edges in the format {u, v, w} where u is the source node, v is the destination node and w is the weight of the edge
    // S is the source node
    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int S) {
        vector<int> distance(V, INT_MAX); // Initialize distance array with a very large number
        distance[S] = 0; // Distance from source to itself is 0

        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto edge : edges) {
                int u = edge[0]; // Source node
                int v = edge[1]; // Destination node
                int w = edge[2]; // Weight of the edge

                // If the distance to u + w is less than the distance to v, update the distance to v
                // This is the relaxation step
                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }

        // Check for negative cycles
        // If we can still relax any edge, it means there is a negative cycle
        for (auto edge : edges) {
            int u = edge[0];  // Source node
            int v = edge[1];  // Destination node
            int w = edge[2];  // Weight of the edge

            // If we can still relax any edge, it means there is a negative cycle
            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                return vector<int>(V, -1); // Return -1 for all nodes if negative cycle is found
            }
        }

        return distance; // Return the distance array
    }
};

int main() {
    Graph g;

    // Example graph with 6 vertices and edges
    int V = 6;

    // We are adding 7 edges to the graph
    // Each edge is represented as {u, v, w} where u is the source node, v is the destination node and w is the weight of the edge
    vector<vector<int>> edges(7, vector<int>(3));
    edges[0] = {3, 2, 6};   // 3 -> 2 with weight 6
	  edges[1] = {5, 3, 1};   // 5 -> 3 with weight 1
	  edges[2] = {0, 1, 5};   // 0 -> 1 with weight 5
	  edges[3] = {1, 5, -3};  // 1 -> 5 with weight -3
	  edges[4] = {1, 2, -2};  // 1 -> 2 with weight -2
	  edges[5] = {3, 4, -2};  // 3 -> 4 with weight -2
	  edges[6] = {2, 4, 3};   // 2 -> 4 with weight 3

    int S = 0; // Source node

    vector<int> distances = g.bellmanFord(V, edges, S); // Find shortest path from source to all other nodes

    cout << "Shortest distances from source node " << S << ":" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Distance to node " << i << ": " << distances[i] << endl; // Print the shortest distance to each node
    }

    return 0; // Return success
}

// Time Complexity:
// 1. O(V * E) where V is the number of vertices and E is the number of edges.
// 2. We relax all edges V-1 times, and for each edge, we check if we can relax it.
// 3. The overall time complexity is O(V * E).

// Space Complexity:
// 1. O(V) for the distance array.
// 2. We are using a distance array to store the shortest distances from the source node to all other nodes.
// 3. The space complexity is O(V).