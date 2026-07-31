// Prim's Algorithm — Minimum Spanning Tree (MST) of a connected, undirected, weighted graph.
// Notes link : https://takeuforward.org/data-structure/prims-algorithm-minimum-spanning-tree-c-and-java-g-45/

// An MST connects all V vertices with V-1 edges of minimum total weight.

// Approach (greedy + min-heap):
// 1. Push {weight:0, node:0, parent:-1}. Maintain a visited[] array and a running sum.
// 2. Pop the smallest-weight entry. Skip if the node is visited; else mark visited, add its weight
//    to sum, and record the edge (parent, node).
// 3. Push all unvisited neighbors with their edge weights. Repeat until the heap is empty.

// JavaScript note: C++ used a priority_queue of triplets. Here we include a MinHeap ordered by
// weight and store items as { weight, node, parent }.
class MinHeap {
  constructor() {
    this.a = [];
  }
  size() {
    return this.a.length;
  }
  push(item) {
    this.a.push(item);
    let i = this.a.length - 1;
    while (i > 0) {
      const p = Math.floor((i - 1) / 2);
      if (this.a[p].weight > this.a[i].weight) {
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
        if (l < n && this.a[l].weight < this.a[s].weight) s = l;
        if (r < n && this.a[r].weight < this.a[s].weight) s = r;
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
    this.adjList = Array.from({ length: vertices }, () => []); // [node, weight]
  }

  addEdge(u, v, weight) {
    this.adjList[u].push([v, weight]);
    this.adjList[v].push([u, weight]);
  }

  primsAlgorithm() {
    const visited = new Array(this.V).fill(false);
    const pq = new MinHeap();
    pq.push({ weight: 0, node: 0, parent: -1 });
    let sum = 0;
    const mst = [];

    while (pq.size() > 0) {
      const { weight, node, parent } = pq.pop();

      if (visited[node]) continue;

      visited[node] = true;
      sum += weight;
      if (parent !== -1) mst.push([parent, node]);

      for (const [nbr, w] of this.adjList[node]) {
        if (!visited[nbr]) {
          pq.push({ weight: w, node: nbr, parent: node });
        }
      }
    }

    console.log("Minimum Sum of the MST:", sum);
    console.log("Edges of the MST:");
    for (const [a, b] of mst) {
      console.log(`${a} - ${b}`);
    }
  }
}

const g = new Graph(5);
g.addEdge(0, 1, 2);
g.addEdge(0, 2, 1);
g.addEdge(1, 2, 1);
g.addEdge(2, 3, 2);
g.addEdge(3, 4, 1);
g.addEdge(4, 2, 2);
g.primsAlgorithm();

// Time: O(E log V). Space: O(V + E).
