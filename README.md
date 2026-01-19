# Console Games Collection
A collection of simple terminal-based games implemented in pure C using only standard libraries.

## Available Games

### 1. Minesweeper
Classic minesweeper game with grid-based gameplay.
- Navigate with WASD keys
- Place flags with 'f' key
- Reveal cells with Spacebar
- Quit with 'q'

### Compilation
```bash
make # Compile all games

clang -o bin/minesweeper src/minesweeper.c # Or compile specific game
```

```bash
./bin/<game>
```