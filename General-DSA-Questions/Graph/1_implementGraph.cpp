// Write a function to implement a Graph.

// Notes link : https://takeuforward.org/graph/graph-representation-in-c/

// We have 2 methods to represent a graph:

// 1. Adjacency List : Each node stores a list of its connected nodes.
// 2. Adjacency Matrix : A 2D array where each cell (i, j) indicates if there's an edge between node i and node j.

#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Adjacency List Representation
class AdjacencyListGraph {
  private:
    int V; // Number of vertices
    vector<list<int>> adjList; // Adjacency list
    // vector<vector<int>> adjList; // Better to use vector<vector<int>> for adjaceny list

  public:
    // Constructor
    AdjacencyListGraph(int vertices) {
        V = vertices; // Set the number of vertices
        adjList.resize(V); // Resize the adjacency list to hold V lists
        // adjList.resize(V, vector<int>());  // Resize the adjacency list to hold V lists
    }

    // Function to add an edge to the graph
    // We assume the graph is undirected
    // So we add edges in both directions
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
        adjList[v].push_back(u); // Add edge from v to u (for undirected graph)
    }

    // Function to print the adjacency list representation of the graph
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " "; // Print each neighbor of vertex i
            }
            cout << endl; // Move to the next line after printing all neighbors
        }
    }
};

// Adjacency Matrix Representation
class AdjacencyMatrixGraph {
  private:
    int V; // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix

  public:
    // Constructor
    AdjacencyMatrixGraph(int vertices) {
        V = vertices; // Set the number of vertices
        adjMatrix.resize(V, vector<int>(V, 0)); // Resize the matrix to VxV and initialize with 0
    }

    // Function to add an edge to the graph
    // 1 represents an edge, 0 represents no edge
    // We assume the graph is undirected
    // So we set both adjMatrix[u][v] and adjMatrix[v][u] to 1
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1; // Set the edge from u to v
        adjMatrix[v][u] = 1; // Set the edge from v to u (for undirected graph)
    }

    // Function to print the adjacency matrix representation of the graph
    void printGraph() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " "; // Print each cell of the matrix
            }
            cout << endl; // Move to the next line after printing each row
        }
    }
};

int main() {
    // Create a graph using adjacency list representation
    AdjacencyListGraph listGraph(4); // Create a graph with 5 vertices
    listGraph.addEdge(0, 1); // Add edges
    listGraph.addEdge(0, 2);
    listGraph.addEdge(1, 2);
    listGraph.addEdge(2, 3);

    cout << "Adjacency List Representation:" << endl;
    listGraph.printGraph(); // Print the adjacency list

    // Create a graph using adjacency matrix representation
    AdjacencyMatrixGraph matrixGraph(4); // Create a graph with 5 vertices
    matrixGraph.addEdge(0, 1); // Add edges
    matrixGraph.addEdge(0, 2);
    matrixGraph.addEdge(1, 2);
    matrixGraph.addEdge(2, 3);

    cout << "Adjacency Matrix Representation:" << endl;
    matrixGraph.printGraph(); // Print the adjacency matrix

    return 0; // Return success
}

// Time Complexity of Adjacency List:
// Operation                       |    Time Complexity
// Add edge (u, v)                 |        O(1)
// Remove edge (u, v)              |   O(degree(u))
// Check if edge (u, v) exists     |   O(degree(u))
// Get all neighbors of u          |   O(degree(u))
// Traverse all vertices and edges |   O(V + E)

// Space Complexity of Adjacency List:
// 1. O(V + E) where V is the number of vertices and E is the number of edges.
// 2. Each vertex has a list of its neighbors, and the total number of edges is E.


// Time Complexity of Adjacency Matrix:
// Operation                       | Time Complexity
// Add edge (u, v)                 |   O(1)
// Remove edge (u, v)              |   O(1)
// Check if edge (u, v) exists     |   O(1)
// Get all neighbors of u          |   O(V)
// Traverse all vertices and edges |   O(V²)

// Space Complexity of Adjacency Matrix:
// 1. O(V²) where V is the number of vertices.
// 2. The matrix is a 2D array of size VxV, which can be inefficient for sparse graphs.
// 3. It uses more space compared to the adjacency list representation, especially for sparse graphs.