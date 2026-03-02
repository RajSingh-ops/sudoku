let currentPuzzle = [];

async function createPuzzle() {

    const res = await fetch("/generate", { method: "POST" });
    const data = await res.json();

    currentPuzzle = data.puzzle;
    renderGrid(currentPuzzle);
    document.getElementById("result").innerText = "";
}

function renderGrid(puzzle) {

    const grid = document.getElementById("grid");
    grid.innerHTML = "";

    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {

            const cell = document.createElement("div");
            cell.classList.add("cell");

            if ((j + 1) % 3 === 0 && j !== 8)
                cell.classList.add("thick-right");

            if ((i + 1) % 3 === 0 && i !== 8)
                cell.classList.add("thick-bottom");

            const input = document.createElement("input");

            if (puzzle[i][j] !== ".") {
                input.value = puzzle[i][j];
                input.disabled = true;
            } else {
                input.maxLength = 1;
            }

            cell.appendChild(input);
            grid.appendChild(cell);
        }
    }
}

function getUserBoard() {

    const inputs = document.querySelectorAll("#grid input");
    let board = [];
    let index = 0;

    for (let i = 0; i < 9; i++) {
        let row = [];
        for (let j = 0; j < 9; j++) {
            const value = inputs[index].value;
            row.push(value === "" ? "." : value);
            index++;
        }
        board.push(row);
    }

    return board;
}

async function submitPuzzle() {

    const board = getUserBoard();

    const res = await fetch("/submit", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            puzzle: currentPuzzle,
            board: board
        })
    });

    const data = await res.json();

    if (data.status === "correct") {
        document.getElementById("result").innerText = "Correct";
    } else {
        document.getElementById("result").innerText = "Incorrect";
        renderGrid(data.solution);
    }
}

async function showSolution() {

    const res = await fetch("/solve", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            puzzle: currentPuzzle
        })
    });

    const data = await res.json();
    renderGrid(data.solution);
}