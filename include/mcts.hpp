#ifndef MCTS_HPP
#define MCTS_HPP
#pragma once
#include <Random-Helper.hpp>
#include <Timer.hpp>
#include <cmath>
#include <map>
#include <memory>
#include <vector>
namespace MCTS {
template <class State> class Node : public std::enable_shared_from_this<Node<State>> {
  public:
    using Node_Sptr = std::shared_ptr<Node>;
    using Node_Wptr = std::weak_ptr<Node>;
    using Player = typename State::Player;
    constexpr Node() = default;
    constexpr explicit Node(const State &state_) : state(state_) {}
    constexpr Node(const Node_Wptr &parent_, const State &state_)
        : parent(parent_), state(state_) {}
    constexpr explicit Node(const Node_Sptr &node) : state(node->state) {}
    [[nodiscard]] constexpr Node_Sptr Ptr() const & { return std::make_shared<Node>(*this); }
    [[nodiscard]] constexpr Node_Wptr getThis() { return this->shared_from_this(); }
    constexpr void reset() { parent.reset(); }
    constexpr void debugBoard() const & { state.debugBoard(); }
    constexpr void debugLargeboard() const & { state.debugLargeboard(); }
    constexpr void addChild(const Node_Wptr &player, const State &state_) {
        children.push_back(std::make_shared<Node>(Node(player, state_)));
    }
    constexpr double score(const Player &player) const {
        return wins.at(player) - wins.at(player.otherPlayer());
    }
    constexpr double ucb1Score(const Player &player, const double &lnTotal) const {
        return (wins.at(player) / visits) + sqrt(2 * lnTotal / visits);
    }
    constexpr Player getPlayer() const & { return state.getPlayer(); }
    Node_Sptr getChild() const &;
    [[nodiscard]] constexpr Node_Sptr getRandomChild() const & {
        return *rnd::select_randomly(children.begin(), children.end());
    }
    Node_Sptr ucb1() const &;
    Node_Sptr bestChild() const &;
    void status() const &;
    void allChildernStatus() const &;
    constexpr void won(const Player &player, const double &depth) { wins.at(player) += 1 / depth; }
    constexpr void visited() { ++visits; }
    Node_Sptr choose_move(const Timer::milliseconds_t &duration);
    void simulate();
    [[nodiscard]] constexpr State getState() const & { return state; }
    [[nodiscard]] constexpr bool isOver() const & { return state.isOver(); }
    [[nodiscard]] constexpr Player getWinner() const & { return state.getWinner(); }
    Node_Sptr userMove();

  private:
    Node_Wptr parent{};
    State state{};
    std::vector<Node_Sptr> children{};
    unsigned int visits{0};
    std::map<Player, double> wins{{Player{Player::Mark::X}, 0.}, {Player{Player::Mark::O}, 0.}};
};
} // namespace MCTS
#endif // !MCTS_HPP
