#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP
#pragma once
#include "timer.hpp"
#include <limits>

namespace NEGAMAX {
template <class State> class Negamax {
public:
  static constexpr auto INF{std::numeric_limits<int>::max()};
  using Player = typename State::Player;
  using Move = typename State::Move;
  constexpr Negamax() = default;
  constexpr Negamax(State state_, int duration_)
      : state(std::move(state_)), duration(duration_) {}
  constexpr explicit Negamax(State state_) : state(std::move(state_)) {}

  constexpr void debugBoard() const & { state.debugBoard(); }
  constexpr void debugLargeboard() const & { state.debugLargeboard(); }

  [[nodiscard]] constexpr State getState() const & { return state; }
  [[nodiscard]] constexpr bool isOver() const & { return state.isOver(); }
  [[nodiscard]] constexpr Player getWinner() const & {
    return state.getWinner();
  }
  Negamax choose_move(int duration_ = 1000);
  std::pair<int, Move> simulate(timer::time start, int depth, int alpha = -INF,
                                int beta = INF, int color = 1) const &;
  Negamax userMove();

private:
  State state{};
  int duration{};
};
} // namespace NEGAMAX
#endif // NEGAMAX_HPP
