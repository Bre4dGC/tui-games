# Console Games Collection
A collection of simple terminal-based games implemented in pure C using only standard libraries.

## Available Games

### 1. Minesweeper

<img src="assets/minesweeper.png" alt="minesweeper" width="200"/>

Classic minesweeper game with grid-based gameplay.
- Navigate with WASD keys
- Place flags with 'f' key
- Reveal cells with Spacebar
- Quit with 'q'

### 2. Tic Tac Toe

<img src="assets/tictactoe.png" alt="tictactoe" width="200"/>

Two-player Tic Tac Toe game.
- Navigate with WASD keys
- Place X or O with Spacebar
- Quit with 'q'

### 3. Match-3 Puzzle

<img src="assets/matchthree.png" alt="matchthree" width="200"/>

A simple match-3 puzzle game.
- Navigate with WASD keys
- Swap tiles with Spacebar + direction + Spacebar
- Quit with 'q'

### 4. Snake

<img src="assets/snake.png" alt="snake" width="200"/>

Snake game.
- Navigate with WASD keys
- Quit with 'q'

### Compilation
```bash
make # Compile all games

clang -o bin/minesweeper src/minesweeper.c # Or compile specific game
```

```bash
./bin/<game>
```