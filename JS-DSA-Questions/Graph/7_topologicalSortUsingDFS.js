// Topological Sort using DFS.
// Notes link : https://takeuforward.org/data-structure/topological-sort-algorithm-dfs-g-21/

// Topological sort: a linear ordering of vertices such that for every directed edge u → v, u comes
// before v. Exists only for a Directed Acyclic Graph (DAG).

// Approach:
// 1. Run DFS.
// 2. After exploring ALL neighbors of a node (its dependencies), push it onto a stack.
// 3. Popping the stack yields the topological order.
// Intuition: a node is recorded only after everything it points to is handled, so reversing finish
// order gives a valid ordering.

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  // Directed edge
  addEdge(u, v) {
    this.adjList[u].push(v);
  }

  dfs(node, visited, stack) {
    visited[node] = true;
    for (const neighbor of this.adjList[node]) {
      if (!visited[neighbor]) {
        this.dfs(neighbor, visited, stack);
      }
    }
    stack.push(node); // add after all dependencies
  }

  topologicalSort() {
    const stack = [];
    const visited = new Array(this.V).fill(false);

    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) {
        this.dfs(i, visited, stack);
      }
    }

    // Pop to get topological order (reverse of finish order)
    return stack.reverse();
  }
}

const g = new Graph(6);
g.addEdge(5, 0);
g.addEdge(5, 2);
g.addEdge(4, 0);
g.addEdge(4, 1);
g.addEdge(2, 3);
g.addEdge(3, 1);
console.log("Topological Sort:", g.topologicalSort().join(" ")); // e.g. 5 4 2 3 1 0
