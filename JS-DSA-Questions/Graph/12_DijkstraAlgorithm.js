// Dijkstra's Algorithm — shortest path from a source in a weighted graph with NON-NEGATIVE weights.
// Notes link : https://takeuforward.org/data-structure/di_vjkstras-algorithm-using-set-g-33/

// It's greedy: once a node's shortest distance is finalized, it can't improve — which fails with
// negative weights (use Bellman-Ford there). Works on directed and undirected graphs.

// Approach (min-heap / priority queue):
// 1. distance[] = Infinity; distance[source] = 0. Push {dist:0, node:source}.
// 2. Pop the smallest-distance node; relax its neighbors; push improved neighbors.
// 3. Skip stale entries (a popped distance greater than the recorded one).
// Time O(E log V), Space O(V).

// JavaScript note: C++ used std::set or priority_queue. JS has neither built in, so we include a
// small MinHeap keyed by distance. We handle stale entries by comparing on pop.
class MinHeap {
  constructor() {
    this.a = [];
  }
  size() {
    return this.a.length;
  }
  push(item) {
    // item = [dist, node]
    this.a.push(item);
    let i = this.a.length - 1;
    while (i > 0) {
      const p = Math.floor((i - 1) / 2);
      if (this.a[p][0] > this.a[i][0]) {
        [this.a[p], this.a[i]] = [this.a[i], this.a[p]];
        i = p;
      } else break;
    }
  }
  pop() {
    const top = this.a[0];
    const last = this.a.pop();
    if (this.a.length > 0) {
      this.a[0] = last;
      let i = 0;
      const n = this.a.length;
      while (true) {
        const l = 2 * i + 1;
        const r = 2 * i + 2;
        let s = i;
        if (l < n && this.a[l][0] < this.a[s][0]) s = l;
        if (r < n && this.a[r][0] < this.a[s][0]) s = r;
        if (s !== i) {
          [this.a[i], this.a[s]] = [this.a[s], this.a[i]];
          i = s;
        } else break;
      }
    }
    return top;
  }
}

class Graph {
  constructor(vertices) {
    this.V = vertices;
    // adjList[u] = array of [v, weight]
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v, weight) {
    this.adjList[u].push([v, weight]);
    this.adjList[v].push([u, weight]);
  }

  dijkstra(source) {
    const distance = new Array(this.V).fill(Infinity);
    const pq = new MinHeap();

    distance[source] = 0;
    pq.push([0, source]);

    while (pq.size() > 0) {
      const [nodeDistance, node] = pq.pop();

      // Skip stale entries
      if (nodeDistance > distance[node]) continue;

      for (const [neighborNode, edgeWeight] of this.adjList[node]) {
        if (nodeDistance + edgeWeight < distance[neighborNode]) {
          distance[neighborNode] = nodeDistance + edgeWeight;
          pq.push([distance[neighborNode], neighborNode]);
        }
      }
    }

    return distance;
  }
}

const g = new Graph(3);
g.addEdge(0, 1, 2);
g.addEdge(0, 2, 4);
g.addEdge(1, 2, 1);

const distances = g.dijkstra(0);
console.log("Shortest distances from source node 0:");
distances.forEach((d, i) => console.log(`Distance to node ${i}: ${d}`));
// Expected: [0, 2, 3]
