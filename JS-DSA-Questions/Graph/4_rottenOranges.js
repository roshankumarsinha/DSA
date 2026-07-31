// Minimum time to rot all oranges in a grid.
// 0 = empty, 1 = fresh, 2 = rotten. A rotten orange rots its 4-directional fresh neighbors each
// minute. Return the minimum minutes to rot everything, or -1 if some fresh orange can't be reached.

// Approach: multi-source BFS.
// 1. Enqueue all initially rotten oranges; count fresh oranges.
// 2. BFS level by level (each level = 1 minute), rotting fresh neighbors.
// 3. If fresh oranges remain at the end, return -1; else return the elapsed time.

// JavaScript note: C++ used queue<pair<int,int>>. Here each queue item is a [row, col] array, and a
// plain array is the queue (push/shift).
function minTimeToRotAllOranges(grid) {
  const rows = grid.length;
  const cols = grid[0].length;
  const q = [];
  let freshCount = 0;

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === 2) q.push([i, j]);
      else if (grid[i][j] === 1) freshCount++;
    }
  }

  if (freshCount === 0) return 0;

  let time = 0;
  const directions = [
    [-1, 0],
    [1, 0],
    [0, -1],
    [0, 1],
  ];

  while (q.length > 0) {
    const size = q.length;
    let hasRotten = false;

    for (let i = 0; i < size; i++) {
      const [r, c] = q.shift();

      for (const [dr, dc] of directions) {
        const nr = r + dr;
        const nc = c + dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] === 1) {
          grid[nr][nc] = 2;
          q.push([nr, nc]);
          freshCount--;
          hasRotten = true;
        }
      }
    }

    if (hasRotten) time++;
  }

  return freshCount > 0 ? -1 : time;
}

const grid = [
  [2, 1, 0],
  [1, 1, 0],
  [0, 1, 2],
];
console.log("Minimum time to rot all oranges:", minTimeToRotAllOranges(grid)); // 2
