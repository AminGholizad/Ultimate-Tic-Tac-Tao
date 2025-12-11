#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP
#pragma once
#include <Timer.hpp>
#include <limits>
#include <utility>

namespace NEGAMAX {
template <class State> class Negamax {
    static constexpr auto INF{std::numeric_limits<int>::max()};

  public:
    using Player = typename State::Player;
    using Move = typename State::Move;
    constexpr Negamax() = default;
    constexpr explicit Negamax(State state_) : state(std::move(state_)) {}

    constexpr void debugBoard() const & { state.debugBoard(); }
    constexpr void debugLargeboard() const & { state.debugLargeboard(); }

    [[nodiscard]] constexpr State getState() const & { return state; }
    [[nodiscard]] constexpr bool isOver() const & { return state.isOver(); }
    [[nodiscard]] constexpr Player getWinner() const & { return state.getWinner(); }
    Negamax choose_move(const Timer::milliseconds_t &duration = Timer::milliseconds_t{1000});
    std::pair<int, Move> simulate(const Timer::Timer &timer, const Timer::milliseconds_t &duration,
                                  int depth, int alpha = -INF, int beta = INF,
                                  int color = 1) const &;
    Negamax userMove();

  private:
    State state{};
};
} // namespace NEGAMAX
#endif // NEGAMAX_HPP
