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
template <Game::GameState State> class Mcts : public Game::Strategy<Mcts<State>> {
  public:
    std::optional<Game::Move> do_choose_move(State &state, const Timer::milliseconds_t &duration);

  private:
    class Node {
      public:
        using Node_ptr = std::unique_ptr<Node>;
        using Player = Game::Player;
        constexpr Node() = default;
        constexpr explicit Node(State state_) : state(std::move(state_)) {}
        constexpr void add_child(State state_, Game::Move move_) {
            auto child = std::make_unique<Node>(state_);
            child->move = move_;
            child->parent = this;
            children.push_back(std::move(child));
        }
        [[nodiscard]] constexpr double score(const Player &player) const & {
            return wins.at(player) - wins.at(player.other_player());
        }
        [[nodiscard]] constexpr double ucb1_score(const Player &player,
                                                  const double &lnTotal) const {
            return (wins.at(player) / visits) + sqrt(2 * lnTotal / visits);
        }
        [[nodiscard]] constexpr Node *get_random_child() const & {
            return rnd::select_randomly(children)->get();
        }
        constexpr void won(const Player &player, const double &depth) {
            wins.at(player) += 1 / depth;
        }
        constexpr void visited() { ++visits; }

        [[nodiscard]] Node *get_child() const &;

        [[nodiscard]] Node *ucb1() const &;
        [[nodiscard]] Node *best_child() const &;
        void status() const &;
        void all_childern_status() const &;
        void simulate();

        Node *parent{};
        State state{};
        Game::Move move{};
        std::vector<Node_ptr> children{};
        unsigned int visits{0};
        std::map<Player, double> wins{{Player{Player::Mark::X}, 0.}, {Player{Player::Mark::O}, 0.}};
    };
    Node Tree;
};
} // namespace MCTS
#endif // !MCTS_HPP
