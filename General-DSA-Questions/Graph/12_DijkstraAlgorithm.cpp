// Write a function to implement Dijkstra's Algorithm.

// Dijkstra's Algorithm is a greedy algorithm used to find the shortest path from a source node to all other nodes in a weighted graph.
// It works only for graphs with non-negative weights because :-
// 1. It assumes that once a node is visited, the shortest path to it has been found.
// 2. Dijkstra is greedy — it assumes once a node’s shortest distance is finalized, it cannot be improved.
// 3. But if negative weights exist, you might find a better (shorter) path after finalizing a node — breaking Dijkstra's assumption!

// Dijkstra algorithm can work with both directed and undirected graphs.

// Notes link : https://takeuforward.org/data-structure/di_vjkstras-algorithm-using-set-g-33/

// Approach:
// 1. We would be using a set and a distance array of size V (where ‘V’ are the number of nodes in the graph)
//    initialized with infinity (indicating that at present none of the nodes are reachable from the source node) and initialize the distance to source node as 0.
// 2. We push the source node to the set along with its distance which is also 0.
// 3. Now, we start erasing the elements from the set and look out for their adjacent nodes one by one.
//    If the current reachable distance is better than the previous distance indicated by the distance array, we update the distance and insert it in the set.
// 4. A node with a lower distance would be first erased from the set as opposed to a node with a higher distance.
//    By following step 3, until our set becomes empty, we would get the minimum distance from the source node to all other nodes. We can then return the distance array. 
// 5. The only difference between using a Priority Queue and a Set is that in a set we can check if there exists a pair with the same node but a greater distance than the
//    current inserted node as there will be no point in keeping that node into the set if we come across a much better value than that. So, we simply delete the element with a greater distance value for the same node.

// Intuition :
// The above problem implements a BFS kind of approach using the set data structure.
// The only thing that we need to take care of is that for all the paths possible between a pair of nodes, we need to store the path with the minimum cost between them.
// That is, say we have a node that has been reached by two paths, one with a cost of 7 and another with a cost of say 9.
// It is obvious that the path with a cost of 7 would be more optimal than the path with a cost of 9.
// A set data structure in C++ always stores the elements in increasing order i.e., when we erase from a set, the smallest valued elements get erased first.
// In C++, a set is a standard template library (STL) container that stores unique elements in a sorted order (by default, ascending). It's implemented as a balanced binary search tree (usually a Red-Black Tree).

// So, we can use this property of the set to implement Dijkstra's Algorithm.
// 6. We can also use a priority queue instead of a set to implement Dijkstra's Algorithm.
//    The only difference is that in a priority queue, we can only access the top element and not the rest of the elements.
//    So, we need to pop the top element and then push all its adjacent nodes into the priority queue.
//    The priority queue will always give us the node with the minimum distance first.


#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <climits> // For INT_MAX
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

    // Function to add an edge to the graph (directed) along with its weight
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight}); // Add edge from u to v with weight
        adjList[v].push_back({u, weight}); // Add edge from v to u with weight
    }

    // Function to perform Dijkstra's Algorithm using a set
    vector<int> dijkstra(int source) {
        vector<int> distance(V, INT_MAX); // Initialize distance array with a very large number
        set<pair<int, int>> s; // Set to store pairs of (distance, node)

        distance[source] = 0; // Distance from source to itself is 0
        s.insert({0, source}); // Start with the source node

        while (!s.empty()) {
            auto it = *(s.begin()); // Get the node with the minimum distance
            int nodeDistance = it.first; // Distance of the current node
            int node = it.second; // Current node
            s.erase(it); // Remove the current node from the set

            // Traverse all its neighbors
            for (auto neighbor : adjList[node]) {
                int edgeWeight = neighbor.second; // Weight of the edge
                int neighborNode = neighbor.first; // Neighbor node

                // If the current reachable distance is better than the previous distance
                if (nodeDistance + edgeWeight < distance[neighborNode]) {
                    // Update the distance and insert it in the set
                    if (distance[neighborNode] != INT_MAX) {
                        // Remove the old pair from the set if it exists and has a greater distance
                        // Prevents processing the same node multiple times with worse paths
                        s.erase({distance[neighborNode], neighborNode}); // Remove the old pair from the set
                    }
                    distance[neighborNode] = nodeDistance + edgeWeight; // Update the distance
                    s.insert({distance[neighborNode], neighborNode}); // Insert the new pair into the set
                }
            }
        }

        return distance; // Return the distance array
    }

    // Function to perform Dijkstra's Algorithm using a priority queue, this is more easy to implement than using a set
    vector<int> dijkstraUsingPQ(int source) {
        vector<int> distance(V, INT_MAX); // Initialize distance array with a very large number
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap priority queue

        distance[source] = 0; // Distance from source to itself is 0
        pq.push({0, source}); // Start with the source node

        while (!pq.empty()) {
            auto it = pq.top(); // Get the node with the minimum distance
            int nodeDistance = it.first; // Distance of the current node
            int node = it.second; // Current node
            pq.pop(); // Remove the current node from the priority queue

            // Traverse all its neighbors
            for (auto neighbor : adjList[node]) {
                int edgeWeight = neighbor.second; // Weight of the edge
                int neighborNode = neighbor.first; // Neighbor node

                // If the current reachable distance is better than the previous distance
                if (nodeDistance + edgeWeight < distance[neighborNode]) {
                    distance[neighborNode] = nodeDistance + edgeWeight; // Update the distance
                    pq.push({distance[neighborNode], neighborNode}); // Insert the new pair into the priority queue
                }
            }
        }

        return distance; // Return the distance array
    }
};

int main() {
    Graph g(3); // Create a graph with 3 vertices

    g.addEdge(0, 1, 2); // Add edge from 0 to 1 with weight 2
    g.addEdge(0, 2, 4); // Add edge from 0 to 2 with weight 4
    g.addEdge(1, 2, 1); // Add edge from 1 to 2 with weight 1

    vector<int> distances = g.dijkstra(0); // Find shortest paths from source node 0
    cout << "Shortest distances from source node 0:" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Distance to node " << i << ": " << distances[i] << endl; // Print the shortest distance to each node
    }
    return 0; // Return success
}

// Graph :
// (0)
//  |  \
// 2|   \4
//  |    \
// (1)-1-(2)

// Edges :
// 0 -> 1 (weight 2)
// 0 -> 2 (weight 4)
// 1 -> 2 (weight 1)

// Initial distance array : [0, INT_MAX, INT_MAX]
// In set we will push (0, 0) i.e. (distance, node)

// After first iteration :
// Erase (0, 0) from set
// Explore neighbors of 0
// 1. For neighbor 1 :
//    distance[1] = min(distance[1], 0 + 2) = min(INT_MAX, 2) = 2
//    So, we will push (2, 1) in the set
// 2. For neighbor 2 :
//    distance[2] = min(distance[2], 0 + 4) = min(INT_MAX, 4) = 4
//    So, we will push (4, 2) in the set
// Set now contains : (2, 1), (4, 2)
// Distance array : [0, 2, 4]

// After second iteration :
// Erase (2, 1) from set
// Explore neighbors of 1
// 1. For neighbor 0 :
//    distance[0] = min(distance[0], 2 + 2) = min(0, 4) = 0
// 2. For neighbor 2 :
//    distance[2] = min(distance[2], 2 + 1) = min(4, 3) = 3
//    So, we will push (3, 2) in the set
// Set now contains : (3, 2), (4, 2)
// Distance array : [0, 2, 3]

// After third iteration :
// Erase (3, 2) from set
// Explore neighbors of 2
// 1. For neighbor 0 :
//    distance[0] = min(distance[0], 3 + 4) = min(0, 7) = 0
// 2. For neighbor 1 :
//    distance[1] = min(distance[1], 3 + 1) = min(2, 4) = 2
// Set now contains : (4, 2)
// Distance array : [0, 2, 3]

// After fourth iteration :
// Erase (4, 2) from set
// Explore neighbors of 2
// 1. For neighbor 0 :
//    distance[0] = min(distance[0], 4 + 4) = min(0, 8) = 0
// 2. For neighbor 1 :
//    distance[1] = min(distance[1], 4 + 1) = min(2, 5) = 2
// Set now contains : empty
// Distance array : [0, 2, 3]


// Time Complexity : O(E * log(V)) where E is the number of edges and V is the number of vertices.
// Space Complexity : O(V) for the distance array and the set.
