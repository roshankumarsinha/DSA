// Count the Strongly Connected Components (SCCs) in a DIRECTED graph — Kosaraju's Algorithm.
// An SCC is a maximal set of vertices where every vertex is reachable from every other.

// Notes link : https://takeuforward.org/graph/strongly-connected-components-kosarajus-algorithm-g-54/

// Kosaraju's 3 steps:
// 1. DFS the original graph, pushing each node onto a stack in order of finishing time.
// 2. Transpose the graph (reverse every edge).
// 3. Pop nodes from the stack; each unvisited node starts a DFS on the transposed graph that
//    reveals one full SCC. Count them.

// JavaScript note: adjacency lists are arrays of arrays; a plain array is the stack; a Set/boolean
// array tracks visited nodes.
class Solution {
  dfs(node, vis, adj, st) {
    vis[node] = true;
    for (const it of adj[node]) {
      if (!vis[it]) this.dfs(it, vis, adj, st);
    }
    st.push(node); // push on finish
  }

  dfsOnTranspose(node, vis, adjT) {
    vis[node] = true;
    for (const it of adjT[node]) {
      if (!vis[it]) this.dfsOnTranspose(it, vis, adjT);
    }
  }

  kosaraju(V, adj) {
    const vis = new Array(V).fill(false);
    const st = [];

    // Step 1: finishing-order stack
    for (let i = 0; i < V; i++) {
      if (!vis[i]) this.dfs(i, vis, adj, st);
    }

    // Step 2: transpose the graph
    const adjT = Array.from({ length: V }, () => []);
    for (let i = 0; i < V; i++) {
      vis[i] = false; // reset for step 3
      for (const it of adj[i]) {
        adjT[it].push(i); // reverse edge i -> it becomes it -> i
      }
    }

    // Step 3: DFS on the transposed graph in reverse finishing order
    let scc = 0;
    while (st.length > 0) {
      const node = st.pop();
      if (!vis[node]) {
        scc++;
        this.dfsOnTranspose(node, vis, adjT);
      }
    }

    return scc;
  }
}

// Build the graph
const V = 5;
const edges = [
  [1, 0],
  [0, 2],
  [2, 1],
  [0, 3],
  [3, 4],
];
const adj = Array.from({ length: V }, () => []);
for (const [u, v] of edges) {
  adj[u].push(v);
}

const obj = new Solution();
console.log("The number of strongly connected components is:", obj.kosaraju(V, adj)); // 3
