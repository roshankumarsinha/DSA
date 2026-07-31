// Implement a Graph.
// Notes link : https://takeuforward.org/graph/graph-representation-in-c/

// Two representations:
// 1. Adjacency List : each vertex stores a list of its neighbors.
// 2. Adjacency Matrix : a V×V grid where cell (i, j) marks an edge between i and j.

// JavaScript note: C++ used vector<list<int>> / vector<vector<int>>. In JS, an array of arrays is
// the natural adjacency list, and Array.from({length: V}, () => new Array(V).fill(0)) builds the
// zero matrix.

// Adjacency List Representation
class AdjacencyListGraph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  // Undirected edge → add both directions
  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  printGraph() {
    for (let i = 0; i < this.V; i++) {
      console.log(`Vertex ${i}: ${this.adjList[i].join(" ")}`);
    }
  }
}

// Adjacency Matrix Representation
class AdjacencyMatrixGraph {
  constructor(vertices) {
    this.V = vertices;
    this.adjMatrix = Array.from({ length: vertices }, () => new Array(vertices).fill(0));
  }

  addEdge(u, v) {
    this.adjMatrix[u][v] = 1;
    this.adjMatrix[v][u] = 1;
  }

  printGraph() {
    for (let i = 0; i < this.V; i++) {
      console.log(this.adjMatrix[i].join(" "));
    }
  }
}

// Driver code
const listGraph = new AdjacencyListGraph(4);
listGraph.addEdge(0, 1);
listGraph.addEdge(0, 2);
listGraph.addEdge(1, 2);
listGraph.addEdge(2, 3);
console.log("Adjacency List Representation:");
listGraph.printGraph();

const matrixGraph = new AdjacencyMatrixGraph(4);
matrixGraph.addEdge(0, 1);
matrixGraph.addEdge(0, 2);
matrixGraph.addEdge(1, 2);
matrixGraph.addEdge(2, 3);
console.log("Adjacency Matrix Representation:");
matrixGraph.printGraph();

// Adjacency List: space O(V + E); great for sparse graphs; neighbor lookup O(degree).
// Adjacency Matrix: space O(V^2); O(1) edge existence check; wasteful for sparse graphs.
