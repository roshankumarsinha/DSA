// Write a function to detect cycle in a directed graph.

// Notes Link : https://takeuforward.org/data-structure/detect-cycle-in-a-directed-graph-using-dfs-g-19/

// Key Concept : "If we revisit a node that’s already in the recursion stack (recStack), then a cycle exists in a directed graph."

// 🧠 Intuition Behind the Condition:
// In a directed graph, we follow one-way paths from a node to its neighbors.
// Now imagine you're doing a DFS traversal starting at some node u.
// You mark u as:
//  a.  Visited
//  b.  Part of the current recursion path (pathVisited)

// You then recursively visit its neighbor v, then neighbor of v, and so on...

// 🎯 The moment you reach a node that's already in the current recursion path, it means:
// You started at a node, followed a path, and returned to a node that was already part of the current path.

// That’s exactly the definition of a cycle.



// In DFS cycle detection for directed graphs, we maintain:
//  a.  visited[]: to check if a node has been explored at all
//  b.  pathVisited[]: to check if a node is part of the current DFS path

// Now you’re asking:
// Why can't we just use visited[] to detect cycles? Why do we need pathVisited[]?

// 🧠 Short Answer:
// Just because a node has been visited before, doesn’t mean visiting it again forms a cycle.
// Example: point 6 to 3
//                1 → 2 → 3
//                ↓       ↑ 
//                4 → 5 → 6
// It could’ve been visited via a completely different path, and going to it again doesn’t mean you looped back.
// But if the node is in the current path (pathVisited) and you revisit it → you looped back before finishing the path → cycle ✅


// Approach:
// 1. Use DFS to traverse the graph.
// 2. Maintain two arrays:
//    a.  visited[]: to check if a node has been explored at all
//    b.  pathVisited[]: to check if a node is part of the current DFS path
// 3. For each node:
//    a.  If it’s not visited, call DFS on it.
//    b.  In the DFS function:
//      b1.  Mark the node as visited and add it to the pathVisited.
//      b2.  For each neighbor of the current node:
//        b21.  If the neighbor is not visited, call DFS on it.
//        b22.  If the neighbor is in the pathVisited, a cycle is detected.
//      b23.  After exploring all neighbors, remove the node from the pathVisited.
// 4. If no cycles are found after processing all nodes, return false.


#include <iostream>
#include <vector>
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

    // Function to add an edge to the graph (directed)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
    }

    // Function to perform DFS traversal and detect cycle
    bool dfs(int node, vector<bool>& visited, vector<bool>& pathVisited) {
        visited[node] = true; // Mark the current node as visited
        // Add the node the pathVisited. Path visited is used to keep track of the nodes in the current path
        pathVisited[node] = true;

        // Traverse all its neighbors
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) { // If neighbor is not visited
                if (dfs(neighbor, visited, pathVisited)) { // Recursively call DFS on the neighbor
                    return true; // Cycle detected
                }
            } else if (pathVisited[neighbor]) { // If neighbor is in the recursion stack
                return true; // Cycle detected
            }
        }

        // After exploring all neighbors, remove the node from the pathVisited
        // This indicates that we are done exploring this path
        // and we are backtracking
        // This is important because we need to allow other paths to explore this node
        pathVisited[node] = false;
        return false; // No cycle detected
    }

    // Function to check for cycles in the graph
    bool hasCycle() {
        vector<bool> visited(V, false); // Initialize visited array to false
        vector<bool> pathVisited(V, false); // Initialize recursion stack to false

        // Loop through all vertices to ensure all components are covered
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                if (dfs(i, visited, pathVisited)) { // Start DFS from this vertex
                    return true; // Cycle detected
                }
            }
        }

        return false; // No cycles found in the graph
    }
};

int main() {
    Graph g(4); // Create a graph with 4 vertices

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0); // This edge creates a cycle
    g.addEdge(2, 3);

    // Check for cycles in the graph
    if (g.hasCycle()) {
        cout << "Cycle detected in the directed graph." << endl;
    } else {
        cout << "No cycle detected in the directed graph." << endl;
    }

    return 0; // Return success
}