# Ultimate-Tic-Tac-Tao
C++ code for playing UTTT against the AI algorithms

## Gameplay
You start the game as X if you like to be the O, you should type "-1 -1"
The game continues until one player wins.
### Rules
After the first player that can move anywhere on the board, every move depends on the previous move as follows:
1. The player should play in the mini board that is indicated by the last move
2. If the mini board is won or full the player can move in anywhere that is not marked before

## AI algorithms
Negamax algorithm and Monte carlo tree search



**Note**:
After cloning run this to pull libraries
```sh
git submodule init
git submodule update --remote
```
