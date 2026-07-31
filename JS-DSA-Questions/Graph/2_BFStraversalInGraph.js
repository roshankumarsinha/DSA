// BFS traversal of a graph (which may be disconnected).
// Notes link : https://takeuforward.org/graph/breadth-first-search-bfs-level-order-traversal/

// Approach:
// 1. Adjacency list representation.
// 2. A visited[] array of size V.
// 3. Loop over all vertices (to cover disconnected components); for each unvisited vertex, run BFS.
// 4. BFS with a queue: pop a node, visit it, enqueue its unvisited neighbors (marking them visited).

// JavaScript note: a plain array is used as the queue (push/shift). visited is an Array of booleans.
class Graph {
  constructor(vertices) {
    this.V = vertices;
    this.adjList = Array.from({ length: vertices }, () => []);
  }

  addEdge(u, v) {
    this.adjList[u].push(v);
    this.adjList[v].push(u);
  }

  bfs() {
    const visited = new Array(this.V).fill(false);
    const result = [];

    for (let i = 0; i < this.V; i++) {
      if (!visited[i]) {
        const q = [i];
        visited[i] = true;

        while (q.length > 0) {
          const node = q.shift();
          result.push(node);

          for (const neighbor of this.adjList[node]) {
            if (!visited[neighbor]) {
              q.push(neighbor);
              visited[neighbor] = true;
            }
          }
        }
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
console.log("BFS Traversal of the graph:", g.bfs().join(" ")); // 0 1 2 3 4 5 6

// Time: O(V + E). Space: O(V + E) for the graph + O(V) for visited/queue.
