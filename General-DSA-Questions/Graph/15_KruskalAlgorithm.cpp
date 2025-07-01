// Write a function to implement Kruskal's Algorithm.

// Kruskal's Algorithm is a greedy algorithm used to find the Minimum Spanning Tree (MST) of a connected, undirected, weighted graph.

// It works by sorting the edges of the graph in non-decreasing order of their weights and adding them to the MST, ensuring that no cycles are formed.
// It is implemented using the Disjoint Set data structure.

// Notes link for Kruskal's Algorithm : https://takeuforward.org/data-structure/kruskals-algorithm-minimum-spanning-tree-g-47/
// Watch video of TakeUForward.

#include <iostream>
#include <vector>
#include <algorithm>    // This is needed for the sort function
using namespace std;

// Disjoint Set class to manage the connected components using union by size
class DisjointSet {
  private:
    vector<int> parent; // Parent array to store the parent of each node
    vector<int> size; // Size array to store the size of each component

  public:
    // Constructor to initialize the disjoint set with a given number of nodes
    DisjointSet(int n) {
        parent.resize(n + 1); // Resize the parent array to hold n + 1 elements, as we are using 1-based indexing and 0 is not used
        size.resize(n + 1, 1); // Initialize the size array to 1

        for (int i = 0; i < n; i++) {
            // Each node is its own parent initially
            parent[i] = i; // Initialize each node's parent to itself
        }
    }

    // Function to find the ultimate-parent of a node with path compression
    int findUltimateParent(int node) {
        // If the node is its own parent, return the node
        if (parent[node] == node) {
            return node;
        }
        // Otherwise, recursively find the parent and perform path compression
        return parent[node] = findUltimateParent(parent[node]); // Path compression
    }

    // Function to join two components using union by size
    void unionBySize(int u, int v) {
        int parentU = findUltimateParent(u); // Find the ultimate parent of u
        int parentV = findUltimateParent(v); // Find the ultimate parent of v

        // If both nodes have the same parent, they are already in the same component
        if (parentU == parentV) {
            return;
        }

        // Union by size
        // Attach the smaller size tree under the root of the larger size tree
        // Compare the sizes of the two parents
        // Attach the smaller size tree under the root of the larger size tree
        if (size[parentU] < size[parentV]) {
            parent[parentU] = parentV; // Make parentV the parent of parentU
            size[parentV] = size[parentV] + size[parentU]; // Update the size of the new root
        } else {  // If size[parentU] >= size[parentV]
            parent[parentV] = parentU; // Make parentU the parent of parentV
            size[parentU] = size[parentU] + size[parentV]; // Update the size of the new root
        }
    }

    // Function to check if two nodes are in the same component
    bool isSameComponent(int u, int v) {
        return findUltimateParent(u) == findUltimateParent(v); // Check if the ultimate parents are the same
    }
};

// Class to implement Kruskal's Algorithm
class Kruskal {
  private:
    int V; // Number of vertices
    vector<pair<int, pair<int, int>>> edges; // Vector to store the edges of the graph {weight, {u, v}}

  public:
    // Constructor to initialize the graph with a given number of vertices
    Kruskal(int vertices) {
        V = vertices;
    }

    // Function to add an edge to the graph (undirected) along with its weight
    void addEdge(int u, int v, int weight) {
        edges.push_back({weight, {u, v}}); // Add edge to the edges vector
        edges.push_back({weight, {v, u}}); // Add the reverse edge to make it undirected
    }

    // Function to implement Kruskal's Algorithm to find the Minimum Spanning Tree (MST) and print minimum Sum and MST
    void kruskalAlgorithm() {
        // Sort the edges based on their weights in non-decreasing order
        sort(edges.begin(), edges.end());

        DisjointSet ds(V); // Create a disjoint set to manage the connected components

        vector<pair<int, int>> mst; // Vector to store the edges of the MST
        int minSum = 0; // Variable to store the minimum sum of edge weights

        for (auto edge : edges) {
            int weight = edge.first; // Edge weight
            int u = edge.second.first; // First vertex
            int v = edge.second.second; // Second vertex

            // Check if u and v are in the same component
            if (!ds.isSameComponent(u, v)) {
                ds.unionBySize(u, v); // Union the two components
                mst.push_back({u, v}); // Add the edge to the MST
                minSum += weight; // Add the weight to the minimum sum
            }
        }

        // Print the minimum sum of edge weights
        cout << "Minimum Sum: " << minSum << endl;

        // Print the edges of the MST
        cout << "Edges in MST:" << endl;
        for (auto edge : mst) {
            cout << edge.first << " - " << edge.second << endl;
        }
    }
};

int main() {
    int V = 5; // Number of vertices
    Kruskal kruskal(V); // Create a Kruskal object

    // Add edges to the graph (undirected) along with their weights
    kruskal.addEdge(0, 1, 2);
    kruskal.addEdge(0, 2, 1);
    kruskal.addEdge(1, 2, 1);
    kruskal.addEdge(2, 3, 2);
    kruskal.addEdge(3, 4, 1);
    kruskal.addEdge(4, 2, 2);

    // Call Kruskal's Algorithm to find the Minimum Spanning Tree (MST)
    kruskal.kruskalAlgorithm();

    return 0;
}

// Time Complexity:
// 1. Sorting the edges takes O(E log E), where E is the number of edges.
// 2. The union and find operations take O(log V) in the worst case, but with path compression, they become O(1) on average.
// 3. Therefore, the overall time complexity of Kruskal's Algorithm is O(E log E).

// Space Complexity:
// 1. The space complexity is O(V + E) for storing the edges and the disjoint set.
// 2. The disjoint set uses O(V) space for the parent and size arrays.
// 3. The edges vector uses O(E) space.
// 4. Therefore, the overall space complexity is O(V + E).