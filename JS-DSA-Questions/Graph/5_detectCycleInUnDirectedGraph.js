// Detect a cycle in an UNDIRECTED graph.
// Notes Link : https://takeuforward.org/data-structure/detect-cycle-in-an-undirected-graph-using-bfs/

// Key idea: in an undirected graph, every edge goes both ways, so seeing the PARENT again is
// expected. A cycle exists if we reach an already-visited node that is NOT the parent (a back edge).

// Approach (BFS):
// - Each queue item stores { node, parent }.
// - Start BFS from each unvisited vertex (graph may be disconnected).
// - For each neighbor: if unvisited → enqueue with current as parent; else if it's not the parent
//   → a cycle exists.

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  bfs(start, visited) {
    const q = [{ node: start, parent: -1 }];
    visited[start] = true;

    while (q.length > 0) {
      const { node, parent } = q.shift();

      for (const neighbor of this.adjList[node]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push({ node: neighbor, parent: node });
        } else if (neighbor !== parent) {
          return true; // cycle detected
        }
      }
    }

    return false;
  }

  hasCycle() {
    const visited = new Array(this.V).fill(false);
    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) {
        if (this.bfs(i, visited)) return true;
      }
    }
    return false;
  }
}

// Driver code
const g = new Graph(5);
g.addEdge(0, 1);
g.addEdge(1, 2);
g.addEdge(2, 0); // creates a cycle
g.addEdge(3, 4);
console.log(g.hasCycle() ? "Cycle detected in the graph." : "No cycle detected in the graph.");

// Can also be done with DFS: dfs(node, parent) — cycle if a visited neighbor isn't the parent.
