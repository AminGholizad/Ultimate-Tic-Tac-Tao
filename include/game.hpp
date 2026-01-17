#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include "move.hpp"
#include "player.hpp"
#include <Timer.hpp>
#include <algorithm>

namespace Game {

template <typename GAME> class State {
  public:
    [[nodiscard]] constexpr decltype(auto) get_board(this auto &&self) {
        return (self.do_get_board());
    }
    [[nodiscard]] constexpr decltype(auto) get_winner(this auto &&self) {
        return (self.do_get_winner());
    }
    [[nodiscard]] constexpr decltype(auto) get_player(this auto &&self) {
        return (self.do_get_player());
    }
    [[nodiscard]] constexpr decltype(auto) get_moves(this auto &&self) {
        return (self.do_get_moves());
    }

    [[nodiscard]] constexpr bool is_over(this const auto &self) { return self.do_is_over(); }
    [[nodiscard]] constexpr bool is_first_move(this const auto &self) {
        return self.do_is_first_move();
    }
    [[nodiscard]] constexpr bool is_draw(this const auto &self) { return self.do_is_draw(); }
    [[nodiscard]] constexpr bool is_board_full(this const auto &self) {
        return self.do_is_board_full();
    }
    [[nodiscard]] constexpr bool is_valid_move(this const auto &self,
                                               const std::optional<Game::Move> &move) {
        if (!move) {
            return true;
        }
        auto valid_moves = self.do_get_moves();
        return std::ranges::find(valid_moves, *move) != valid_moves.end();
    }

    void debugBoard(this const auto &self) { self.do_debugBoard(); }
    void debugValidMoves(this const auto &self) { self.do_debugValidMoves(); }

    template <typename Self> [[nodiscard]] Self sim_move(this const Self &self, Move const &move) {
        return self.do_sim_move(move);
    }

    [[nodiscard]] constexpr auto game_over(this const auto &self) {
        return std::make_tuple(self.get_moves().empty(), self.get_winner() == self.get_player(),
                               self.get_winner() == self.get_player().other_player());
    }
    [[nodiscard]] int calc_score(this const auto &self, int color, int depth) {
        return self.do_calc_score(color, depth);
    }
    void updateState(this auto &&self, const Move &move) { self.do_updateState(move); }

    constexpr void change_player(this auto &&self) { self.do_change_player(); }

  private:
    [[nodiscard]] Player compute_winner(this const auto &self, const Player &test_player) {
        return self.do_compute_winner(test_player);
    }
}; // class State

template <typename T>
concept GameState = std::derived_from<T, State<T>>;

template <typename STRATEGY> class Strategy {
  public:
    std::optional<Move> choose_move(this auto &&self, GameState auto &state) {
        return self.do_choose_move(state);
    }
};
template <typename T>
concept GameStrategy = std::derived_from<T, Strategy<T>>;

void moveTo(GameState auto &state, const std::optional<Game::Move> &move) {
    if (!move) {
        std::cerr << "other player will go first...\n";
        state.change_player();
        return;
    }
    state.updateState(*move);
    std::cerr << state.get_player().other_player() << " moved to :";
    std::cout << *move << '\n';
}

template <GameState GT> [[nodiscard]] constexpr bool operator==(const GT &lhs, const GT &rhs) {
    if (lhs.get_player() != rhs.get_player()) {
        return false;
    }
    if (lhs.get_board() != rhs.get_board()) {
        return false;
    }
    return true;
}

template <GameState GT> [[nodiscard]] constexpr bool operator!=(const GT &lhs, const GT &rhs) {
    if (lhs.get_player() == rhs.get_player()) {
        return false;
    }
    if (lhs.get_board() == rhs.get_board()) {
        return false;
    }
    return true;
}

void run_game(GameState auto &game, GameStrategy auto &player1_strategy,
              GameStrategy auto &player2_strategy) {
    while (!game.is_over()) {
        auto move = player1_strategy.choose_move(game);
        moveTo(game, move);
        if (!game.is_over()) {
            move = player2_strategy.choose_move(game);
            moveTo(game, move);
        }
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
} // namespace Game
#endif // !GAME_HPP
