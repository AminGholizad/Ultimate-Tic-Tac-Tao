#ifndef TTT_HPP
#define TTT_HPP
#pragma once
#include "move.hpp"
#include "player.hpp"
#include <algorithm>
#include <array>
#include <vector>

namespace TTT {
class State {
  public:
    using Player = Game::Player;
    using Move = Game::Move;
    static constexpr size_t ZERO = 0ULL;
    static constexpr size_t THREE = 3ULL;
    using Board3x3 = std::array<std::array<Player, THREE>, THREE>; // TODO: convert to linear
    constexpr State() = default;
    constexpr State(Board3x3 board_, Move move_, Player player_)
        : board(board_), lastMove(move_), player(player_) {}

    [[nodiscard]] friend constexpr bool operator==(const State &lhs, const State &rhs) {
        if (lhs.player != rhs.player) {
            return false;
        }
        if (lhs.lastMove != rhs.lastMove) {
            return false;
        }
        for (auto i = ZERO; i < THREE; ++i) {
            for (auto j = ZERO; j < THREE; ++j) {
                if (lhs.board[i][j] != rhs.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    [[nodiscard]] friend constexpr bool operator!=(const State &lhs, const State &rhs) {
        if (lhs.player == rhs.player) {
            return false;
        }
        if (lhs.lastMove == rhs.lastMove) {
            return false;
        }
        for (auto i = ZERO; i < THREE; ++i) {
            for (auto j = ZERO; j < THREE; ++j) {
                if (lhs.board[i][j] == rhs.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void debugBoard() const &;
    void debugValidMoves() const &;

    [[nodiscard]] constexpr Player getWinner() const & { return winner; }
    [[nodiscard]] constexpr Player getPlayer() const & { return player; }
    [[nodiscard]] constexpr Move getMove() const & { return lastMove; }
    [[nodiscard]] constexpr auto get_moves() const & { return valid_moves; }
    [[nodiscard]] constexpr bool isOver() const & { return !winner.isNone(); }
    [[nodiscard]] constexpr bool isDraw() const & { return winner.isDraw(); }

    constexpr void bring_to_first(Move const &move) {
        auto iter = std::ranges::find(valid_moves, move);
        std::rotate(valid_moves.begin(), iter, iter + 1);
    }

    void userMove();
    void set_valid_moves();
    [[nodiscard]] State sim_move(Move const &move) const &;
    void moveTo(Move const &move);
    [[nodiscard]] constexpr auto game_over() const & {
        return std::make_tuple(winner.isDraw(), winner == player, winner == player.otherPlayer());
    }

  private:
    Board3x3 board{Player{Player::Mark::None}};
    Move lastMove{-1, -1};
    Player player{Player::Mark::X};
    Player winner{Player::Mark::None};
    std::vector<Move> valid_moves;

    [[nodiscard]] Player compute_winner(const Player &test_player) const &;
    [[nodiscard]] constexpr bool is_board_full() const & {
        for (auto i = ZERO; i < THREE; ++i) {
            for (auto j = ZERO; j < THREE; ++j) {
                if (board[i][j].isNone()) {
                    return false;
                }
            }
        }
        return true;
    }
    [[nodiscard]] constexpr bool is_valid(Move const &move) const & {
        return std::ranges::find(valid_moves, move) != valid_moves.end();
    }
    void updateState(Move const &move);
};
} // namespace TTT
#endif // !TTT_HPP
