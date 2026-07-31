// DFS traversal of a graph (which may be disconnected).
// Notes Link : https://takeuforward.org/data-structure/depth-first-search-dfs/

// Like BFS, but we recurse (depth-first) instead of using a queue. Loop over all vertices so
// disconnected components are covered.

class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  dfs(node, visited, result) {
    visited[node] = true;
    result.push(node);

    for (const neighbor of this.adjList[node]) {
      if (!visited[neighbor]) {
        this.dfs(neighbor, visited, result);
      }
    }
  }

  dfsTraversal() {
    const visited = new Array(this.V).fill(false);
    const result = [];

    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) {
        this.dfs(i, visited, result);
      }
    }

    return result;
  }
}

// Driver code — three disconnected components
const g = new Graph(7);
g.addEdge(0, 1);
g.addEdge(0, 2);
g.addEdge(3, 4);
g.addEdge(5, 6);
console.log("DFS Traversal of the graph:", g.dfsTraversal().join(" ")); // 0 1 2 3 4 5 6

// Time: O(V + E). Space: O(V) for visited + recursion stack.
// BFS uses a queue and finds shortest paths in unweighted graphs; DFS uses recursion/stack and
// suits topological sort and cycle detection.
