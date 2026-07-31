// Detect a cycle in a directed graph using BFS (Kahn's Algorithm).

// Idea: Kahn's Algorithm produces a topological order only for a DAG. If the number of vertices we
// manage to process (in-degree reaching 0) is LESS than V, some vertices are stuck in a cycle →
// the graph is cyclic.

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
  }

  // Returns true if the graph has a cycle
  hasCycle() {
    const inDegree = new Array(this.V).fill(0);
    let count = 0;

    for (let i = 0; i < this.V; i++) {
      for (const neighbor of this.adjList[i]) {
        inDegree[neighbor]++;
      }
    }

    const q = [];
    for (let i = 0; i < this.V; i++) {
      if (inDegree[i] === 0) q.push(i);
    }

    while (q.length > 0) {
      const node = q.shift();
      count++;

      for (const neighbor of this.adjList[node]) {
        inDegree[neighbor]--;
        if (inDegree[neighbor] === 0) q.push(neighbor);
      }
    }

    return count !== this.V; // couldn't process all → cycle
  }
}

// Acyclic example
const g = new Graph(6);
g.addEdge(5, 0);
g.addEdge(5, 2);
g.addEdge(4, 0);
g.addEdge(4, 1);
g.addEdge(2, 3);
g.addEdge(3, 1);
console.log(g.hasCycle() ? "Graph is cyclic" : "Graph is acyclic"); // acyclic

// Cyclic example
const g2 = new Graph(4);
g2.addEdge(0, 1);
g2.addEdge(1, 2);
g2.addEdge(2, 0); // cycle
g2.addEdge(2, 3);
console.log(g2.hasCycle() ? "Graph is cyclic" : "Graph is acyclic"); // cyclic
