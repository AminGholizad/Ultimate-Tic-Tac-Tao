#ifndef TTT_HPP
#define TTT_HPP
#pragma once
#include "game.hpp"
#include "move.hpp"
#include "player.hpp"
#include <algorithm>
#include <array>
#include <vector>

namespace Tic_Tac_Toe {

class State : public Game::State<State> {
  public:
    using Player = Game::Player;
    using Move = Game::Move;
    using Moves = std::vector<Move>;
    using Board = std::array<std::array<Player, 3>, 3>; // TODO: convert to linear

    constexpr State() = default;
    constexpr explicit State(Board board_, Player player_ = Game::PlayerX)
        : board(board_), player(player_) {
        if (auto checked_winner = do_compute_winner(player); checked_winner.is_none()) {
            winner = do_compute_winner(player.other_player());
        } else {
            winner = checked_winner;
        }
        set_valid_moves();
    }

    void do_debugValidMoves() const &;
    void do_debugBoard() const &;

    void do_updateState(const Move &move);
    void set_valid_moves();

    [[nodiscard]] State do_sim_move(const Move &move) const &;

    [[nodiscard]] int do_calc_score(int color, int depth) const & {
        (void)this; // TODO: add two in a rows as a score metric
        return color * depth;
    }
    [[nodiscard]] Game::Player do_compute_winner(const Game::Player &test_player) const &;

    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.board); }
    [[nodiscard]] decltype(auto) do_get_player(this auto &&self) { return (self.player); }
    [[nodiscard]] decltype(auto) do_get_winner(this auto &&self) { return (self.winner); }
    [[nodiscard]] decltype(auto) do_get_moves(this auto &&self) { return (self.valid_moves); }

    [[nodiscard]] constexpr bool do_is_over() const & { return !winner.is_none(); }
    [[nodiscard]] constexpr bool do_is_draw() const & { return winner.is_draw(); }

  private:
    Board board{};
    Move last_move{-1, -1};
    Player player{Player::Mark::X};
    Player winner{Player::Mark::None};
    Moves valid_moves{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
};
} // namespace Tic_Tac_Toe
#endif // !TTT_HPP
