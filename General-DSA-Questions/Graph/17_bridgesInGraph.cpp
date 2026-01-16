// Write a function to detect Bridges(also called critical Connections) in a graph.

// 🔍 What is a Bridge?
// A bridge in an undirected graph is an edge that, if removed, increases the number of connected components of the graph.
// In simpler terms:  It’s a critical edge — removing it breaks the graph into two or more disconnected parts.

// Example:
// Consider the following graph:
// 0 --- 1 --- 2
//       |
//       3

// Bridge edges:  
// - (1, 2) → removing disconnects node 2  
// - (1, 3) → removing disconnects node 3

// Notes link for Bridges in Graph: https://takeuforward.org/plus/dsa/problems/bridges-in-graph
// watch video of TakeUForward.


// Steps to solve the problem:
// In order to find all the bridges of a graph, we will implement some logic over the DFS algorithm.
// This is more of an algorithm-based approach. So, let’s discuss the algorithm in detail. Before that, we will discuss two important concepts of the algorithm i.e.time of insertion and lowest time of insertion.
//    1.  Time of insertion: During the DFS call, the time when a node is visited, is called its time of insertion. For example, if in the above graph, we start DFS from node 0 it will visit node 0 first then node 1, node 2, and so on.
//        So, the time of insertion for node 0 will be 1, node 1 will be 2, node 2 will be 3 and it will continue like this. To store the time of insertion for each node, we will use a time array.
//    2.  Lowest time of insertion: In this case, the current node refers to all its adjacent nodes "except the parent" and takes the minimum lowest time of insertion into account. To store this entity for each node, we will use another ‘low’ array.

// The logical modification of the DFS algorithm is discussed below:
// After the DFS for any adjacent node gets completed, we will just check if the edge, whose starting point is the current node and ending point is that adjacent node, is a bridge.
// For that, we will just check if any other path from the current node to the adjacent node exists if we remove that particular edge. If any other alternative path exists, this edge is not a bridge. Otherwise, it can be considered a valid bridge. 

// Approach: The algorithm steps are as follows:-

// 1. we need to create the adjacency list for the given graph from the edge information(If not already given). And we will declare a variable timer(either globally or we can carry it while calling DFS), that will keep track of the time of insertion for each node.
// 2. Then we will start DFS from node 0(assuming the graph contains a single component otherwise, we will call DFS for every component) with parent -1.
//    a.  Inside DFS, we will first mark the node visited and then store the time of insertion and the lowest time of insertion properly. The timer may be initialized to 0 or 1.
//    b.  Now, it’s time to visit the adjacent nodes. 
//      b1. If the adjacent node is the parent itself, we will just continue to the next node.
//      b2. If the adjacent node is not visited, we will call DFS for the adjacent node with the current node as the parent.
//      b3. After the DFS gets completed, we will compare the lowest time of insertion of the current node and the adjacent node and take the minimum one.
//      b4. Now, we will check if the lowest time of insertion of the adjacent node is greater than the time of insertion of the current node.
//      b5. If it is, then we will store the adjacent node and the current node in our answer array as they are representing the bridge.
//      b6. If the adjacent node is already visited, we will just compare the lowest time of insertion of the current node and the adjacent node and take the minimum one.
// 3. Finally, our answer array will store all the bridges.

// Note: We are not considering the parent’s insertion time during calculating the lowest insertion time as we want to check if any other path from the node to the parent exists excluding the edge we intend to remove.

// Watch the video from "Take U Forward"


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
    vector<pair<int, int>> bridges; // Vector to store the bridges
    int time; // Timer variable to keep track of the time of insertion
  public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V); // Resize the adjacency list to hold V lists
        timer.resize(V, 0); // Initialize timer array to 0
        low.resize(V, 0); // Initialize low array to 0
        visited.resize(V, false); // Initialize visited array to false
        time = 1; // Initialize time variable
    }

    // Function to add an edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Add edge from u to v
        adjList[v].push_back(u); // Add edge from v to u (undirected graph)
    }

    // Function to perform DFS and find bridges
    void dfs(int node, int parent) {
        visited[node] = true; // Mark the current node as visited
        timer[node] = low[node] = time; // Set the time of insertion and lowest time of insertion
        time++; // Increment the timer for the next node

        // Traverse all its neighbors
        for (int neighbor : adjList[node]) {
            // If neighbor is parent, continue to the next neighbor because we don't want to go back to the parent
            // You add an undirected edge between nodes u and v. In the adjacency list, both will appear:
            // When DFS goes from u to v, and then from v to u again, it would mistakenly think there's a back edge or a cycle — unless we tell DFS to ignore the immediate parent.
            if (neighbor == parent) { // If the neighbor is the parent, continue to the next neighbor
                continue;
            }
            if (!visited[neighbor]) { // If the neighbor is not visited
                dfs(neighbor, node); // Recursively call DFS on the neighbor

                // After DFS, update the lowest time of insertion for the current node
                low[node] = min(low[node], low[neighbor]);

                // Check if the edge is a bridge
                if (low[neighbor] > timer[node]) {
                    bridges.push_back({node, neighbor}); // Store the bridge
                }
            } else { // If the neighbor is already visited
                low[node] = min(low[node], timer[neighbor]); // Update the lowest time of insertion
            }
        }
    }

    // Function to find all bridges in the graph
    void findBridges() {
        // Call DFS for each component of the graph
        for (int i = 0; i < V; i++) {
            if (!visited[i]) { // If the vertex is not visited
                dfs(i, -1); // Start DFS from this vertex with parent -1
            }
        }
    }

    // Function to print the bridges
    void printBridges() {
        cout << "Bridges in the graph:" << endl;
        for (auto bridge : bridges) {
            cout << bridge.first << " - " << bridge.second << endl; // Print the bridge
        }
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    // Add edges to the graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    // Find bridges in the graph
    g.findBridges();

    // Print the bridges
    g.printBridges();

    return 0;
}

// Graph representation:
// 0 ----- 1 ----- 2
//  \     /
//    \ /
//     3 ----- 4
// The bridges in this graph are:
// 1 - 2
// 3 - 4

// Time Complexity:
// The time complexity of this algorithm is O(V + E), where V is the number of vertices and E is the number of edges in the graph.
// This is because we are performing a DFS traversal of the graph, which takes O(V + E) time.
// The DFS visits each vertex once and explores each edge once.

// Space Complexity:
// The space complexity of this algorithm is O(V + E) as well.
// This is due to the adjacency list representation of the graph and the additional space used for the visited, timer, low, and bridges arrays.
// The adjacency list takes O(V + E) space, and the other arrays take O(V) space.
// Therefore, the overall space complexity is O(V + E).

