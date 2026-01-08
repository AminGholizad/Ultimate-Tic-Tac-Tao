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
constexpr Timer::milliseconds_t DEFAULT_DURATION{1000};
constexpr double TIME_LIMIT_REDUCTION_FACTOR{0.98};
template <Game::GameState State> class Mcts : public Game::Strategy<Mcts<State>> {
  public:
    constexpr explicit Mcts(Timer::milliseconds_t time_limit_)
        : time_limit{time_limit_ * TIME_LIMIT_REDUCTION_FACTOR} {}
    std::optional<Game::Move> do_choose_move(State &state);
    void status() { Tree.status(); }

  private:
    class Node {
      public:
        using Node_ptr = std::unique_ptr<Node>;
        using Player = Game::Player;
        constexpr Node() = default;
        constexpr explicit Node(State state_) : state(std::move(state_)) {}

        Node(Node &&other) noexcept
            : parent(nullptr), state(other.state), move(other.move),
              children(std::move(other.children)), visits(other.visits),
              wins(std::move(other.wins)) {
            fix_children_parent();
        }

        Node &operator=(Node &&other) noexcept {
            if (this != &other) {
                state = other.state;
                move = other.move;
                children = std::move(other.children);
                visits = other.visits;
                wins = std::move(other.wins);
                parent = nullptr;
                fix_children_parent();
            }
            return *this;
        }

        Node(const Node &) = delete;
        Node operator=(const Node &) = delete;
        ~Node() = default;

        void fix_children_parent() {
            for (auto &child : children) {
                child->parent = this;
            }
        }

        static Node detach_subtree(Node *node) {
            if (node == nullptr) {
                return Node{};
            }
            if (node->parent == nullptr) {
                return std::move(*node);
            }

            auto parent = node->parent;
            auto &siblings = parent->children;

            auto iter = std::ranges::find_if(
                siblings, [&](const Node::Node_ptr &child) { return child.get() == node; });

            if (iter == siblings.end()) {
                return Node{};
            }
            Node tmp = std::move(*(*iter));
            siblings.erase(iter);

            tmp.parent = nullptr;
            return tmp;
        }

        constexpr void add_child(State state_, Game::Move move_) {
            if (auto result = find(state_); result == nullptr) {
                auto child = std::make_unique<Node>(state_);
                child->move = move_;
                child->parent = this;
                children.push_back(std::move(child));
            }
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
        void simulate(Timer::Timer timer, Timer::milliseconds_t time_limit);
        [[nodiscard]] Node *find(const State &state_);

        Node *parent{};
        State state{};
        Game::Move move{}; // NOLINT(readability-redundant-member-init)
        std::vector<Node_ptr> children{};
        unsigned int visits{0};
        std::map<Player, double> wins{{Player{Player::Mark::X}, 0.}, {Player{Player::Mark::O}, 0.}};
    };
    Node Tree;
    Timer::milliseconds_t time_limit{DEFAULT_DURATION};
};
} // namespace MCTS
#endif // !MCTS_HPP
