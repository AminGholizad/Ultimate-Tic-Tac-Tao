#include "mcts.hpp"
#include <Timer.hpp>
#include <algorithm>
#include <iostream>
#include <queue>
namespace MCTS {
template <Game::GameState State> Mcts<State>::Node *Mcts<State>::Node::get_child() const & {
    return (std::ranges::all_of(children, [](const auto &child) { return child->visits > 0; }))
               ? ucb1()
               : get_random_child();
}
template <Game::GameState State> Mcts<State>::Node *Mcts<State>::Node::ucb1() const & {
    const auto lnTotal = std::log(visits);
    const auto player = state.get_player();
    return std::ranges::max_element(children,
                                    [player, lnTotal](const auto &node_a, const auto &node_b) {
                                        return node_a->ucb1_score(player, lnTotal) <
                                               node_b->ucb1_score(player, lnTotal);
                                    })
        ->get();
}
template <Game::GameState State> Mcts<State>::Node *Mcts<State>::Node::best_child() const & {
    const auto player = state.get_player();
    return std::ranges::max_element(children,
                                    [player](const auto &node_a, const auto &node_b) {
                                        return node_a->score(player) < node_b->score(player);
                                    })
        ->get();
}
template <Game::GameState State> void Mcts<State>::Node::status() const & {
    const auto player = state.get_player().other_player(); // last played player
    std::cerr << move << "(#visits " << visits << " ,{";
    std::cerr << player << ':' << wins.at(player) << ", " << player.other_player() << ':'
              << wins.at(player.other_player())
              << "}) Score:" << wins.at(player) - wins.at(player.other_player()) << '\n';
}
template <Game::GameState State> void Mcts<State>::Node::all_childern_status() const & {
    std::cerr << "Player:" << state.get_player() << " #childern " << children.size() << '\n';
    for (const auto &child : children) {
        child->status();
    }
    std::cerr << "best is: ";
    best_child()->status();
}
template <Game::GameState State>
std::optional<Game::Move> Mcts<State>::do_choose_move(State &state) {
    if (auto result = Tree.find(state); result) {
        Tree = Node::detach_subtree(result);
    } else {
        Tree = Node(state);
    }
    for (const auto move_ : Tree.state.get_moves()) {
        Tree.add_child(Tree.state.sim_move(move_), move_);
    }
    const auto timer = Timer::Timer();
    while (timer.is_time_remaining(time_limit)) {
        Tree.simulate(timer, time_limit);
    }
    const auto best = Tree.best_child();
    return best->move;
}
template <Game::GameState State>
void Mcts<State>::Node::simulate(const Timer::Timer timer,
                                 const Timer::milliseconds_t time_limit_) {
    auto current_node = get_child();
    double depth = 0;
    while (timer.is_time_remaining(time_limit_) && !current_node->state.is_over()) {
        if (current_node->children.size() == 0) {
            for (const auto move_ : current_node->state.get_moves()) {
                current_node->add_child(current_node->state.sim_move(move_), move_);
            }
        }
        current_node = current_node->get_child();
        depth++;
    }
    if (const auto winner = current_node->state.get_winner();
        !winner.is_draw() && !winner.is_none()) {
        while (current_node != nullptr) {
            current_node->visited();
            current_node->won(winner, depth);
            current_node = current_node->parent;
        }
    } else {
        while (current_node != nullptr) {
            current_node->visited();
            current_node = current_node->parent;
        }
    }
}
template <Game::GameState State> Mcts<State>::Node *Mcts<State>::Node::find(const State &state_) {
    std::queue<Node *> que{};
    for (const auto &child : children) {
        que.push(child.get());
    }
    while (!que.empty()) {
        auto *current = que.front();
        que.pop();
        if (current->state == state_) {
            return current;
        }
        for (const auto &child : current->children) {
            que.push(child.get());
        }
    }
    return nullptr;
}

} // namespace MCTS
#include "Tic_Tac_Toe.hpp"
template class MCTS::Mcts<Tic_Tac_Toe::State>;

#include "Tic_Tac_Toe_V2.hpp"
template class MCTS::Mcts<Tic_Tac_Toe_V2::State>;

#include "Ultimate_Tic_Tac_Toe.hpp"
template class MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>;
