# Console Games Collection
A collection of simple terminal-based games implemented in pure C using only standard libraries.

## Available Games

### 1. Minesweeper
<div align="center"> 
    <img src="assets/minesweeper.png" alt="minesweeper" width="200"/>
</div>
Classic minesweeper game with grid-based gameplay.
- Navigate with WASD keys
- Place flags with 'f' key
- Reveal cells with Spacebar
- Quit with 'q'

### 2. Tic Tac Toe
<div align="center"> 
    <img src="assets/tictactoe.png" alt="tictactoe" width="200"/>
</div>
Two-player Tic Tac Toe game.
- Navigate with WASD keys
- Place X or O with Spacebar
- Quit with 'q'

### 3. Match-3 Puzzle
<div align="center"> 
    <img src="assets/matchthree.png" alt="matchthree" width="200"/>
</div>
A simple match-3 puzzle game.
- Navigate with WASD keys
- Swap tiles with Spacebar + direction + Spacebar
- Quit with 'q'

### Compilation
```bash
make # Compile all games

clang -o bin/minesweeper src/minesweeper.c # Or compile specific game
```

```bash
./bin/<game>
```