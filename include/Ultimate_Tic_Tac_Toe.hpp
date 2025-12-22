#ifndef UTTT_HPP
#define UTTT_HPP
#pragma once
#include "game.hpp"
#include "move.hpp"
#include "player.hpp"
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

namespace Ultimate_Tic_Tac_Toe {
static constexpr auto ZERO = 0ULL;
static constexpr auto THREE = 3ULL;
static constexpr auto NINE = 9ULL;
class State : public Game::State<State> {
  public:
    using Player = Game::Player;
    using Move = Game::Move;
    using Moves = std::vector<Move>;
    using Board9x9 = std::array<std::array<Player, NINE>, NINE>;   // TODO: make this linear
    using Board3x3 = std::array<std::array<Player, THREE>, THREE>; // TODO: make this linear
    constexpr State() = default;
    constexpr State(Board9x9 board_, Move last_move_) : board(board_), last_move(last_move_) {
        player = board_[last_move_.x][last_move_.y].other_player();
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (is_sub_winner(i * 3, j * 3, player)) {
                    largeboard[i][j] = player;
                    fill_sub(i * 3, j * 3, player);
                    winner = do_compute_winner(player);
                } else if (const auto other = player.other_player();
                           is_sub_winner(i * 3, j * 3, other)) {
                    largeboard[i][j] = other;
                    fill_sub(i * 3, j * 3, other);
                    winner = do_compute_winner(other);
                } else if (const auto draw = Player{Player::Mark::Draw};
                           is_sub_full(i * 3, j * 3)) {
                    largeboard[i][j] = draw;
                    fill_sub(i * 3, j * 3, draw);
                }
            }
            set_valid_moves();
        }
        if (auto checked_winner = do_compute_winner(player); checked_winner == player) {
            winner = checked_winner;
        } else if (checked_winner = do_compute_winner(player.other_player());
                   checked_winner == player.other_player()) {
            winner = checked_winner;
        }
    }

    void do_debugValidMoves() const &;
    void do_debugBoard() const &;

    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.board); }
    [[nodiscard]] decltype(auto) do_get_player(this auto &&self) { return (self.player); }
    [[nodiscard]] decltype(auto) do_get_winner(this auto &&self) { return (self.winner); }
    [[nodiscard]] decltype(auto) do_get_moves(this auto &&self) { return (self.valid_moves); }

    [[nodiscard]] constexpr bool do_is_over() const & { return !winner.is_none(); }
    [[nodiscard]] constexpr bool do_is_draw() const & { return winner.is_draw(); }

    [[nodiscard]] constexpr std::pair<int, int> sub_win_count() const & {
        int MEsum = 0;
        int OPsum = 0;
        for (auto i = ZERO; i < THREE; ++i) {
            for (auto j = ZERO; j < THREE; ++j) {
                if (largeboard[i][j] == player) {
                    ++MEsum;
                } else if (largeboard[i][j] == player.other_player()) {
                    ++OPsum;
                }
            }
        }
        return std::make_pair(MEsum, OPsum);
    }

    void debugLargeboard() const &;
    void debugSubboard(const size_t &x, const size_t &y) const &;

    [[nodiscard]] State do_sim_move(const Move &move) const &;

    [[nodiscard]] Player do_compute_winner(Player const &test_player) const &;

    constexpr void do_updateState(Move const &move) {
        board[move.x][move.y] = player;
        last_move = move;
        const auto [large_x, large_y] = move / 3;
        const auto sub_x = large_x * 3;
        const auto sub_y = large_y * 3;
        if (is_sub_winner(sub_x, sub_y, player)) {
            largeboard[large_x][large_y] = player;
            fill_sub(sub_x, sub_y, player);
            winner = do_compute_winner(player);
        } else if (is_sub_full(sub_x, sub_y)) {
            largeboard[large_x][large_y] = Player(Player::Mark::Draw);
            fill_sub(sub_x, sub_y, Player(Player::Mark::Draw));
            winner = do_compute_winner(player);
        }
        player = player.other_player();
        set_valid_moves();
    }

    [[nodiscard]] int do_calc_score(int color, int depth) const & {
        auto [MEsum, OPsum] = sub_win_count();
        return color * (MEsum - 2 * OPsum) * (depth + 1);
    }

  private:
    Board9x9 board{};
    Board3x3 largeboard{};
    std::optional<Move> last_move{};
    Player player{Player::Mark::X};
    Player winner{Player::Mark::None};
    Moves valid_moves{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, //
                      {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {1, 8}, //
                      {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, //
                      {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, //
                      {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8}, //
                      {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, //
                      {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, //
                      {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7}, {7, 8}, //
                      {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {8, 6}, {8, 7}, {8, 8}};

    constexpr void fill_sub(const size_t &x, const size_t &y, Player const &player_) {
        for (auto i = x; i < x + 3; ++i) {
            for (auto j = y; j < y + 3; ++j) {
                board[i][j] = player_;
            }
        }
    }

    [[nodiscard]] bool is_largeboard_full() const &;
    [[nodiscard]] constexpr bool is_sub_winner(const size_t &x, const size_t &y,
                                               const Player &test_player) const & {
        for (auto i = ZERO; i < THREE; ++i) {
            if (board[i + x][y] == test_player && board[i + x][1 + y] == test_player &&
                board[i + x][2 + y] == test_player) {
                return true;
            }
            if (board[x][i + y] == test_player && board[1 + x][i + y] == test_player &&
                board[2 + x][i + y] == test_player) {
                return true;
            }
        }
        if (board[x][y] == test_player && board[1 + x][1 + y] == test_player &&
            board[2 + x][2 + y] == test_player) {
            return true;
        }
        if (board[x][2 + y] == test_player && board[1 + x][1 + y] == test_player &&
            board[2 + x][y] == test_player) {
            return true;
        }
        return false;
    }
    [[nodiscard]] constexpr bool is_sub_full(const size_t &x, const size_t &y) const & {
        for (auto i = x; i < x + 3; ++i) {
            for (auto j = y; j < y + 3; ++j) {
                if (board[i][j].is_none()) {
                    return false;
                }
            }
        }
        return true;
    }

    constexpr void set_valid_moves() {
        valid_moves.clear();
        assert(last_move);
        const auto [large_x, large_y] = *last_move % THREE;
        const size_t sub_x = large_x * THREE;
        const size_t sub_y = large_y * THREE;
        if (largeboard[large_x][large_y].is_none()) {
            for (auto i = ZERO; i < THREE; ++i) {
                for (auto j = ZERO; j < THREE; ++j) {
                    if (board[i + sub_x][j + sub_y].is_none()) {
                        valid_moves.emplace_back(i + sub_x, j + sub_y);
                    }
                }
            }
        } else {
            for (auto i = ZERO; i < NINE; ++i) {
                for (auto j = ZERO; j < NINE; ++j) {
                    if (board[i][j].is_none()) {
                        valid_moves.emplace_back(i, j);
                    }
                }
            }
        }
    }
};
} // namespace Ultimate_Tic_Tac_Toe

#endif // !UTTT_HPP
