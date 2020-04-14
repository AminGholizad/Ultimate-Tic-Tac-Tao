#ifndef UTTT_HPP
#define UTTT_HPP
#pragma once
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "game.hpp"

namespace UTTT
{
class State
{
public:
    using Player = Game::Player;
    using Move = Game::Move;
    using Board9x9 = std::array<std::array<Player, 9>, 9>;
    using Board3x3 = std::array<std::array<Player, 3>, 3>;
    inline State() = default;
    inline ~State() = default;
    inline State(State const &) = default;
    inline State(State &&) = default;
    inline State &operator=(State const &) = default;
    inline State &operator=(State &&) = default;
    inline State(Board9x9 b, Board3x3 lb) : board(b), largeboard(lb) {}

    bool operator==(State const &s) const &;
    bool operator!=(State const &s) const &;

    void debugLargeboard() const &;
    void debugSubboard(size_t const &x, size_t const &y) const &;
    void debugBoard() const &;
    void debugValidMoves() const &;

    constexpr Player getWinner() const & { return winner; }
    constexpr Player getPlayer() const & { return player; }
    constexpr Move getMove() const & { return lastMove; }
    inline auto get_moves() const & { return valid_moves; }
    constexpr bool isOver() const & { return !winner.isNone(); }
    constexpr bool isDraw() const & { return winner.isDraw(); }

    inline void bring_to_first(Move const &move)
    {
        auto it = std::find(valid_moves.begin(), valid_moves.end(), move);
        std::rotate(valid_moves.begin(), it, it + 1);
    }
    std::pair<int, int> sub_win_count() const &;

    void userMove();
    void set_valid_moves();
    void init_valid_moves();
    void get_valid_moves();
    State sim_move(Move const &m) const &;
    void moveTo(Move const &m);
    inline auto game_over() const & { return std::make_tuple(valid_moves.empty(), winner == player, winner == player.otherPlayer()); }

private:
    Board9x9 board{Player::Mark::None};
    Board3x3 largeboard{Player::Mark::None};
    Move lastMove{-1, -1};
    Player player{Player::Mark::X};
    Player winner{Player::Mark::None};
    std::vector<Move> valid_moves{};

    Player compute_winner(Player const &p) const &;
    bool is_largeboard_full() const &;
    bool is_sub_winner(const size_t &x, const size_t &y, Player const &p) const &;
    bool is_sub_full(const size_t &x, const size_t &y) const &;
    void fill_sub(const size_t &x, const size_t &y, Player const &p);

    void updateState(Move const &m);

    inline bool is_valid(Move const &m) const & { return std::find(valid_moves.begin(), valid_moves.end(), m) != valid_moves.end(); }
};
} // namespace UTTT

#endif // !UTTT_HPP
