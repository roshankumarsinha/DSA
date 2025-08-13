// Write a function to find Topological Sort using BFS and this is called Kahn's Algorithm.

// Notes link : https://takeuforward.org/data-structure/kahns-algorithm-topological-sort-algorithm-bfs-g-22/

// Approach:
// 1. Calculate the in-degree of each vertex.
// 2. Initialize a queue and push all vertices with in-degree 0 into it.
// 3. While the queue is not empty:
//    a.  Pop a vertex from the queue and add it to the topological order.
//    b.  For each of its neighbors, reduce their in-degree by 1.
//    c.  If the in-degree of a neighbor becomes 0, push it into the queue.
// 4. If the topological order contains all vertices, return it.
// 5. If not, return an empty vector (cycle detected).


// 🧠 The Core Idea: Remove Dependencies Layer by Layer
// Think of a Directed Acyclic Graph (DAG) like a chain of tasks where some tasks must be done before others.
// 🧩 So imagine:
//    Tasks (nodes) with no prerequisites (in-degree = 0) → you can do them right now
//    Once you do one of them, it unlocks the next task (decreases in-degree of its neighbors)
// You keep doing tasks that are currently "unlocked", and gradually unlock more. This is topological sorting — a valid linear order of doing tasks.

// 🔄 How the Algorithm Mirrors This:
// 1. Count prerequisites of each node (in-degree)
// 2. Start with nodes that have no prerequisites
// 3. Every time you process a node:
//    a.  You “remove it” from the system
//    b.  You lower the prerequisites of others that depended on it
//    c.  If something now has all prerequisites done → it's ready → add to queue
// 4. Keep repeating this till you’ve done everything

// Intuition:
// Instead of going deep like DFS, BFS topological sort removes nodes layer by layer starting with nodes that have no incoming edges.
// No incoming edges means no dependencies left for that node and it is independent of any other node.
// So, you can process it right now.
// Think of it like:
//  “What can I process right now that no one depends on anymore?”


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
    vector<int> topologicalSort() {
        vector<int> inDegree(V, 0); // Initialize in-degree array with 0
        vector<int> topoOrder; // Vector to store the topological order

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
            topoOrder.push_back(node); // Add it to the topological order

            // Traverse all its neighbors
            for (int neighbor : adjList[node]) {
                inDegree[neighbor]--; // Decrease in-degree of the neighbor
                if (inDegree[neighbor] == 0) { // If in-degree becomes 0
                    q.push(neighbor); // Push it into the queue
                }
            }
        }

        return topoOrder; // Return the topological order
    }

    // Function to print the topological order
    void printTopologicalOrder() {
        vector<int> topoOrder = topologicalSort(); // Get the topological order
        cout << "Topological Sort: ";
        for (int node : topoOrder) {
            cout << node << " "; // Print each node in the topological order
        }
        cout << endl; // Move to the next line after printing all nodes
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
    g.printTopologicalOrder(); // Output: Topological Sort: 5 4 2 3 1 0

    return 0;
}

// Time Complexity:
// 1. O(V + E) for Kahn's Algorithm, where V is the number of vertices and E is the number of edges.
// 2. O(V) for calculating in-degrees.
// 3. O(V + E) for processing the vertices in the queue.
// 4. Overall time complexity is O(V + E).

// Space Complexity:
// 1. O(V) for the in-degree array.
// 2. O(V) for the queue.
// 3. O(V) for the topological order vector.
// 4. Overall space complexity is O(V).