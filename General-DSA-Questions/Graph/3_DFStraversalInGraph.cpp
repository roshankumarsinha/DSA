// Write a function to traverse a graph using DFS. Note that we can have disconnected graphs also.

// Notes Link : https://takeuforward.org/data-structure/depth-first-search-dfs/

// The Approach is almost similar to BFS but we use recursion instead of a queue.
// The graph is traversed in a depth-first manner instead of level-order.

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

    // Function to add an edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
        adjList[v].push_back(u); // Add edge from v to u (for undirected graph)
    }

    // Function to perform DFS traversal
    // node is the current node to start DFS from
    // visited is a vector to keep track of visited nodes
    void dfs(int node, vector<bool>& visited) {
        visited[node] = true; // Mark the current node as visited
        cout << node << " "; // Visit the node (print it)

        // Traverse all its neighbors
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) { // If neighbor is not visited
                dfs(neighbor, visited); // Recursively call DFS on the neighbor
            }
        }
    }

    // Function to perform DFS traversal for the entire graph
    void dfsTraversal() {
        vector<bool> visited(V, false); // Initialize visited array to false

        // Loop through all vertices to ensure all components are covered
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                dfs(i, visited); // Start DFS from this vertex
            }
        }
    }
};

int main() {
    Graph g(7); // Create a graph with 7 vertices

    // Component 1
    g.addEdge(0, 1);
    g.addEdge(0, 2);

    // Component 2
    g.addEdge(3, 4);

    // Component 3
    g.addEdge(5, 6);

    cout << "DFS Traversal of the graph: ";
    g.dfsTraversal(); // Perform DFS traversal
    cout << endl;

    return 0; // Return success
}

// Output:
// DFS Traversal of the graph: 0 1 2 3 4 5 6

// Time Complexity:
// O(V + E), where V is the number of vertices and E is the number of edges.
// This is because we visit each vertex and edge once during the traversal.

// Space Complexity:
// O(V), where V is the number of vertices.
// This is due to the visited array and the recursion stack used during DFS.

// BFS vs DFS Comparison Table:
// | Feature                         |       BFS (Breadth-First Search)          | DFS (Depth-First Search) |
// |---------------------------------|-------------------------------------------|--------------------------|
// | Traversal Order                 | Level by level (breadth-wise)             | Depth-wise (go as deep as possible first) |
// | Data Structure Used             | Queue                                     | Stack (or recursion)     |
// | Shortest Path (Unweighted Graph)| ✅ Yes                                     | ❌ No (not guaranteed)   |
// | Suitable For                    | Finding shortest path, closer nodes        | Topological sort, cycle detection |
// | Time Complexity                 | O(V + E)                                   | O(V + E)                |
// | Space Complexity                | O(V) – stores all nodes at current level   | O(V) – stores recursive stack |
// | Memory Usage                    | More (due to queue for wide graphs)        | Less (usually)         |
// | Works on Disconnected Graph?    | ✅ Yes (if loop over all nodes)            | ✅ Yes (if loop over all nodes) |
// | Implementation                  | Iterative (easier with queue)              | Recursive or iterative (with stack) |