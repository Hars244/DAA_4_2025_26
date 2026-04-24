const rows = 20;
const cols = 40;

const grid = document.getElementById("grid");

let startNode = "10-5";
let endNode = "10-30";

let isMouseDown = false;
let drawMode = "add";

// Track mouse globally
document.addEventListener("mousedown", () => {
  isMouseDown = true;
});

document.addEventListener("mouseup", () => {
  isMouseDown = false;
});

// Create Grid
function createGrid() {
  for (let r = 0; r < rows; r++) {
    const row = document.createElement("div");
    row.className = "row";

    for (let c = 0; c < cols; c++) {
      const cell = document.createElement("div");
      cell.className = "cell";
      cell.id = `${r}-${c}`;

      // Start & End
      if (cell.id === startNode) cell.classList.add("start");
      if (cell.id === endNode) cell.classList.add("end");

      // Mouse Down (decide add/remove)
      cell.addEventListener("mousedown", () => {
        if (cell.classList.contains("start") || cell.classList.contains("end")) return;

        if (cell.classList.contains("wall")) {
          drawMode = "remove";
          cell.classList.remove("wall");
        } else {
          drawMode = "add";
          cell.classList.add("wall");
        }
      });

      // Drag
      cell.addEventListener("mouseenter", () => {
        if (!isMouseDown) return;

        if (cell.classList.contains("start") || cell.classList.contains("end")) return;

        if (drawMode === "add") {
          cell.classList.add("wall");
        } else {
          cell.classList.remove("wall");
        }
      });

      row.appendChild(cell);
    }

    grid.appendChild(row);
  }
}

createGrid();

// Get neighbors
function getNeighbors(id) {
  const [r, c] = id.split("-").map(Number);
  const neighbors = [];

  const directions = [
    [0, 1], [1, 0], [0, -1], [-1, 0]
  ];

  for (let [dr, dc] of directions) {
    let nr = r + dr;
    let nc = c + dc;

    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
      neighbors.push(`${nr}-${nc}`);
    }
  }

  return neighbors;
}

// BFS
async function startBFS() {
  let queue = [startNode];
  let visited = new Set();
  let parent = {};

  visited.add(startNode);

  while (queue.length > 0) {
    let current = queue.shift();

    if (current === endNode) {
      await drawPath(parent);
      return;
    }

    for (let neighbor of getNeighbors(current)) {
      const cell = document.getElementById(neighbor);

      if (!visited.has(neighbor) && !cell.classList.contains("wall")) {
        visited.add(neighbor);
        parent[neighbor] = current;
        queue.push(neighbor);

        if (!cell.classList.contains("end")) {
          cell.classList.add("visited");
        }

        await sleep(15);
      }
    }
  }
}

// Draw shortest path
async function drawPath(parent) {
  let current = endNode;

  while (current !== startNode) {
    current = parent[current];

    const cell = document.getElementById(current);

    if (!cell.classList.contains("start")) {
      cell.classList.remove("visited");
      cell.classList.add("path");
    }

    await sleep(25);
  }
}

// Sleep (animation)
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

// Reset
function resetGrid() {
  document.querySelectorAll(".cell").forEach(cell => {
    cell.classList.remove("visited", "path", "wall");
  });
}