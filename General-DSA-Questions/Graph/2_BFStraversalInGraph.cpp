// Write a function to do BFS traversal in a graph. Note: Graph can be disconnected also.

// Notes link : https://takeuforward.org/graph/breadth-first-search-bfs-level-order-traversal/

// Approach:
// 1. Use Adjacency List to represent the graph.
// 2. Track visited nodes using a boolean array.
//    a.  Create a visited[] array (or vector) of size V (number of vertices), initialized to false.
//    b.  This array will help us keep track of which nodes have been visited during the traversal.
// 3. Loop through all nodes in the graph.
//    a.  Because the graph may be disconnected, we can't just start BFS from a single node.
//    b.  We iterate through every vertex i from 0 to V-1. This ensures that we cover all nodes in the graph even if they are not connected.
//      b1. If vertex i is not visited, we:
//        b11.  Start a new BFS from it.
//        b12.  This ensures all components are covered.
// 4. BFS Traversal using Queue
//    a.  For each new unvisited node:
//      a1. Push it into a queue.
//      a2. While the queue is not empty:
//        a21.  Pop the front node.
//        a22.  Visit it (print or store it).
//        a23.  Push all its unvisited neighbors into the queue and mark them visited.
//    b.  This continues until all reachable nodes from the starting vertex are processed.
// 5. Repeat the process for all nodes in the graph.
//    a.  Once one BFS completes, the outer loop ensures BFS starts again from any other unvisited vertex, covering the entire graph.

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

    // Function to perform BFS traversal
    void bfs() {
        vector<bool> visited(V, false); // Initialize visited array to false

        // Loop through all vertices to ensure all components are covered
        // So assume there's a disconnected graph with 2 nodes we can cover that using looping through all vertices
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                queue<int> q; // Create a queue for BFS
                q.push(i); // Start BFS from this vertex
                visited[i] = true; // Mark it as visited

                while (!q.empty()) { // While the queue is not empty
                    int node = q.front(); // Get the front node
                    q.pop(); // Remove it from the queue
                    cout << node << " "; // Visit the node (print it)

                    // Traverse all its neighbors
                    for (int neighbor : adjList[node]) {
                        if (!visited[neighbor]) { // If neighbor is not visited
                            q.push(neighbor); // Push it into the queue
                            visited[neighbor] = true; // Mark it as visited
                        }
                    }
                }
            }
        }
    }
};

int main() {
    Graph g(7); // Create a graph with 5 vertices

    // Component 1
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    
    // Component 2
    g.addEdge(3, 4);

    // Component 3
    g.addEdge(5, 6);

    cout << "BFS Traversal of the graph: ";
    g.bfs(); // Perform BFS traversal
    cout << endl; // Print a newline after traversal

    return 0;
}

// Output:
// BFS Traversal of the graph: 0 1 2 3 4 5 6

// Time Complexity:
// 1. O(V + E) for BFS traversal, where V is the number of vertices and E is the number of edges.
// 2. Each vertex and edge is processed once.

// Space Complexity:
// 1. O(V + E) for the adjacency list representation.
// 2. O(V) for the visited array.
// 3. O(V) for the queue used in BFS.
// 4. Total space complexity is O(V + E).