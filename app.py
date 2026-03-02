from fastapi import FastAPI
from fastapi.staticfiles import StaticFiles
from fastapi.responses import FileResponse
from pydantic import BaseModel
import subprocess

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"), name="static")

@app.get("/")
def root():
    return FileResponse("static/index.html")


class SudokuData(BaseModel):
    puzzle: list[list[str]]
    board: list[list[str]] | None = None


@app.post("/generate")
def generate():
    result = subprocess.run(
        ["game.exe"],
        capture_output=True,
        text=True
    )

    puzzle = [row.split() for row in result.stdout.strip().split("\n")]
    return {"puzzle": puzzle}


@app.post("/submit")
def submit(data: SudokuData):

    input_data = "\n".join(" ".join(r) for r in data.puzzle)

    solve_result = subprocess.run(
        ["solve.exe"],
        input=input_data,
        capture_output=True,
        text=True
    )

    solution = [row.split() for row in solve_result.stdout.strip().split("\n")]

    if data.board == solution:
        return {"status": "correct"}
    else:
        return {"status": "incorrect", "solution": solution}


@app.post("/solve")
def solve(data: SudokuData):

    input_data = "\n".join(" ".join(r) for r in data.puzzle)

    solve_result = subprocess.run(
        ["solve.exe"],
        input=input_data,
        capture_output=True,
        text=True
    )

    solution = [row.split() for row in solve_result.stdout.strip().split("\n")]

    return {"solution": solution}