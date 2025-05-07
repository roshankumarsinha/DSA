// Write a function to find Articulation Points in a graph.

// Articulation Points of a graph are the nodes on whose removal, the graph breaks into multiple components. 

// Example :
// 0 --- 1 --- 2
//       |
//       3
//
// Articulation Points:
// - 1 → removing disconnects node 2 and 3

// Intiution:
// 1. If node is a root node and has more than one child, it is an articulation point.
// 2. If node is not a root node and has a child such that no back edge exists from the child to any of the ancestors of the node, it is an articulation point.
//    a. Child should point to an ancestor of parent and not to the parent itself to qualify as a back edge.
// 3. If the child is not a root node and has a back edge to any of the ancestors of the node, it is not an articulation point.

// Notes link for Articulation Points in Graph: https://takeuforward.org/data-structure/articulation-point-in-graph-g-56/


#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
  private:
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list representation of the graph
    vector<int> timer; // Timer to keep track of the time of insertion
    vector<int> low; // Lowest time of insertion for each node
    vector<bool> visited; // Visited array to keep track of visited nodes
    vector<bool> isArticulationPoint; // Array to mark articulation points
    int time; // Timer variable to keep track of the time of insertion

  public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V); // Resize the adjacency list to hold V lists
        timer.resize(V, -1); // Initialize timer array to -1
        low.resize(V, -1); // Initialize low array to -1
        visited.resize(V, false); // Initialize visited array to false
        isArticulationPoint.resize(V, false); // Initialize articulation point array to false
        time = 1; // Initialize time variable
    }

    // Function to add an edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
        adjList[v].push_back(u); // Add edge from v to u (undirected graph)
    }

    // Function to perform DFS and find articulation points
    void dfs(int node, int parent) {
        visited[node] = true; // Mark the current node as visited
        timer[node] = low[node] = time; // Set the time of insertion and lowest time of insertion
        time++; // Increment the timer for the next node

        // Initialize the number of children
        // This is used to check if the node is a root node with more than one child
        // If the node is a root node and has more than one child, it is an articulation point
        int children = 0;

        // Traverse all its neighbors
        for (int neighbor : adjList[node]) {
            if (neighbor == parent) { // If the neighbor is the parent, continue to the next neighbor
                continue;
            }
            if (!visited[neighbor]) { // If the neighbor is not visited
                dfs(neighbor, node); // Recursively call DFS on the neighbor
                low[node] = min(low[node], low[neighbor]); // Update the lowest time of insertion for the current node

                // Check if the edge is an articulation point
                if (low[neighbor] >= timer[node] && parent != -1) {
                    isArticulationPoint[node] = true; // Mark the node as an articulation point
                }
                children++; // Increment the number of children
            } else { // If the neighbor is already visited
                low[node] = min(low[node], timer[neighbor]); // Update the lowest time of insertion
            }
        }

        // If node is a root node and has more than one child, it is an articulation point
        if (parent == -1 && children > 1) {
            isArticulationPoint[node] = true; // Mark the root node as an articulation point
        }
    }

    // Function to find all articulation points in the graph
    void findArticulationPoints() {
        // Call DFS for each component of the graph
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                dfs(i, -1); // Start DFS from this vertex with parent -1
            }
        }
    }

    // Function to print the articulation points
    void printArticulationPoints() {
        cout << "Articulation Points in the graph:" << endl;
        for (int i = 0; i < V; i++) {
            if (isArticulationPoint[i]) { // If the node is an articulation point
                cout << i << " "; // Print the articulation point
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices
    g.addEdge(0, 1); // Add edges to the graph
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 4);

    g.findArticulationPoints(); // Find articulation points in the graph
    g.printArticulationPoints(); // Print the articulation points

    return 0;
}

// Output:
// Articulation Points in the graph:
// 1 4

// Graph representation for the above example:
// 0---1--4
//      / |
//     2--3