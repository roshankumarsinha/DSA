// Write a function to implement Prim's Algorithm.

// Prim's Algorithm is used to find the Minimum Spanning Tree (MST) of a connected, undirected, weighted graph.

// What is a Minimum Spanning Tree (MST)?
// 1. First we need to understand what is Spanning Tree?
//    a. A spanning tree is a tree in which we have N nodes(i.e. All the nodes present in the original graph) and N-1 edges and all nodes are reachable from each other.
//    b. Understand the concept of Spanning Tree and Minimum Spanning Tree from this link: https://takeuforward.org/data-structure/minimum-spanning-tree-theory-g-44/
// 2. A Minimum Spanning Tree (MST) is a spanning tree with the minimum sum of edge weights.
// 3. In other words, it connects all vertices in the graph with the minimum total edge weight.

// Approach:
// In order to implement Prim’s algorithm, we will be requiring an array(visited array) and a priority queue that will essentially represent a min-heap.
// We need another array(MST) as well if we wish to store the edge information of the minimum spanning tree.

// Priority Queue(Min Heap): The priority queue will be storing the pairs (edge weight, node).
// We can start from any given node. Here we are going to start from node 0 and so we will initialize the priority queue with (0, 0).
// If we wish to store the mst of the graph, the priority queue should instead store the triplets (edge weight, node, parent node) and in that case, we will initialize with (0, 0, -1).

// Visited array: All the nodes will be initially marked as unvisited.

// sum variable: It will be initialized with 0 and we wish that it will store the sum of the edge weights finally.

// MST array(optional): If we wish to store the minimum spanning tree(MST) of the graph, we need this array. This will store the edge information as a pair of starting and ending nodes of a particular edge.

// Step 1 : We will first push edge weight 0, node value 0, and parent -1 as a triplet into the priority queue to start the algorithm.
// Note: We can start from any node of our choice. Here we have chosen node 0.

// Step 2 : Then the top-most element (element with minimum edge weight as it is the min-heap we are using) of the priority queue is popped out.

// Step 3 : After that, we will check whether the popped-out node is visited or not.
// If the node is visited: We will continue to the next element of the priority queue.
// If the node is not visited: We will mark the node visited in the visited array and add the edge weight to the sum variable.
// If we wish to store the mst, we should insert the parent node and the current node into the mst array as a pair in this step.

// Step 4 : Now, we will iterate on all the unvisited adjacent nodes of the current node and will store each of their information in the specified triplet format i.e. (edge weight, node value, and parent node) in the priority queue.

// Step 5 : We will repeat steps 2, 3, and 4 using a loop until the priority queue becomes empty.

// Step 6 : Finally, the sum variable should store the sum of all the edge weights of the minimum spanning tree.


// Note: Points to remember if we do not wish to store the mst(minimum spanning tree) for the graph and are only concerned about the sum of all the edge weights of the minimum spanning tree:
// 1. First of all, we will not use the triplet format instead, we will just use the pair in the format of (edge weight, node value). Basically, we do not need the parent node.
// 2. In step 3, we need not store anything in the mst array and we need not even use the mst array in our whole algorithm as well.


// Intuition:
// The intuition of this algorithm is the greedy technique used for every node.
// If we carefully observe, for every node, we are greedily selecting its unvisited adjacent node with the minimum edge weight(as the priority queue here is a min-heap and the topmost element is the node with the minimum edge weight).
// Doing so for every node, we can get the sum of all the edge weights of the minimum spanning tree and the spanning tree itself(if we wish to) as well.

// Notes link for Prim's Algorithm : https://takeuforward.org/data-structure/prims-algorithm-minimum-spanning-tree-c-and-java-g-45/


#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Graph {
  private:
    int V; // Number of vertices
    // The first element of the pair is the destination node and the second element is the weight of the edge
    vector<list<pair<int, int>>> adjList; // Adjacency list representation of the graph

  public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V); // Resize the adjacency list to hold V lists
    }

    // Function to add an edge to the graph (undirected) along with its weight
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight}); // Add edge from u to v with weight
        adjList[v].push_back({u, weight}); // Add edge from v to u with weight
    }

    // Function to perform Prim's Algorithm to find the Minimum Spanning Tree (MST) and print minimum Sum and MST
    void primsAlgorithm() {
        // Using a vector to keep track of visited nodes
        vector<bool> visited(V, false);

        // Priority queue to store {weight, node, parent}. Min-heap based on weight.
        // If we do not wish to store the mst, we can use a pair instead of a triplet.
        // Using a pair to store {weight, node}, something like: priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        // Start from node 0, with weight 0 and no parent (-1)
        pq.push({0, {0, -1}}); // {weight, {node, parent}}
        int sum = 0; // Variable to store the sum of edge weights

        // Vector to store the edges of the MST. {node, parent}
        // If we do not wish to store the mst, we can remove this vector.
        vector<pair<int, int>> mst;

        while (!pq.empty()) {
            // Get the top element from the priority queue
            auto top = pq.top();
            pq.pop();

            int weight = top.first; // Edge weight
            int node = top.second.first; // Current node
            int parent = top.second.second; // Parent node

            // If the node is already visited, continue to the next iteration
            if (visited[node]) {
                continue;
            }

            // If the node is not visited, we will mark it as visited
            // and add the edge weight to the sum
            // Mark the current node as visited
            visited[node] = true;

            // Add the edge weight to the sum
            sum += weight;

            // If we wish to store the mst, add the edge to the mst vector
            if (parent != -1) {
                mst.push_back({parent, node});
            }

            // Traverse all unvisited adjacent nodes and push them into the priority queue
            for (auto neighbor : adjList[node]) {
                // If the neighbor is not visited, push it into the priority queue
                if (!visited[neighbor.first]) {
                    pq.push({neighbor.second, {neighbor.first, node}}); // {weight, {node, parent}}
                }
            }
        }

        // Print the sum of edge weights of the minimum spanning tree
        cout << "Minimum Sum of the MST: " << sum << endl;
        // Print the edges of the minimum spanning tree
        cout << "Edges of the MST:" << endl;
        for (auto edge : mst) {
            cout << edge.first << " - " << edge.second << endl; // Print the edge
        }
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices

    // Add edges to the graph with weights
    g.addEdge(0, 1, 2); // Add edge from 0 to 1 with weight 2
    g.addEdge(0, 2, 1); // Add edge from 0 to 2 with weight 1
    g.addEdge(1, 2, 1); // Add edge from 1 to 2 with weight 1
    g.addEdge(2, 3, 2); // Add edge from 2 to 3 with weight 2
    g.addEdge(3, 4, 1); // Add edge from 3 to 4 with weight 1
    g.addEdge(4, 2, 2); // Add edge from 4 to 2 with weight 2

    g.primsAlgorithm(); // Perform Prim's Algorithm to find the MST

    return 0;
}

// Time Complexity:
// O(E log V), where E is the number of edges and V is the number of vertices.
// The log V factor comes from the priority queue operations.
// The overall complexity is dominated by the priority queue operations, which take O(log V) time for each edge.

// Space Complexity:
// O(V + E), where V is the number of vertices and E is the number of edges.
// The space complexity is due to the adjacency list representation of the graph and the priority queue.