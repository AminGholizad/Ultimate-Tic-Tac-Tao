#include "ttt.hpp"
#include <iostream>
namespace TTT {
void State::debugBoard() const & {
  if (lastMove != Move({-1, -1})) {
    std::cerr << player.otherPlayer() << " moved to (" << lastMove << ")\n";
  }
  std::cerr << "-------\n";
  for (const auto &row : board) {
    std::cerr << '|';
    for (const auto &elem : row) {
      std::cerr << elem << '|';
    }
    std::cerr << "\n-------\n";
  }
  std::cerr << '\n';
}
void State::debugValidMoves() const & {
  std::cerr << "Your valid moves are:\n";
  for (const auto &move : valid_moves) {
    std::cerr << '(' << move << ")\n";
  }
  std::cerr << '\n';
}
void State::userMove() {
  Move move;
  switch (1) {
  case 0:
    do {
      std::cerr << "Please enter a valid move\n";
      [[fallthrough]];
    case 1:
      std::cin >> move;
      std::cin.ignore();
      if (move == Move({-1, -1})) {
        return;
      }
    } while (!is_valid(move));
  }
  updateState(move);
  set_valid_moves();
}
void State::set_valid_moves() {
  valid_moves.clear();
  for (auto i = ZERO; i < THREE; ++i) {
    for (auto j = ZERO; j < THREE; ++j) {
      if (board[i][j].isNone()) {
        valid_moves.emplace_back(i, j);
      }
    }
  }
}
State::Player State::compute_winner(const Player &test_player) const & {
  for (auto i = ZERO; i < THREE; ++i) {
    if (board[i][0] == test_player && board[i][1] == test_player &&
        board[i][2] == test_player) {
      return test_player;
    }
    if (board[0][i] == test_player && board[1][i] == test_player &&
        board[2][i] == test_player) {
      return test_player;
    }
  }
  if (board[0][0] == test_player && board[1][1] == test_player &&
      board[2][2] == test_player) {
    return test_player;
  }
  if (board[0][2] == test_player && board[1][1] == test_player &&
      board[2][0] == test_player) {
    return test_player;
  }
  if (is_board_full()) {
    return Player{Player::Mark::Draw};
  }
  return Player{Player::Mark::None};
}
void State::updateState(const Move &move) {
  board[move.X()][move.Y()] = player;
  lastMove = move;
  winner = compute_winner(player);
  player = player.otherPlayer();
}
void State::moveTo(const Move &move) {
  updateState(move);
  std::cerr << player << " Moved to :";
  std::cout << lastMove << '\n';
}
State State::sim_move(const Move &move) const & {
  auto state_copy = *this;
  state_copy.updateState(move);
  state_copy.set_valid_moves();
  return state_copy;
}
} // namespace TTT
