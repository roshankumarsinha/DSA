// Write a function to find shortest path from source to destination in a undirected graph.
// Given an Undirected Graph having unit weight, find the shortest path from the source to all other nodes in this graph.

// Notes link : https://takeuforward.org/data-structure/shortest-path-in-undirected-graph-with-unit-distance-g-28/

// Approach using BFS:
// 1. We will use BFS to find the shortest path from the source to all other nodes.
// 2. We will use a queue to store the nodes to be visited.
// 3. We will use a distance array to store the distance from the source to each node.
// 4. We will initialize the distance of the source to 0 and all other nodes to with a very large number.
// 5. We will start from the source and visit all its neighbors.
// 6. For each neighbor, if the distance from the source to the neighbor is greater than the distance from the source to the current node + 1, we will update the distance of the neighbor and add it to the queue.
// 7. We will continue this process until the queue is empty.
// 8. Finally, we will return the distance array.

// Intution behind this approach is that BFS travels level by level, so we can be sure that the first time we reach a node, it is the shortest path to that node.

#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Graph {
  private:
    int V; // Number of vertices
    vector<list<int>> adjList; // Adjacency list representation of the graph

  public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V); // Resize the adjacency list to hold V lists
    }

    // Function to add an edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
        adjList[v].push_back(u); // Add edge from v to u (for undirected graph)
    }

    // Function to find the shortest path from source to all other nodes
    vector<int> shortestPath(int source) {
        vector<int> distance(V, INT_MAX); // Initialize distance array with a very large number
        queue<int> q; // Queue to store nodes to be visited

        distance[source] = 0; // Distance from source to itself is 0
        q.push(source); // Start BFS from the source

        while (!q.empty()) {
            int node = q.front(); // Get the front node
            q.pop(); // Remove it from the queue

            // Traverse all its neighbors
            for (int neighbor : adjList[node]) {
                // If the distance from the source to the neighbor is greater than the distance from the source to the current node + 1
                // then update the distance of the neighbor and add it to the queue
                if (distance[node] + 1 < distance[neighbor]) {
                    distance[neighbor] = distance[node] + 1; // Update the distance of the neighbor
                    q.push(neighbor); // Add the neighbor to the queue
                }
            }
        }

        // Updated shortest distances are stored in the resultant array ‘ans’.
        // Unreachable nodes are marked as -1. 
        vector<int> ans(V, -1);
        for (int i = 0; i < V; i++) {
            if (distance[i] != INT_MAX) {
                ans[i] = distance[i]; // Update the answer array with the shortest distance
            }
        }
        return ans; // Return the distance array
    }
};

int main() {
    Graph g(9); // Create a graph with 9 vertices

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(1, 2);
    g.addEdge(2, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(6, 8);

    int source = 0; // Source node
    vector<int> shortestDistances = g.shortestPath(source); // Find shortest path from source to all other nodes
    cout << "Shortest distances from source " << source << " to all other nodes:" << endl;
    for (int i = 0; i < shortestDistances.size(); i++) {
        cout << "Distance to node " << i << ": " << shortestDistances[i] << endl; // Print the shortest distance to each node
    }
    return 0; // Return success
}

// Graph :
  //     0
  //    / \
  //   1   3
  //  /     \
  // 2       4
  //  \       \
  //   6 - 5   8
  //   | \  /
  //   7  8

// Output:
// Node 0: distance 0 (start)
// Node 1: distance 1 (0 → 1)
// Node 2: distance 2 (0 → 1 → 2)
// Node 3: distance 1 (0 → 3)
// Node 4: distance 2 (0 → 3 → 4)
// Node 5: distance 3 (0 → 3 → 4 → 5)
// Node 6: distance 3 (0 → 1 → 2 → 6 or 0 → 3 → 4 → 5 → 6)
// Node 7: distance 4 (0 → … → 6 → 7)
// Node 8: distance 4 (0 → … → 6 → 8 or 0 → 3 → 4 → 5 → 6 → 8)
