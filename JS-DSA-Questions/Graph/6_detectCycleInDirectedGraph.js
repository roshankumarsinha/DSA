// Detect a cycle in a DIRECTED graph.
// Notes Link : https://takeuforward.org/data-structure/detect-cycle-in-a-directed-graph-using-dfs-g-19/

// Key idea: a directed cycle exists if, during DFS, we revisit a node that is still in the CURRENT
// recursion path (pathVisited), not merely one that was visited earlier via a different path.

// Why both visited[] and pathVisited[]?
// - visited[]: has this node been explored at all?
// - pathVisited[]: is this node part of the current DFS path?
// A node can be visited via another path without forming a cycle; only revisiting a node on the
// active path means we looped back.

// Approach (DFS):
// - Mark node visited and pathVisited on entry.
// - For each neighbor: recurse if unvisited; if the neighbor is on the current path → cycle.
// - Unset pathVisited on exit (backtrack).

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  // Directed edge
  addEdge(u, v) {
    this.adjList[u].push(v);
  }

  dfs(node, visited, pathVisited) {
    visited[node] = true;
    pathVisited[node] = true;

    for (const neighbor of this.adjList[node]) {
      if (!visited[neighbor]) {
        if (this.dfs(neighbor, visited, pathVisited)) {
          return true; // propagate cycle detection upward
        }
      } else if (pathVisited[neighbor]) {
        return true; // neighbor is on the current path → cycle
      }
    }

    pathVisited[node] = false; // backtrack
    return false;
  }

  hasCycle() {
    const visited = new Array(this.V).fill(false);
    const pathVisited = new Array(this.V).fill(false);

    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) {
        if (this.dfs(i, visited, pathVisited)) return true;
      }
    }
    return false;
  }
}

// Driver code
const g = new Graph(4);
g.addEdge(0, 1);
g.addEdge(1, 2);
g.addEdge(2, 0); // creates a cycle
g.addEdge(2, 3);
console.log(g.hasCycle() ? "Cycle detected in the directed graph." : "No cycle detected in the directed graph.");
