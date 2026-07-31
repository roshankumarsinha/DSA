// Topological Sort using BFS — Kahn's Algorithm.
// Notes link : https://takeuforward.org/data-structure/kahns-algorithm-topological-sort-algorithm-bfs-g-22/

// Approach:
// 1. Compute the in-degree of each vertex.
// 2. Enqueue all vertices with in-degree 0 (no prerequisites).
// 3. Repeatedly: pop a vertex, add it to the order, and decrement the in-degree of its neighbors;
//    enqueue any neighbor whose in-degree drops to 0.
// 4. If the order contains all vertices, it's valid (otherwise a cycle exists).

// Intuition: remove dependency-free nodes layer by layer, unlocking dependents as you go.
// Time O(V + E), Space O(V).

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
  }

  topologicalSort() {
    const inDegree = new Array(this.V).fill(0);
    const topoOrder = [];

    // Compute in-degrees
    for (let i = 0; i < this.V; i++) {
      for (const neighbor of this.adjList[i]) {
        inDegree[neighbor]++;
      }
    }

    // Enqueue all in-degree-0 vertices
    const q = [];
    for (let i = 0; i < this.V; i++) {
      if (inDegree[i] === 0) q.push(i);
    }

    while (q.length > 0) {
      const node = q.shift();
      topoOrder.push(node);

      for (const neighbor of this.adjList[node]) {
        inDegree[neighbor]--;
        if (inDegree[neighbor] === 0) q.push(neighbor);
      }
    }

    return topoOrder;
  }
}

const g = new Graph(6);
g.addEdge(5, 0);
g.addEdge(5, 2);
g.addEdge(4, 0);
g.addEdge(4, 1);
g.addEdge(2, 3);
g.addEdge(3, 1);
console.log("Topological Sort:", g.topologicalSort().join(" ")); // e.g. 4 5 2 0 3 1
