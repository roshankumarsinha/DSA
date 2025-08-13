// Write a function to implement Disjoint Sets.

// Why do we need Disjoint Sets data structure?
//    Assume we have given 2 components for undirrected graph :
//    1 -- 2 -- 3 -- 4

//      5 -- 6 -- 7
//    The question is whether node 1 and node 5 are in the same component or not.

// Approach we can take to solve this : Now, in order to solve this question we can use either the DFS or BFS traversal technique like if
//                                      we traverse the components of the graph we can find that node 1 and node 5 are not in the same component.
//                                      This is actually the brute force approach whose time complexity is O(N+E)(N = no. of nodes, E = no. of edges).
//                                      But using a Disjoint Set data structure we can solve this same problem in constant time.


// Approach:
// 1. We need parent array which will store the parent of each node.
// 2. We need rank array which will store the rank of each node. (If we are using union by rank)
// 3. We need size array which will store the size of each component. (If we are using union by size)
// 4. We need findParent function which will find the ultimate parent of a node.
// 5. We need union function which will join two components.
// 6. We will do path compression in the findParent function to make the tree flat which will make the findParent function faster and reduce the time complexity from O(logN) to O(1).

// You can read all the stuff from : https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/
// Watch video of TakeUForward.

// Union by size is more simple and clear to understand compared to union by rank.


#include <iostream>
#include <vector>
#include <list>
using namespace std;

class DisjointSet {
  private:
    vector<int> parent; // Parent array to store the parent of each node
    vector<int> rank; // Rank array to store the rank of each node
    vector<int> size; // Size array to store the size of each component

  public:
    // Constructor to initialize the disjoint set with a given number of nodes
    DisjointSet(int n) {
        parent.resize(n + 1); // Resize the parent array to hold n + 1 elements, as we are using 1-based indexing and 0 is not used
        rank.resize(n + 1, 0); // Initialize the rank array to 0
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
        // If we just return findParent(parent[node]), the tree will be deep and the time complexity will be O(logN).
        // By writing parent[node] = findParent(parent[node]), we are making the tree flat and reducing the time complexity to O(1).
    }

    // Function to join two components using union by rank
    void unionByRank(int u, int v) {
        int parentU = findUltimateParent(u); // Find the ultimate parent of u
        int parentV = findUltimateParent(v); // Find the ultimate parent of v

        // If both nodes have the same parent, they are already in the same component
        if (parentU == parentV) {
            return;
        }

        // Union by rank
        // Compare the ranks of the two parents
        // Attach the smaller rank tree under the root of the larger rank tree
        if (rank[parentU] < rank[parentV]) {
            parent[parentU] = parentV; // Make parentV the parent of parentU
        } else if (rank[parentU] > rank[parentV]) {
            parent[parentV] = parentU; // Make parentU the parent of parentV
        } else {  // If ranks are equal, make one as root and increment its rank
            parent[parentV] = parentU; // Make parentU the parent of parentV
            rank[parentU]++; // Increment the rank of the new root
        }
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

int main() {
    DisjointSet ds(7); // Create a disjoint set with 7 nodes

    // Perform union operations
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);

    // ds.unionBySize(1, 2);
    // ds.unionBySize(2, 3);
    // ds.unionBySize(4, 5);
    // ds.unionBySize(6, 7);

    // Check if two nodes are in the same component
    cout << "Are 1 and 3 in the same component? " << (ds.isSameComponent(1, 3) ? "Yes" : "No") << endl; // Yes
    cout << "Are 1 and 4 in the same component? " << (ds.isSameComponent(1, 4) ? "Yes" : "No") << endl; // No
    cout << "Are 5 and 6 in the same component? " << (ds.isSameComponent(5, 6) ? "Yes" : "No") << endl; // No

    ds.unionByRank(5, 6); // Union 5 and 6
    cout << "Are 5 and 6 in the same component after union? " << (ds.isSameComponent(5, 6) ? "Yes" : "No") << endl; // Yes

    return 0;
}

// Time Complexity:
// 1. The time complexity of the find function is O(logN) in the worst case, but with path compression, it becomes O(1) on average.
// So this is for Dynaminc Graph so for each query we can say O(1).
// 2. The time complexity of the union function is O(logN) in the worst case, but with union by rank or size, it becomes O(1) on average.
// So this is for Dynaminc Graph so for each query we can say O(1).
// 3. The overall time complexity for N union operations is O(N logN) in the worst case, but with path compression and union by rank or size, it becomes O(N) on average.
