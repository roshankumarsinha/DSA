// Write a function to find shortest path from source to destination in a directed acyclic graph.

// Notes link : https://takeuforward.org/data-structure/shortest-path-in-directed-acyclic-graph-topological-sort-g-27/

// Given a DAG, find the shortest path from the source to all other nodes in this DAG. In this problem statement, we have assumed the source vertex to be ‘0’. You will be given the weighted edges of the graph.
// Note: What is a DAG ( Directed Acyclic Graph)?
// A Directed Graph (containing one-sided edges) having no cycles is said to be a Directed Acyclic Graph.

// Approach :
// 1. First find the topological sort of the graph.
//    a. Why do we have to find topological sort?
//    b.  If we don’t use topological order:
//      b1. We might try to compute the shortest path to a node before we know the shortest path to its dependencies.
//      b2. This could cause incorrect results or require repeated relaxation like in Bellman-Ford (which is slower).

//    c.  Topological sort gives an order such that for every directed edge u → v, u comes before v.
//    d.  So if we relax edges in topological order, we’re guaranteed that we’ve already found the shortest path to u before considering v

// 2. Initialize a distance array with a very large number.
// 3. Set the distance of the source node to 0.
// 4. Traverse the graph in topological order.
// 5. For each node, relax its neighbors.
// 6. If the distance to a neighbor can be improved, update it. (It is same as the previous question)
// 7. Finally, return the distance array.


#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <climits> // For INT_MAX
using namespace std;

class Graph {
  private:
    int V; // Number of vertices
    // Here we are using a pair to store the weight of the edge and the destination node
    // This is because we are given the weighted edges of the graph
    // Example: 0 → 1 (weight 2), 0 → 2 (weight 3) will be stored as 0 -> {(1, 2), (2, 3)}
    vector<list<pair<int, int>>> adjList; // Adjacency list representation of the graph

  public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V); // Resize the adjacency list to hold V lists
    }

    // Function to add an edge to the graph (directed) along with its weight
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight}); // Add edge from u to v with weight
    }

    // Function to perform DFS and find the topological order
    void dfs(int node, vector<bool>& visited, stack<int>& topoStack) {
        visited[node] = true; // Mark the current node as visited

        // Traverse all its neighbors
        for (auto neighbor : adjList[node]) {
            if (!visited[neighbor.first]) { // If neighbor is not visited
                dfs(neighbor.first, visited, topoStack); // Recursively call DFS on the neighbor
            }
        }

        topoStack.push(node); // Push the current node to the stack after visiting all its neighbors
    }

    // Function to find the shortest path from source to all other nodes in the DAG
    vector<int> shortestPath(int source) {
        vector<bool> visited(V, false); // Initialize visited array to false
        stack<int> topoStack; // Stack to store the topological order

        // Perform DFS for all vertices to find the topological order
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, visited, topoStack); // Start DFS from this vertex
            }
        }

        vector<int> distance(V, INT_MAX); // Initialize distance array with a very large number
        distance[source] = 0; // Distance from source to itself is 0

        // Process vertices in topological order
        while (!topoStack.empty()) {
            int node = topoStack.top(); // Get the top node
            topoStack.pop(); // Remove it from the stack

            // Traverse all its neighbors
            for (auto neighbor : adjList[node]) {
                int neighborNode = neighbor.first; // Get the neighbor node
                int weight = neighbor.second; // Get the weight of the edge

                // If the distance to the neighbor can be improved, update it
                if (distance[node] != INT_MAX && distance[node] + weight < distance[neighborNode]) {
                    distance[neighborNode] = distance[node] + weight; // Update the distance of the neighbor
                }
            }
        }

        // Unreachable nodes will still have the value INT_MAX
        // We can replace it with -1 if needed
        for (int i = 0; i < V; i++) {
            if (distance[i] == INT_MAX) {
                distance[i] = -1; // Mark unreachable nodes as -1
            }
        }

        return distance; // Return the distance array
    }
};

int main() {
    Graph g(6); // Create a graph with 6 vertices

    // Add edges to the graph with weights
    g.addEdge(0, 1, 2);
    g.addEdge(0, 4, 1);
    g.addEdge(1, 2, 3);
    g.addEdge(4, 2, 2);
    g.addEdge(2, 3, 6);
    g.addEdge(4, 5, 4);
    g.addEdge(5, 3, 1);

    vector<int> shortestDistances = g.shortestPath(0); // Find shortest path from source to all other nodes

    cout << "Shortest distances from source node 0:" << endl;
    for (int i = 0; i < shortestDistances.size(); i++) {
        cout << "Distance to node " << i << ": " << shortestDistances[i] << endl; // Print the shortest distance to each node
    }
    return 0;

}

// Graph :
  //      0
  //    /   \
  //   v     v
  //  1       4
  //  |      / \
  //  v     v   v
  //  2 <--     5
  //   \        |
  //    v       v
  //     3 <-----


// and edge weights
// 0 → 1 (2)
// 0 → 4 (1)
// 1 → 2 (3)
// 4 → 2 (2)
// 2 → 3 (6)
// 4 → 5 (4)
// 5 → 3 (1)

// Sort the edges in topological order
// 0 → 4 → 1 → 2 → 5 → 3

// 🛣️ Step 3: Initialize Distances
// Start with:
// dist[0] = 0
// dist[1...5] = INF (1e9)


// 🔁 Step 4: Relax Edges in Topo Order
// ▶️ Node 0
// 0 → 1 (2) → dist[1] = 2
// 0 → 4 (1) → dist[4] = 1
// dist = [0, 2, INF, INF, 1, INF]
// ▶️ Node 4
// 4 → 2 (2) → dist[2] = 1 + 2 = 3
// 4 → 5 (4) → dist[5] = 1 + 4 = 5
// dist = [0, 2, 3, INF, 1, 5]
// ▶️ Node 5
// 5 → 3 (1) → dist[3] = 5 + 1 = 6
// dist = [0, 2, 3, 6, 1, 5]
// ▶️ Node 1
// 1 → 2 (3) → but current dist[2] = 3, and 2 + 3 = 5 > 3 → no update
// ▶️ Node 2
// 2 → 3 (6) → 3 + 6 = 9 > current dist[3] = 6 → no update

// ✅ Final Distances
// Node:     0   1   2   3   4   5
// Dist:     0   2   3   6   1   5

// Time Complexity:
// 1. O(V + E) for DFS traversal to find topological order, where V is the number of vertices and E is the number of edges.
// 2. O(V + E) for processing the edges in topological order.
// 3. Overall time complexity is O(V + E).

// Space Complexity:
// 1. O(V) for the visited array.
// 2. O(V) for the stack used to store the topological order.
// 3. O(V) for the distance array.
// 4. O(V + E) for the adjacency list representation.
// 5. Total space complexity is O(V + E).


// ⚠️ Note
// This method only works on DAGs.

// If the graph has cycles → use Dijkstra (for positive weights) or Bellman-Ford (for negative weights).
