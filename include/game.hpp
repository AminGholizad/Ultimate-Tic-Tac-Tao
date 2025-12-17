#ifndef GAME_HPP
#define GAME_HPP
#pragma once
#include "move.hpp"
#include "player.hpp"
#include <Timer.hpp>
#include <algorithm>
#include <limits>
#include <ranges>

namespace Game {
constexpr int INF{std::numeric_limits<int>::max()};
constexpr Timer::milliseconds_t DEFAULT_DURATION{1000};

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
    [[nodiscard]] constexpr decltype(auto) get_last_move(this auto &&self) {
        return (self.do_get_last_move());
    }
    [[nodiscard]] constexpr decltype(auto) get_moves(this auto &&self) {
        return (self.do_get_moves());
    }

    [[nodiscard]] constexpr bool is_over(this const auto &self) { return self.do_is_over(); }
    [[nodiscard]] constexpr bool is_draw(this const auto &self) { return self.do_is_draw(); }
    [[nodiscard]] constexpr bool is_board_full(this const auto &self) {
        for (const auto &row : self.get_board()) {
            for (const auto &cell : row) {
                if (cell.is_none()) {
                    return false;
                }
            }
        }
        return true;
    }
    [[nodiscard]] constexpr bool is_valid(this const auto &self, Move const &move) {
        auto valid_moves = self.do_get_moves();
        return std::ranges::find(valid_moves, move) != valid_moves.end();
    }
    constexpr void bring_to_first(this auto &self, Move const &move) {
        auto &moves = self.get_moves();
        auto iter = std::ranges::find(moves, move);
        std::rotate(moves.begin(), iter, iter + 1);
    }

    void debugBoard(this const auto &self) { self.do_debugBoard(); }
    void debugValidMoves(this const auto &self) { self.do_debugValidMoves(); }

    void set_valid_moves(this auto &self) { self.do_set_valid_moves(); }
    template <typename Self> [[nodiscard]] Self sim_move(this const Self &self, Move const &move) {
        return self.do_sim_move(move);
    }
    void moveTo(this auto &self, Move const &move);
    [[nodiscard]] constexpr auto game_over(this const auto &self) {
        return std::make_tuple(self.get_moves().empty(), self.get_winner() == self.get_player(),
                               self.get_winner() == self.get_player().other_player());
    }
    [[nodiscard]] int calc_score(this const auto &self, int color, int depth) {
        return self.do_calc_score(color, depth);
    }
    void updateState(this auto &&self, Move const &move) { self.do_updateState(move); }

  private:
    [[nodiscard]] Player compute_winner(this const auto &self, const Player &test_player) {
        return self.do_compute_winner(test_player);
    }
}; // class State

template <typename T>
concept GameState = std::is_base_of_v<State<T>, T>;

auto simulate(const GameState auto &state, const Timer::Timer &timer,
              const Timer::milliseconds_t &duration, int depth, int alpha = -INF, int beta = INF,
              int color = 1) {
    {
        auto [no_moves_left, did_I_win, did_opponent_win] = state.game_over();
        if (did_I_win || did_opponent_win) {
            return std::make_pair(
                color * (static_cast<int>(did_I_win) - static_cast<int>(did_opponent_win)) * 100 *
                    (depth + 1),
                Move{});
        }
        if (depth == 0 || no_moves_left || !timer.is_time_remaining(duration)) {
            auto score = state.calc_score(color, depth + 1);
            return std::make_pair(score, Move{});
        }
    }
    int maxEval = -INF;
    auto best_move = state.get_moves()[0];
    for (const auto &mov : state.get_moves()) {
        auto temp_state = state.sim_move(mov);
        auto [val, move] = simulate(temp_state, timer, duration, depth - 1, -beta, -alpha, -color);
        if (-val > maxEval) {
            maxEval = -val;
            best_move = mov;
        }
        alpha = (alpha < maxEval) ? maxEval : alpha;
        if (beta <= alpha) {
            break;
        }
    }
    return std::make_pair(maxEval, best_move);
}

Move choose_move(GameState auto &state, const Timer::milliseconds_t &duration) {
    state.set_valid_moves();
    auto best_move = state.get_moves()[0];
    const auto timer = Timer::Timer();
    int depth = 1;
    while (timer.is_time_remaining(duration)) {
        auto [_, move] = simulate(state, timer, duration, depth);
        if (!timer.is_time_remaining(duration)) {
            break;
        }
        state.bring_to_first(move);
        best_move = move;
        depth++;
    }
    return best_move;
}

auto userMove(GameState auto &state) {
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
                state.get_player() = state.get_player().other_player();
                state.get_moves().clear();
                return;
            }
        } while (!state.is_valid(move));
    }
    state.updateState(move);
    state.set_valid_moves();
}

void moveTo(GameState auto &state, const Move &move) {
    state.updateState(move);
    std::cerr << state.get_player().other_player() << " moved to :";
    std::cout << state.get_last_move() << '\n';
}

template <GameState GT> [[nodiscard]] constexpr bool operator==(const GT &lhs, const GT &rhs) {
    if (lhs.get_player() != rhs.get_player()) {
        return false;
    }
    if (lhs.get_last_move() != rhs.get_last_move()) {
        return false;
    }
    for (const auto &[lhs_row, rhs_row] : std::views::zip(lhs.get_board(), rhs.get_board())) {
        for (const auto &[lhs_cell, rhs_cell] : std::views::zip(lhs_row, rhs_row)) {
            if (lhs_cell != rhs_cell) {
                return false;
            }
        }
    }
    return true;
}

template <GameState GT> [[nodiscard]] constexpr bool operator!=(const GT &lhs, const GT &rhs) {
    if (lhs.get_player() == rhs.get_player()) {
        return false;
    }
    if (lhs.get_last_move() == rhs.get_last_move()) {
        return false;
    }
    for (const auto &[lhs_row, rhs_row] : std::views::zip(lhs.get_board(), rhs.get_board())) {
        for (const auto &[lhs_cell, rhs_cell] : std::views::zip(lhs_row, rhs_row)) {
            if (lhs_cell == rhs_cell) {
                return false;
            }
        }
    }
    return true;
}
} // namespace Game
#endif // !GAME_HPP
