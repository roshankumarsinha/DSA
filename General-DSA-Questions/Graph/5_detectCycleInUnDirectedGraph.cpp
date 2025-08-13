// Write a function to detect cycle in an undirected graph.

// Notes Link : https://takeuforward.org/data-structure/detect-cycle-in-an-undirected-graph-using-bfs/

// Key Concept : In an undirected graph, a cycle exists if during BFS traversal, we encounter a visited node that is not the parent of the current node.

// Why is this?
// 🧠 Understanding the Logic
// 👉 In an undirected graph, when you go from node A to B, there's always an edge back from B to A.
// This means when you're doing BFS, you will always encounter the parent again, but that’s expected.
// ✅ So we need to ignore the parent when checking visited neighbors.

// 🎯 Now here's the key idea:
// If you visit a neighbor that is:
//    1.  Already visited
//    2.  AND is not the parent of the current node
// Then you have found a back edge, which forms a cycle.

// Approach (Using BFS):
// 1. Use a Queue for BFS Traversal
//    a.  Each queue element should store:
//      a1. The current node
//      a2. Its parent (from which it was discovered)
// 2. Use a Visited Array
//    a.  Track visited nodes to avoid processing the same node again.
// 3. Start BFS from Each Component
//    a.  Since the graph might be disconnected, loop through each node, and run BFS if it’s unvisited.
// 4. For Each Node:
//    a.  Mark it as visited.
//    b.  Push it into the queue with its parent.
//    c.  While the queue is not empty:
//      c1.  Pop the front node and its parent.
//      c2.  For each neighbor of the current node:
//        c21.  If the neighbor is not visited:
//          c211.  Mark it as visited.
//          c212.  Push it into the queue with the current node as its parent.
//        c22.  If the neighbor is visited and is not the parent of the current node:
//          c221.  A cycle is detected, return true.
// 5. If no cycles are found after processing all nodes, return false.


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

    // Function to perform BFS traversal and detect cycle
    bool bfs(int start, vector<bool>& visited) {
        queue<pair<int, int>> q; // Queue to store pairs of (node, parent)
        q.push({start, -1}); // Start with the node and if no parent then add -1.

        while (!q.empty()) {
            int node = q.front().first; // Get the front node
            int parent = q.front().second; // Get the parent of the front node
            
            q.pop(); // Remove it from the queue

            // Traverse all its neighbors
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) { // If neighbor is not visited
                    visited[node] = true; // Mark the current node as visited
                    q.push({neighbor, node}); // Push it into the queue with current node as parent
                } else if (neighbor != parent) { // If neighbor is visited and not the parent
                    return true; // Cycle detected
                }
            }
        }

        return false; // No cycle detected in this component
    }

    // Function to check for cycles in the graph
    bool hasCycle() {
        vector<bool> visited(V, false); // Initialize visited array to false

        // Loop through all vertices to ensure all components are covered
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                if (bfs(i, visited)) { // Start BFS from this vertex
                    return true; // Cycle detected
                }
            }
        }

        return false; // No cycles found in the graph
    }


    // We can solve this using DFS as well
    // void dfs(int node, int parent, vector<bool>& visited) {
    //     visited[node] = true; // Mark the current node as visited
    //     for (int neighbor : adjList[node]) {
    //         if (!visited[neighbor]) { // If neighbor is not visited
    //             dfs(neighbor, node, visited); // Recursively call DFS on the neighbor
    //         } else if (neighbor != parent) { // If neighbor is visited and not the parent
    //             return true; // Cycle detected
    //         }
    //     }
    //     return false; // No cycle detected in this component
    // }
    // Function to check for cycles in the graph using DFS
    // bool hasCycleDFS() {
    //     vector<bool> visited(V, false); // Initialize visited array to false
    //     for (int i = 0; i < V; i++) {
    //         if (!visited[i]) { // If the vertex is not visited
    //             if (dfs(i, -1, visited)) { // Start DFS from this vertex
    //                 return true; // Cycle detected
    //             }
    //         }
    //     }
    //     return false; // No cycles found in the graph
    // }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // This creates a cycle
    g.addEdge(3, 4);

    // Check for cycles in the graph
    if (g.hasCycle()) {
        cout << "Cycle detected in the graph." << endl;
    } else {
        cout << "No cycle detected in the graph." << endl;
    }

    return 0; // Return success
}

// Output:
// Cycle detected in the graph.