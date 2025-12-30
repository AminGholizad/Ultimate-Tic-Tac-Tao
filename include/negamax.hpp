#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP
#pragma once
#include "game.hpp"
#include <Timer.hpp>
#include <limits>
namespace NEGAMAX {
constexpr int INF{std::numeric_limits<int>::max()};
constexpr Timer::milliseconds_t DEFAULT_DURATION{1000};
class Negamax : public Game::Strategy<Negamax> {
  public:
    constexpr explicit Negamax(Timer::milliseconds_t time_limit_)
        : time_limit{time_limit_ * 0.99} {}
    std::optional<Game::Move> do_choose_move(Game::GameState auto &state) const &;

  private:
    Timer::milliseconds_t time_limit{DEFAULT_DURATION};
    auto simulate(const Game::GameState auto &state, const Timer::Timer &timer, int depth,
                  int alpha = -INF, int beta = INF, int color = 1) const &;
};
} // namespace NEGAMAX
#endif // NEGAMAX_HPP
