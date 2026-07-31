// Kruskal's Algorithm — Minimum Spanning Tree (MST) of a connected, undirected, weighted graph.
// Notes link : https://takeuforward.org/data-structure/kruskals-algorithm-minimum-spanning-tree-g-47/

// Greedy: sort all edges by weight ascending, then add each edge to the MST if its two endpoints
// are in different components (checked/merged via Disjoint Set), skipping edges that would form a
// cycle. Stop once V-1 edges are chosen.

// Disjoint Set with path compression + union by size (see 15_DisjointSets.js).
class DisjointSet {
  constructor(n) {
    this.parent = new Array(n + 1);
    this.size = new Array(n + 1).fill(1);
    for (let i = 0; i <= n; i++) this.parent[i] = i;
  }

  findUltimateParent(node) {
    if (this.parent[node] === node) return node;
    this.parent[node] = this.findUltimateParent(this.parent[node]);
    return this.parent[node];
  }

  unionBySize(u, v) {
    const pu = this.findUltimateParent(u);
    const pv = this.findUltimateParent(v);
    if (pu === pv) return;
    if (this.size[pu] < this.size[pv]) {
      this.parent[pu] = pv;
      this.size[pv] += this.size[pu];
    } else {
      this.parent[pv] = pu;
      this.size[pu] += this.size[pv];
    }
  }

  isSameComponent(u, v) {
    return this.findUltimateParent(u) === this.findUltimateParent(v);
  }
}

class Kruskal {
  constructor(vertices) {
    this.V = vertices;
    this.edges = []; // each edge: [weight, u, v]
  }

  addEdge(u, v, weight) {
    this.edges.push([weight, u, v]);
  }

  kruskalAlgorithm() {
    // Sort edges by weight ascending
    this.edges.sort((a, b) => a[0] - b[0]);

    const ds = new DisjointSet(this.V);
    const mst = [];
    let minSum = 0;

    for (const [weight, u, v] of this.edges) {
      if (!ds.isSameComponent(u, v)) {
        ds.unionBySize(u, v);
        mst.push([u, v]);
        minSum += weight;
      }
    }

    console.log("Minimum Sum:", minSum);
    console.log("Edges in MST:");
    for (const [a, b] of mst) {
      console.log(`${a} - ${b}`);
    }
  }
}

const kruskal = new Kruskal(5);
kruskal.addEdge(0, 1, 2);
kruskal.addEdge(0, 2, 1);
kruskal.addEdge(1, 2, 1);
kruskal.addEdge(2, 3, 2);
kruskal.addEdge(3, 4, 1);
kruskal.addEdge(4, 2, 2);
kruskal.kruskalAlgorithm();

// Time: O(E log E) (sorting dominates). Space: O(V + E).
