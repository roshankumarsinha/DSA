// Disjoint Set Union (DSU / Union-Find).

// Why? To answer "are these two nodes in the same component?" in ~O(1), instead of O(N+E) with
// BFS/DFS each time. Essential for Kruskal's MST and dynamic connectivity.
// Notes: https://takeuforward.org/data-structure/disjoint-set-union-by-rank-union-by-size-path-compression-g-46/

// Components:
// - parent[]: each node's parent (a node is its own parent initially).
// - rank[] / size[]: heuristics to keep trees shallow when merging.
// - findUltimateParent: with PATH COMPRESSION, flattening the tree → ~O(1) amortized.
// - union by rank / size: attach the smaller tree under the larger.

// JavaScript note: this uses 1-based indexing like the C++ version (arrays sized n+1).
class DisjointSet {
  constructor(n) {
    this.parent = new Array(n + 1);
    this.rank = new Array(n + 1).fill(0);
    this.size = new Array(n + 1).fill(1);
    for (let i = 0; i <= n; i++) {
      this.parent[i] = i; // each node is its own parent
    }
  }

  // Find with path compression
  findUltimateParent(node) {
    if (this.parent[node] === node) return node;
    // Compress: point the node directly at the root
    this.parent[node] = this.findUltimateParent(this.parent[node]);
    return this.parent[node];
  }

  unionByRank(u, v) {
    const pu = this.findUltimateParent(u);
    const pv = this.findUltimateParent(v);
    if (pu === pv) return;

    if (this.rank[pu] < this.rank[pv]) {
      this.parent[pu] = pv;
    } else if (this.rank[pu] > this.rank[pv]) {
      this.parent[pv] = pu;
    } else {
      this.parent[pv] = pu;
      this.rank[pu]++;
    }
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

// Driver code
const ds = new DisjointSet(7);
ds.unionByRank(1, 2);
ds.unionByRank(2, 3);
ds.unionByRank(4, 5);
ds.unionByRank(6, 7);

console.log("Are 1 and 3 in the same component?", ds.isSameComponent(1, 3) ? "Yes" : "No"); // Yes
console.log("Are 1 and 4 in the same component?", ds.isSameComponent(1, 4) ? "Yes" : "No"); // No
console.log("Are 5 and 6 in the same component?", ds.isSameComponent(5, 6) ? "Yes" : "No"); // No

ds.unionByRank(5, 6);
console.log("Are 5 and 6 in the same component after union?", ds.isSameComponent(5, 6) ? "Yes" : "No"); // Yes
