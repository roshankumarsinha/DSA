// Write a function to detect cycle in a directed graph using BFS.

// Approach we will use Kahn's Algorithm. As you know Kahn's Algorithm is used to find Topological Sort of a Acyclic Directed Graph.
// so, if we are not able to find the topological sort of a directed graph, then we can say that the graph is cyclic.

// Approach:
// 1. All process will be same except we will check if the size of the topological order is equal to the number of vertices.
// 2. If the size of the topological order is not equal to the number of vertices, then we can say that the graph is cyclic.
// 3. If the size of the topological order is equal to the number of vertices, then we can say that the graph is acyclic.


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

    // Function to add an edge to the graph (directed)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
    }

    // Function to perform Topological Sort using Kahn's Algorithm (BFS)
    void topologicalSort() {
        vector<int> inDegree(V, 0); // Initialize in-degree array with 0
        int count = 0; // Count of visited nodes

        // Calculate in-degree of each vertex
        for (int i = 0; i < V; i++) {
            for (int neighbor : adjList[i]) {
                inDegree[neighbor]++; // Increment in-degree for each neighbor
            }
        }

        queue<int> q; // Queue to store vertices with in-degree 0

        // Push all vertices with in-degree 0 into the queue
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i); // Push vertex with in-degree 0 into the queue
            }
        }

        // Process the vertices in the queue
        while (!q.empty()) {
            int node = q.front(); // Get the front node
            q.pop(); // Remove it from the queue
            count++; // Increment the count of visited nodes

            // Traverse all its neighbors
            for (int neighbor : adjList[node]) {
                inDegree[neighbor]--; // Decrease in-degree of the neighbor
                if (inDegree[neighbor] == 0) { // If in-degree becomes 0
                    q.push(neighbor); // Push it into the queue
                }
            }
        }

        // Check if the count of visited nodes is equal to the number of vertices
        if (count != V) {
            cout << "Graph is cyclic" << endl; // If not, the graph is cyclic
        } else {
            cout << "Graph is acyclic" << endl; // If yes, the graph is acyclic
        }
    }
};

int main() {
    Graph g(6); // Create a graph with 6
    // Add edges to the graph
    g.addEdge(5, 0);
    g.addEdge(5, 2);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Perform topological sort
    g.topologicalSort();  // Output: Graph is acyclic

    // Create a cyclic graph
    Graph g2(4); // Create a graph with 4 vertices
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0); // This edge creates a cycle
    g2.addEdge(2, 3);
    g2.topologicalSort(); // Output: Graph is cyclic

    return 0;
}