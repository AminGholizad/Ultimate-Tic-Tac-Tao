#ifndef NEGAMAX_HPP
#define NEGAMAX_HPP
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <algorithm>
#include "timer.hpp"
namespace NEGAMAX
{
template <class State>
class negamax
{
public:
    static const int INF;
    using Player = State::Player;
    using Move = State::Move;
    negamax() = default;
    inline negamax(State s, int d) : state(s), duration(d) {}
    inline negamax(State s) : state(s) {}
    ~negamax() = default;

    inline void debugBoard() const & { state.debugBoard(); }
    inline void debugLargeboard() const & { state.debugLargeboard(); }

    inline State getState() const & { return state; }
    constexpr bool isOver() const & { return state.isOver(); }
    constexpr Player getWinner() const & { return state.getWinner(); }
    negamax choose_move(int t = 1000);
    std::pair<int, Move> simulate(timer::time start, int depth, int alpha = -INF, int beta = INF, int color = 1) const &;
    negamax userMove();

private:
    State state{};
    int duration{};
};
} // namespace NEGAMAX
#endif // NEGAMAX_HPP
