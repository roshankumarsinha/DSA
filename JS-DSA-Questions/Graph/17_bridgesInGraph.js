// Find Bridges (a.k.a. Critical Connections) in an undirected graph.
// A bridge is an edge whose removal increases the number of connected components.

// Notes link : https://takeuforward.org/plus/dsa/problems/bridges-in-graph

// Approach (DFS with discovery time and low-link):
// - tin[node]: the time (order) when node was first visited.
// - low[node]: the smallest tin reachable from node's subtree, excluding the direct parent edge.
// - After DFS returns from a child, edge (node, child) is a bridge if low[child] > tin[node]
//   (the child's subtree cannot reach node or any ancestor by another route).

// JavaScript note: C++ used a member `time`; here we keep a mutable counter in a closure/state.
class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
    this.tin = new Array(vertices).fill(0);
    this.low = new Array(vertices).fill(0);
    this.visited = new Array(vertices).fill(false);
    this.bridges = [];
    this.timer = 1;
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  dfs(node, parent) {
    this.visited[node] = true;
    this.tin[node] = this.low[node] = this.timer++;

    for (const neighbor of this.adjList[node]) {
      if (neighbor === parent) continue; // don't go back along the parent edge

      if (!this.visited[neighbor]) {
        this.dfs(neighbor, node);
        this.low[node] = Math.min(this.low[node], this.low[neighbor]);

        // Bridge condition
        if (this.low[neighbor] > this.tin[node]) {
          this.bridges.push([node, neighbor]);
        }
      } else {
        // Back edge: update low with the neighbor's discovery time
        this.low[node] = Math.min(this.low[node], this.tin[neighbor]);
      }
    }
  }

  findBridges() {
    for (let i = 0; i < this.V; i++) {
      if (!this.visited[i]) {
        this.dfs(i, -1);
      }
    }
  }

  printBridges() {
    console.log("Bridges in the graph:");
    for (const [a, b] of this.bridges) {
      console.log(`${a} - ${b}`);
    }
  }
}

const g = new Graph(5);
g.addEdge(0, 1);
g.addEdge(1, 2);
g.addEdge(0, 3);
g.addEdge(1, 3);
g.addEdge(3, 4);
g.findBridges();
g.printBridges();
// Bridges: 1 - 2, and 3 - 4

// Time: O(V + E). Space: O(V + E).
