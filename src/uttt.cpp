#include "uttt.hpp"
namespace UTTT {
void State::debugLargeboard() const & {
  std::cerr << "-------\n";
  for (const auto &row : largeboard) {
    std::cerr << "|";
    for (const auto &elem : row) {
      std::cerr << elem << "|";
    }
    std::cerr << "\n-------\n";
  }
  std::cerr << '\n';
}
void State::debugSubboard(const size_t &x, const size_t &y) const & {
  std::cerr << "-------\n";
  for (auto row = ZERO; row < THREE; ++row) {
    std::cerr << "|";
    for (auto col = ZERO; col < THREE; ++col) {
      std::cerr << board[row + x][col + y] << "|";
    }
    std::cerr << "\n-------\n";
  }
  std::cerr << '\n';
}
void State::debugBoard() const & {
  std::cerr << "-----------------------\n";
  for (auto i = ZERO; i < NINE; ++i) {
    if (i % THREE == ZERO) {
      std::cerr << "-----------------------\n";
    }
    std::cerr << "|";
    for (auto j = ZERO; j < NINE; ++j) {
      if (j % THREE == ZERO) {
        std::cerr << "|";
      }
      std::cerr << board[i][j] << "|";
    }
    std::cerr << "|\n-----------------------\n";
  }
  std::cerr << "-----------------------\n";
} // namespace UTTT
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
        player = player.otherPlayer();
        valid_moves.clear();
        return;
      }
    } while (!is_valid(move));
  }
  updateState(move);
  player = player.otherPlayer();
  set_valid_moves();
}

bool State::is_largeboard_full() const & {
  for (auto i = ZERO; i < THREE; ++i) {
    for (auto j = ZERO; j < THREE; ++j) {
      if (largeboard[i][j].isNone()) {
        return false;
      }
    }
  }
  return true;
}
State::Player State::compute_winner(const Player &p) const & {
  for (auto i = ZERO; i < THREE; ++i) {
    if (largeboard[i][0] == p && largeboard[i][1] == p &&
        largeboard[i][2] == p) {
      return p;
    }
    if (largeboard[0][i] == p && largeboard[1][i] == p &&
        largeboard[2][i] == p) {
      return p;
    }
  }
  if (largeboard[0][0] == p && largeboard[1][1] == p && largeboard[2][2] == p) {
    return p;
  }
  if (largeboard[0][2] == p && largeboard[1][1] == p && largeboard[2][0] == p) {
    return p;
  }
  if (is_largeboard_full()) {
    auto [MEsum, OPsum] = sub_win_count();
    return (MEsum > OPsum) ? player : player.otherPlayer();
  }
  return Player{Player::Mark::None};
} // namespace UTTT

void State::moveTo(const Move &move) {
  updateState(move);
  std::cerr << player << " Moved to ";
  std::cout << lastMove << '\n';
  player = player.otherPlayer();
}
State State::sim_move(const Move &move) const & {
  auto copy = *this;
  copy.updateState(move);
  copy.player = copy.player.otherPlayer();
  copy.set_valid_moves();
  return copy;
}
} // namespace UTTT
