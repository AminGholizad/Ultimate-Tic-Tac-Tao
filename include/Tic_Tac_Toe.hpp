#ifndef TTT_HPP
#define TTT_HPP
#pragma once
#include "game.hpp"
#include "move.hpp"
#include "player.hpp"
#include <array>
#include <optional>
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
        int MEsum{0};
        int OPsum{0};
        for (size_t i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1]) {
                MEsum += (board[i][0] == player) ? 1 : 0;
                OPsum += (board[i][0] == player.other_player()) ? 1 : 0;
            }
            if (board[i][1] == board[i][2]) {
                MEsum += (board[i][1] == player) ? 1 : 0;
                OPsum += (board[i][1] == player.other_player()) ? 1 : 0;
            }
            if (board[0][i] == board[1][i]) {
                MEsum += (board[0][i] == player) ? 1 : 0;
                OPsum += (board[0][i] == player.other_player()) ? 1 : 0;
            }
            if (board[1][i] == board[2][i]) {
                MEsum += (board[1][i] == player) ? 1 : 0;
                OPsum += (board[1][i] == player.other_player()) ? 1 : 0;
            }
        }
        if (board[0][0] == board[1][1]) {
            MEsum += (board[0][0] == player) ? 1 : 0;
            OPsum += (board[0][0] == player.other_player()) ? 1 : 0;
        }
        if (board[1][1] == board[2][2]) {
            MEsum += (board[1][1] == player) ? 1 : 0;
            OPsum += (board[1][1] == player.other_player()) ? 1 : 0;
        }

        if (board[0][2] == board[1][1]) {
            MEsum += (board[0][2] == player) ? 1 : 0;
            OPsum += (board[0][2] == player.other_player()) ? 1 : 0;
        }
        if (board[1][1] == board[2][0]) {
            MEsum += (board[1][1] == player) ? 1 : 0;
            OPsum += (board[1][1] == player.other_player()) ? 1 : 0;
        }
        return color * depth * (MEsum - OPsum);
    }
    [[nodiscard]] Game::Player do_compute_winner(const Game::Player &test_player) const &;

    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.board); }
    [[nodiscard]] decltype(auto) do_get_player(this auto &&self) { return (self.player); }
    [[nodiscard]] decltype(auto) do_get_winner(this auto &&self) { return (self.winner); }
    [[nodiscard]] decltype(auto) do_get_moves(this auto &&self) { return (self.valid_moves); }

    [[nodiscard]] constexpr bool do_is_over() const & { return !winner.is_none(); }
    [[nodiscard]] constexpr bool do_is_first_move() const & { return !last_move; }
    [[nodiscard]] constexpr bool do_is_draw() const & { return winner.is_draw(); }

  private:
    Board board{};
    std::optional<Move> last_move{}; // NOLINT(readability-redundant-member-init)
    Player player{Player::Mark::X};
    Player winner{Player::Mark::None};
    Moves valid_moves{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
};
} // namespace Tic_Tac_Toe
#endif // !TTT_HPP
