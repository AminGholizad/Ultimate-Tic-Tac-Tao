#ifndef TTT_HPP
#define TTT_HPP
#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "game.hpp"

namespace TTT
{
class State
{
public:
    using Player = Game::Player;
    using Move = Game::Move;
    using Board3x3 = std::array<std::array<Player, 3>, 3>;
    inline State() = default;
    inline ~State() = default;
    inline State(State const &) = default;
    inline State(State &&) = default;
    inline State &operator=(State const &) = default;
    inline State &operator=(State &&) = default;
    inline State(Board3x3 b, Move m, Player p) : board(b), lastMove(m), player(p) {}

    bool operator==(State const &s) const &;
    bool operator!=(State const &s) const &;

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

    void userMove();
    void set_valid_moves();
    State sim_move(Move const &m) const &;
    void moveTo(Move const &m);
    constexpr auto game_over() const & { return std::make_tuple(winner.isDraw(), winner == player, winner == player.otherPlayer()); }

private:
    Board3x3 board{Player::None};
    Move lastMove{-1, -1};
    Player player{Player::X};
    Player winner{Player::None};
    std::vector<Move> valid_moves{};

    Player compute_winner(Player const &p) const &;
    bool is_board_full() const &;
    bool is_valid(Move const &m) const & { return std::find(valid_moves.begin(), valid_moves.end(), m) != valid_moves.end(); }
    void updateState(Move const &m);
};
} // namespace TTT
#endif // !TTT_HPP