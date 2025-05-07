// Write a function to find number of strongly connected components in a directed graph or print the strongly connected components in a directed graph.
// This algorithm is based on Kosaraju's algorithm.

// This is possible only if the graph is directed.

// What is a strongly connected component?
// A component is called a Strongly Connected Component(SCC) only if for every possible pair of vertices (u, v) inside that component,
// u is reachable from v and v is reachable from u.

// Notes link for Strongly Connected Components: https://takeuforward.org/graph/strongly-connected-components-kosarajus-algorithm-g-54/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
  private:
    // Function to perform DFS and fill the stack with nodes in finishing order
    // node: current node
    // vis: visited array
    // adj: adjacency list
    // st: stack to store the nodes in finishing order
    void dfs(int node, vector<int> &vis, vector<int> adj[], stack<int> &st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(it, vis, adj, st);
            }
        }

        st.push(node);
    }

    // Function to perform DFS for Transposed graph
    // node: current node
    // vis: visited array
    // adjT: transposed adjacency list
    void dfs3(int node, vector<int> &vis, vector<int> adjT[]) {
        vis[node] = 1;
        for (auto it : adjT[node]) {
            if (!vis[it]) {
                dfs3(it, vis, adjT);
            }
        }
    }


  public:
    //Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<int> adj[])
    {
        // Vector to keep track for visited nodes
        vector<int> vis(V, 0);

        // Stack to store the nodes in finishing order
        stack<int> st;

        // Step 1: Fill the stack with nodes in finishing order
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }

        // Step 2: Create the transposed graph
        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            vis[i] = 0;
            for (auto it : adj[i]) {
                // i -> it
                // it -> i
                adjT[it].push_back(i);
            }
        }

        // this variable will count the number of strongly connected components
        int scc = 0;

        // Step 3: Perform DFS on the transposed graph
        // while the stack is not empty
        // pop the top element from the stack
        // if the node is not visited
        // increment the count of strongly connected components
        while (!st.empty()) {
            int node = st.top();
            st.pop();
            if (!vis[node]) {
                scc++;
                dfs3(node, vis, adjT);
            }
        }
        return scc;
    }
};

int main() {

    int V = 5;
    int edges[5][2] = {
        {1, 0}, {0, 2},
        {2, 1}, {0, 3},
        {3, 4}
    };
    vector<int> adj[V];
    for (int i = 0; i < V; i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
    }
    Solution obj;
    int ans = obj.kosaraju(V, adj);
    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}

// Output:
// The number of strongly connected components is: 3