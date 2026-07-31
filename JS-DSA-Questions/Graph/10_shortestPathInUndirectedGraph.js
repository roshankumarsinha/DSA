// Shortest path from a source to all nodes in an UNDIRECTED graph with UNIT edge weights.
// Notes link : https://takeuforward.org/data-structure/shortest-path-in-undirected-graph-with-unit-distance-g-28/

// Approach (BFS): since all edges have weight 1, BFS explores nodes in increasing distance order,
// so the first time we reach a node is its shortest distance.
// 1. distance[] initialized to Infinity; distance[source] = 0.
// 2. BFS: for each neighbor, if distance[node] + 1 < distance[neighbor], update and enqueue.
// 3. Replace still-Infinity entries with -1 (unreachable).

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  shortestPath(source) {
    const distance = new Array(this.V).fill(Infinity);
    const q = [source];
    distance[source] = 0;

    while (q.length > 0) {
      const node = q.shift();
      for (const neighbor of this.adjList[node]) {
        if (distance[node] + 1 < distance[neighbor]) {
          distance[neighbor] = distance[node] + 1;
          q.push(neighbor);
        }
      }
    }

    // Mark unreachable nodes as -1
    return distance.map((d) => (d === Infinity ? -1 : d));
  }
}

const g = new Graph(9);
g.addEdge(0, 1);
g.addEdge(0, 3);
g.addEdge(3, 4);
g.addEdge(4, 5);
g.addEdge(5, 6);
g.addEdge(1, 2);
g.addEdge(2, 6);
g.addEdge(6, 7);
g.addEdge(7, 8);
g.addEdge(6, 8);

const distances = g.shortestPath(0);
console.log("Shortest distances from source 0:");
distances.forEach((d, i) => console.log(`Distance to node ${i}: ${d}`));
