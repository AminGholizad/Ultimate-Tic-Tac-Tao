#ifndef TTT_HPP
#define TTT_HPP
#pragma once
#include "game.hpp"
#include "move.hpp"
#include "player.hpp"
#include <algorithm>
#include <array>
#include <vector>

namespace TTT {

class Tic_Tac_Toe : public Game::State<Tic_Tac_Toe> {
  public:
    using Player = Game::Player;
    using Move = Game::Move;
    using Moves = std::vector<Move>;
    using Board = std::array<std::array<Player, 3>, 3>; // TODO: convert to linear

    constexpr Tic_Tac_Toe() = default;
    constexpr explicit Tic_Tac_Toe(Board board_, Move move_ = {-1, -1},
                                   Player player_ = Player{Player::Mark::X})
        : board(board_), last_move(move_), player(player_) {}

    void do_debugValidMoves() const &;
    void do_debugBoard() const &;

    void do_updateState(const Move &move);
    void do_set_valid_moves();

    [[nodiscard]] Tic_Tac_Toe do_sim_move(const Move &move) const &;

    [[nodiscard]] int do_calc_score(int color, int depth) const & {
        return color * depth * static_cast<int>(last_move.X());
    }
    [[nodiscard]] Game::Player do_compute_winner(const Game::Player &test_player) const &;

    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.board); }
    [[nodiscard]] decltype(auto) do_get_last_move(this auto &&self) { return (self.last_move); }
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
    Moves valid_moves{};
};
} // namespace TTT
#endif // !TTT_HPP
