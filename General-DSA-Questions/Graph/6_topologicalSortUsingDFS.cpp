// Write a function to find Topological Sort using DFS.

// Notes link : https://takeuforward.org/data-structure/topological-sort-algorithm-dfs-g-21/

// What is Topological Sort?
// Topological sort is a linear ordering of vertices such that for every directed edge u → v, vertex u comes before v in the ordering.
// Example:
//  5 → 0   4 → 0
//  ↓       ↓
//  2 → 3 → 1

// One possible topological sort is: 5, 4, 2, 3, 1, 0, because:
// Adjacency List Representation:
// 5 → 0
// 5 → 2
// 4 → 0
// 4 → 1
// 2 → 3
// 3 → 1
// so, 5 comes before 0, 4 comes before 0, 2 comes before 3, and 3 comes before 1.

// We can find Topological sort only if there's no cycle in the graph because if there's a cycle, we can't have a linear ordering because if there is cycle, we will have edge from 1 to 2, 2 to 3, and 3 to 1, so we can't have a linear ordering.
// We can find Topological sort only if it is a Directed Graph because in an undirected graph, we can't have a linear ordering because there's a edge from 1 to 2 and 2 to 1, so we can't have a linear ordering.


// Approach:
// 1. Perform a DFS
// 2. After visiting all neighbors of a node, push it onto a stack
// 3. Finally, pop all elements from the stack to get the topological order

// 🎯 Why Does This Work?
// In DFS:
// 1. You only push a node to the result after exploring all its dependencies
// 2. So by the time you push u, you’ve already handled everything that should come after it
// 3. This naturally gives the topological order when you reverse the finish times.


#include <iostream>
#include <vector>
#include <stack>
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

    // Function to perform DFS and fill the stack with topological order
    void dfs(int node, vector<bool>& visited, stack<int>& Stack) {
        visited[node] = true; // Mark the current node as visited

        // Traverse all its neighbors
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) { // If neighbor is not visited
                dfs(neighbor, visited, Stack); // Recursively call DFS on the neighbor
            }
        }

        // After exploring all neighbors, push the current node onto the stack
        // This ensures that the current node is added after all its dependencies
        // have been added to the stack
        Stack.push(node);
    }

    // Function to perform topological sort
    void topologicalSort() {
        stack<int> Stack; // Stack to store the topological order
        vector<bool> visited(V, false); // Initialize visited array to false

        // Loop through all vertices to ensure all components are covered
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                dfs(i, visited, Stack); // Start DFS from this vertex
            }
        }

        // Print the topological order by popping elements from the stack
        cout << "Topological Sort: ";
        while (!Stack.empty()) {
            cout << Stack.top() << " "; // Print the top element of the stack
            Stack.pop(); // Remove it from the stack
        }
        cout << endl; // Move to the next line after printing all elements
    }
};

int main() {
    Graph g(6); // Create a graph with 6 vertices

    // Add edges to the graph
    g.addEdge(5, 0);
    g.addEdge(5, 2);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Perform topological sort
    g.topologicalSort(); // Output: Topological Sort: 5 4 2 3 1 0

    return 0; // Return success
}

