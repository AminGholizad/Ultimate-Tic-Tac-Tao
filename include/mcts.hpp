#ifndef MCTS_HPP
#define MCTS_HPP
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <cmath>
#include "rand.hpp"
#include "timer.hpp"
namespace MCTS
{
template <class State>
class Node : public std::enable_shared_from_this<Node<State>>
{
public:
    using Node_Sptr = std::shared_ptr<Node>;
    using Node_Wptr = std::weak_ptr<Node>;
    using Player = typename State::Player;
    Node() = default;
    ~Node() = default;
    constexpr Node(State const &s) : state(s) {}
    constexpr Node(Node_Wptr const &p, State const &s) : parent(p), state(s) {}
    constexpr Node(Node_Sptr const &n) : state(n->state) {}
    constexpr Node_Sptr Ptr() const & { return std::make_shared<Node>(*this); }
    inline Node_Wptr getThis() { return this->shared_from_this(); }
    inline void reset() { parent.reset(); }
    inline void debugBoard() const & { state.debugBoard(); }
    inline void debugLargeboard() const & { state.debugLargeboard(); }
    inline void addChild(Node_Wptr const &p, State const &s) { children.push_back(std::make_shared<Node>(Node(p, s))); }
    constexpr double score(Player const &p) const { return wins.at(p) - wins.at(p.otherPlayer()); }
    constexpr double ucb1Score(Player const &p, double const &lnTotal) const { return wins.at(p) / visits + sqrt(2 * lnTotal / visits); }
    constexpr Player getPlayer() const & { return state.getPlayer(); }
    Node_Sptr getChild() const &;
    inline Node_Sptr getRandomChild() const & { return *rnd::select_randomly(children.begin(), children.end()); }
    Node_Sptr ucb1() const &;
    Node_Sptr bestChild() const &;
    void status() const &;
    void allChildernStatus() const &;
    inline void won(Player const &p, double const &depth) { wins.at(p) += 1 / depth; }
    inline void visited() { ++visits; }
    Node_Sptr choose_move(int const &duration);
    void simulate();
    inline State getState() const & { return state; }
    constexpr bool isOver() const & { return state.isOver(); }
    constexpr Player getWinner() const & { return state.getWinner(); }
    Node_Sptr userMove();
private:
    Node_Wptr parent{};
    State state{};
    std::vector<Node_Sptr> children{};
    unsigned int visits{0};
    std::map<Player, double> wins{{Player::Mark::X, 0.}, {Player::Mark::O, 0.}};
};
} // namespace MCTS
#endif // !MCTS_HPP
