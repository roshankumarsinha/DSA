// Shortest path from a source in a Directed Acyclic Graph (DAG) with weighted edges.
// Notes link : https://takeuforward.org/data-structure/shortest-path-in-directed-acyclic-graph-topological-sort-g-27/

// Approach:
// 1. Compute a topological order (DFS + stack).
// 2. Relax edges in topological order. Because every node comes AFTER its dependencies in this
//    order, distances to dependencies are finalized before we use them → single O(V+E) pass.
// 3. Unreachable nodes remain Infinity (reported as -1).

// Only works on DAGs. For general graphs use Dijkstra (non-negative) or Bellman-Ford (negative).

class Graph {
  constructor(vertices) {
    this.V = vertices;
    // adjList[u] = array of [v, weight]
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v, weight) {
    this.adjList[u].push([v, weight]);
  }

  dfs(node, visited, topoStack) {
    visited[node] = true;
    for (const [nbr] of this.adjList[node]) {
      if (!visited[nbr]) {
        this.dfs(nbr, visited, topoStack);
      }
    }
    topoStack.push(node);
  }

  shortestPath(source) {
    const visited = new Array(this.V).fill(false);
    const topoStack = [];

    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) this.dfs(i, visited, topoStack);
    }

    const distance = new Array(this.V).fill(Infinity);
    distance[source] = 0;

    // Process in topological order (pop from the stack)
    while (topoStack.length > 0) {
      const node = topoStack.pop();
      if (distance[node] !== Infinity) {
        for (const [nbr, weight] of this.adjList[node]) {
          if (distance[node] + weight < distance[nbr]) {
            distance[nbr] = distance[node] + weight;
          }
        }
      }
    }

    return distance.map((d) => (d === Infinity ? -1 : d));
  }
}

const g = new Graph(6);
g.addEdge(0, 1, 2);
g.addEdge(0, 4, 1);
g.addEdge(1, 2, 3);
g.addEdge(4, 2, 2);
g.addEdge(2, 3, 6);
g.addEdge(4, 5, 4);
g.addEdge(5, 3, 1);

const distances = g.shortestPath(0);
console.log("Shortest distances from source node 0:");
distances.forEach((d, i) => console.log(`Distance to node ${i}: ${d}`));
// Expected: [0, 2, 3, 6, 1, 5]
