#ifndef MCTS_HPP
#define MCTS_HPP
#pragma once
#include "game.hpp"
#include <Random-Helper.hpp>
#include <Timer.hpp>
#include <cmath>
#include <map>
#include <memory>
#include <vector>
namespace MCTS {
template <Game::GameState State> class Node : public std::enable_shared_from_this<Node<State>> {
  public:
    using Node_Sptr = std::shared_ptr<Node>;
    using Node_Wptr = std::weak_ptr<Node>;
    using Player = Game::Player;

    constexpr explicit Node(const State &state_) : state(state_) {}
    constexpr Node(const Node_Wptr &parent_, const State &state_)
        : parent(parent_), state(state_) {}
    constexpr explicit Node(const Node_Sptr &node) : state(node->state) {}

    [[nodiscard]] constexpr Node_Sptr ptr() const & { return std::make_shared<Node>(*this); }
    [[nodiscard]] constexpr Node_Wptr get_this() { return this->shared_from_this(); }
    constexpr void reset() { parent.reset(); }
    constexpr void add_child(const Node_Wptr &parent_, const State &state_) {
        children.push_back(std::make_shared<Node>(Node(parent_, state_)));
    }
    [[nodiscard]] constexpr double score(const Player &player) const & {
        return wins.at(player) - wins.at(player.other_player());
    }
    [[nodiscard]] constexpr double ucb1_score(const Player &player, const double &lnTotal) const {
        return (wins.at(player) / visits) + sqrt(2 * lnTotal / visits);
    }
    Node_Sptr get_child() const &;
    [[nodiscard]] constexpr Node_Sptr get_random_child() const & {
        return rnd::select_randomly_value(children);
    }
    Node_Sptr ucb1() const &;
    Node_Sptr best_child() const &;
    void status() const &;
    void all_childern_status() const &;
    constexpr void won(const Player &player, const double &depth) { wins.at(player) += 1 / depth; }
    constexpr void visited() { ++visits; }
    void simulate();
    Node_Sptr userMove();

  private:
    Node_Wptr parent{};
    State state{};
    std::vector<Node_Sptr> children{};
    unsigned int visits{0};
    std::map<Player, double> wins{{Player{Player::Mark::X}, 0.}, {Player{Player::Mark::O}, 0.}};
};
template <Game::GameState State> class Mcts : public Game::Strategy<Mcts<State>> {
  public:
    Game::Move do_choose_move(const Timer::milliseconds_t &duration);

  private:
    Node<State> Tree{};
};
} // namespace MCTS
#endif // !MCTS_HPP
