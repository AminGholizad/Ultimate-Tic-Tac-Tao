#ifndef UTTT_HPP
#define UTTT_HPP
#pragma once
#include "move.hpp"
#include "player.hpp"
#include <algorithm>
#include <utility>
#include <vector>

namespace UTTT {
static constexpr auto ZERO = 0ULL;
static constexpr auto THREE = 3ULL;
static constexpr auto NINE = 9ULL;
class State {
public:
  using Player = Game::Player;
  using Move = Game::Move;
  using Board9x9 =
      std::array<std::array<Player, NINE>, NINE>; // TODO: make this linear
  using Board3x3 =
      std::array<std::array<Player, THREE>, THREE>; // TODO: make this linear
  constexpr State() = default;
  constexpr State(Board9x9 board_, Board3x3 largeboard_)
      : board(board_), largeboard(largeboard_) {}

  [[nodiscard]] friend constexpr bool operator==(const State &lhs,
                                                 const State &rhs) {
    if (lhs.player != rhs.player) {
      return false;
    }
    if (lhs.lastMove != rhs.lastMove) {
      return false;
    }
    for (auto i = ZERO; i < NINE; ++i) {
      for (auto j = ZERO; j < NINE; ++j) {
        if (lhs.board[i][j] != rhs.board[i][j]) {
          return false;
        }
      }
    }
    for (auto i = ZERO; i < THREE; ++i) {
      for (auto j = ZERO; j < THREE; ++j) {
        if (lhs.largeboard[i][j] != rhs.largeboard[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  [[nodiscard]] friend constexpr bool operator!=(const State &lhs,
                                                 const State &rhs) {
    return !(lhs == rhs);
  }

  void debugLargeboard() const &;
  void debugSubboard(size_t const &x, size_t const &y) const &;
  void debugBoard() const &;
  void debugValidMoves() const &;

  [[nodiscard]] constexpr Player getWinner() const & { return winner; }
  [[nodiscard]] constexpr Player getPlayer() const & { return player; }
  [[nodiscard]] constexpr Move getMove() const & { return lastMove; }
  [[nodiscard]] constexpr auto get_moves() const & { return valid_moves; }
  [[nodiscard]] constexpr bool isOver() const & { return !winner.isNone(); }
  [[nodiscard]] constexpr bool isDraw() const & { return winner.isDraw(); }

  constexpr void bring_to_first(const Move &move) {
    const auto iter = std::ranges::find(valid_moves, move);
    std::rotate(valid_moves.begin(), iter, iter + 1);
  }
  [[nodiscard]] constexpr std::pair<int, int> sub_win_count() const & {
    int MEsum = 0;
    int OPsum = 0;
    for (auto i = ZERO; i < THREE; ++i) {
      for (auto j = ZERO; j < THREE; ++j) {
        if (largeboard[i][j] == player) {
          ++MEsum;
        } else if (largeboard[i][j] == player.otherPlayer()) {
          ++OPsum;
        }
      }
    }
    return std::make_pair(MEsum, OPsum);
  }

  void userMove();
  constexpr void set_valid_moves() {
    if (valid_moves.empty()) {
      init_valid_moves();
    } else {
      update_valid_moves();
    }
  }
  constexpr void init_valid_moves() {
    for (auto i = ZERO; i < NINE; ++i) {
      for (auto j = ZERO; j < NINE; ++j) {
        valid_moves.emplace_back(i, j);
      }
    }
  }
  constexpr void update_valid_moves() {
    valid_moves.clear();
    const auto [large_x, large_y] = lastMove % THREE;
    const size_t sub_x = large_x * THREE;
    const size_t sub_y = large_y * THREE;
    if (largeboard[large_x][large_y].isNone()) {
      for (auto i = ZERO; i < THREE; ++i) {
        for (auto j = ZERO; j < THREE; ++j) {
          if (board[i + sub_x][j + sub_y].isNone()) {
            valid_moves.emplace_back(i + sub_x, j + sub_y);
          }
        }
      }
    } else {
      for (auto i = ZERO; i < NINE; ++i) {
        for (auto j = ZERO; j < NINE; ++j) {
          if (board[i][j].isNone()) {
            valid_moves.emplace_back(i, j);
          }
        }
      }
    }
  }
  [[nodiscard]] State sim_move(const Move &move) const &;
  void moveTo(const Move &move);
  [[nodiscard]] constexpr auto game_over() const & {
    return std::make_tuple(valid_moves.empty(), winner == player,
                           winner == player.otherPlayer());
  }

private:
  Board9x9 board{Player{Player::Mark::None}};
  Board3x3 largeboard{Player{Player::Mark::None}};
  Move lastMove{-1, -1};
  Player player{Player::Mark::X};
  Player winner{Player::Mark::None};
  std::vector<Move> valid_moves;

  [[nodiscard]] Player compute_winner(Player const &player) const &;
  [[nodiscard]] bool is_largeboard_full() const &;
  [[nodiscard]] constexpr bool is_sub_winner(const size_t &x, const size_t &y,
                                             const Player &player_) const & {
    for (auto i = ZERO; i < THREE; ++i) {
      if (board[i + x][y] == player_ && board[i + x][1 + y] == player_ &&
          board[i + x][2 + y] == player_) {
        return true;
      }
      if (board[x][i + y] == player_ && board[1 + x][i + y] == player_ &&
          board[2 + x][i + y] == player_) {
        return true;
      }
    }
    if (board[x][y] == player_ && board[1 + x][1 + y] == player_ &&
        board[2 + x][2 + y] == player_) {
      return true;
    }
    if (board[x][2 + y] == player_ && board[1 + x][1 + y] == player_ &&
        board[2 + x][y] == player_) {
      return true;
    }
    return false;
  }
  [[nodiscard]] constexpr bool is_sub_full(const size_t &x,
                                           const size_t &y) const & {
    for (auto i = x; i < x + 3; ++i) {
      for (auto j = y; j < y + 3; ++j) {
        if (board[i][j].isNone()) {
          return false;
        }
      }
    }
    return true;
  }
  constexpr void fill_sub(const size_t &x, const size_t &y,
                          Player const &player_) {
    for (auto i = x; i < x + 3; ++i) {
      for (auto j = y; j < y + 3; ++j) {
        board[i][j] = player_;
      }
    }
  }

  constexpr void updateState(Move const &move) {
    board[move.X()][move.Y()] = player;
    lastMove = move;
    const auto [large_x, large_y] = move / 3;
    const auto sub_x = large_x * 3;
    const auto sub_y = large_y * 3;
    if (is_sub_winner(sub_x, sub_y, player)) {
      largeboard[large_x][large_y] = player;
      fill_sub(sub_x, sub_y, player);
      winner = compute_winner(player);
    } else if (is_sub_full(sub_x, sub_y)) {
      largeboard[large_x][large_y] = Player(Player::Mark::Draw);
      fill_sub(sub_x, sub_y, Player(Player::Mark::Draw));
      winner = compute_winner(player);
    }
  }

  [[nodiscard]] constexpr bool is_valid(Move const &move) const & {
    return std::ranges::find(valid_moves, move) != valid_moves.end();
  }
};
} // namespace UTTT

#endif // !UTTT_HPP
