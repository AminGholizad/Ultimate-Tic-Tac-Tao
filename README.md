# Ultimate-Tic-Tac-Tao
C++ code for playing UTTT against the AI algorithms

# Gameplay
You start the game as X if you like to be the O, you should type "-1 -1"
The game continues until one player wins.
## Rules
After the first player that can move anywhere on the board, every move depends on the previous move as follows:
1. The player should play in the mini board that is indicated by the last move
2. If the mini board is won or full the player can move in anywhere that is not marked before

# AI algorithm
A negamax algorithm has been implemented for the brain of the computer player.
Also the iterative deepening has been implemented for 1000ms of computation time limit with can be changed in the source code

# Todo

[] Start screen that will let you choose difficulty level

[] Make the board to show mini boards clearly

[] Make the board to show valid moves clearly

[] Implementing Montecarlo Tree Search algorithm as the AI
