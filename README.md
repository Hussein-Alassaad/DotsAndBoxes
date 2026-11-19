# Dots and Boxes

CMPS 270 Software Construction course project (Fall 2026/27): a console Dots and Boxes game in C.

- **Sprint 1:** two-player game (Players A and B) on a 4x5 grid of boxes
- **Sprint 2:** hard-level bot
- **Sprint 3 (bonus):** network play and multithreading

The game runs on Alpine Linux in a VM and starts automatically at boot.

## Build and run

```sh
make            # builds ./dotsandboxes
make run        # builds and starts the game
make valgrind   # runs the game under Valgrind (leak check)
make gdb        # opens the game in GDB
make clean
```

## How to play

The board has 5 rows (0-4) and 6 columns (0-5) of dots, forming 4x5 boxes.
On your turn, type the row and column of two neighbouring dots, for example:

```
0 0 0 1     # horizontal line from dot (0,0) to dot (0,1)
2 3 3 3     # vertical line from dot (2,3) to dot (3,3)
```

If your line completes a box, your letter (A or B) goes in it and you play again.
The game ends when all 20 boxes are claimed; the player with the most boxes wins.

## Code layout

| File | Responsibility |
|---|---|
| `board.h/.c` | Grid state (lines and box owners), move validation, box completion |
| `game.h/.c` | Players, turns, scores, end of game and winner |
| `display.h/.c` | Printing the board, scores, prompts and messages |
| `input.h/.c` | Reading and parsing the player's input safely |
| `main.c` | Game loop |
| `Makefile` | Build, run, Valgrind and GDB targets |

## Complexity

Checking whether a move completes a box is **O(1)**: a line touches at most two boxes,

Testing, GDB, Valgrind and the boot setup are documented in [DEBUGGING.md](DEBUGGING.md).
and each box is checked by looking at its four sides.
