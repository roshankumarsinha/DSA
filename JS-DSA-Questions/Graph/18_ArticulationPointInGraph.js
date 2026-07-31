// Find Articulation Points in an undirected graph.
// An articulation point is a vertex whose removal increases the number of connected components.

// Intuition:
// 1. A root of the DFS tree is an articulation point if it has more than one DFS child.
// 2. A non-root node u is an articulation point if it has a child v with low[v] >= tin[u]
//    (the child's subtree can't reach an ancestor of u without going through u).
// Note: when computing low from an already-visited neighbor, use its discovery time (tin), and
// never go back to the direct parent.

// Notes link : https://takeuforward.org/data-structure/articulation-point-in-graph-g-56/

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
    this.tin = new Array(vertices).fill(-1);
    this.low = new Array(vertices).fill(-1);
    this.visited = new Array(vertices).fill(false);
    this.isArticulationPoint = new Array(vertices).fill(false);
    this.timer = 1;
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  dfs(node, parent) {
    this.visited[node] = true;
    this.tin[node] = this.low[node] = this.timer++;
    let children = 0;

    for (const neighbor of this.adjList[node]) {
      if (neighbor === parent) continue;

      if (!this.visited[neighbor]) {
        this.dfs(neighbor, node);
        this.low[node] = Math.min(this.low[node], this.low[neighbor]);

        // Non-root articulation condition
        if (this.low[neighbor] >= this.tin[node] && parent !== -1) {
          this.isArticulationPoint[node] = true;
        }
        children++;
      } else {
        this.low[node] = Math.min(this.low[node], this.tin[neighbor]);
      }
    }

    // Root with more than one DFS child
    if (parent === -1 && children > 1) {
      this.isArticulationPoint[node] = true;
    }
  }

  findArticulationPoints() {
    for (let i = 0; i < this.V; i++) {
      if (!this.visited[i]) {
        this.dfs(i, -1);
      }
    }
  }

  printArticulationPoints() {
    const points = [];
    for (let i = 0; i < this.V; i++) {
      if (this.isArticulationPoint[i]) points.push(i);
    }
    console.log("Articulation Points in the graph:", points.join(" "));
  }
}

const g = new Graph(5);
g.addEdge(0, 1);
g.addEdge(1, 4);
g.addEdge(2, 3);
g.addEdge(3, 4);
g.addEdge(2, 4);
g.findArticulationPoints();
g.printArticulationPoints(); // 1 4

// Time: O(V + E). Space: O(V + E).
