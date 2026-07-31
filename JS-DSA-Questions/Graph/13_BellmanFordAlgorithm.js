// Bellman-Ford Algorithm — shortest paths from a source, allowing NEGATIVE edge weights, and it
// can also detect negative cycles. Works for directed and undirected graphs.
// Notes link : https://takeuforward.org/data-structure/bellman-ford-algorithm-g-41/

// Approach:
// 1. distance[] = Infinity; distance[source] = 0.
// 2. Relax ALL edges V-1 times: for edge (u, v, w), if distance[u] + w < distance[v], update.
// 3. One more pass: if any edge can still be relaxed, a negative cycle exists.

// JavaScript note: edges are given as [u, v, w] triples; Infinity replaces INT_MAX. We guard
// against Infinity + w to avoid relaxing from unreachable nodes.
function bellmanFord(V, edges, S) {
  const distance = new Array(V).fill(Infinity);
  distance[S] = 0;

  // Relax all edges V-1 times
  for (let i = 0; i < V - 1; i++) {
    for (const [u, v, w] of edges) {
      if (distance[u] !== Infinity && distance[u] + w < distance[v]) {
        distance[v] = distance[u] + w;
      }
    }
  }

  // Negative cycle check
  for (const [u, v, w] of edges) {
    if (distance[u] !== Infinity && distance[u] + w < distance[v]) {
      return new Array(V).fill(-1); // negative cycle detected
    }
  }

  return distance;
}

const V = 6;
const edges = [
  [3, 2, 6],
  [5, 3, 1],
  [0, 1, 5],
  [1, 5, -3],
  [1, 2, -2],
  [3, 4, -2],
  [2, 4, 3],
];
const S = 0;

const distances = bellmanFord(V, edges, S);
console.log(`Shortest distances from source node ${S}:`);
distances.forEach((d, i) => console.log(`Distance to node ${i}: ${d}`));

// Time: O(V * E). Space: O(V).
