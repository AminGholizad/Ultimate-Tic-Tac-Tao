#include "mcts.hpp"
#include <Timer.hpp>
#include <algorithm>
#include <iostream>
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
    const auto player = state.get_player().other_player();
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
    // TODO: check if Tree has value then check for state inside Tree and if it exists use it for
    // next iterations otherwise create a new Tree.
    Tree = Node(state);
    for (const auto move_ : Tree.state.get_moves()) {
        Tree.add_child(Tree.state.sim_move(move_), move_);
    }
    const auto timer = Timer::Timer();
    while (timer.is_time_remaining(time_limit)) {
        Tree.simulate();
    }
    const auto best = Tree.best_child();
    return best->move;
}
template <Game::GameState State> void Mcts<State>::Node::simulate() {
    auto current_node = get_child();
    double depth = 0;
    // TODO: also check for time limit
    while (!current_node->state.is_over()) {
        if (current_node->children.size() == 0) {
            for (const auto move_ : current_node->state.get_moves()) {
                current_node->add_child(current_node->state.sim_move(move_), move_);
            }
        }
        current_node = current_node->get_child();
        depth++;
    }
    if (const auto winner = current_node->state.get_winner(); !winner.is_draw()) {
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
} // namespace MCTS
#include "Tic_Tac_Toe.hpp"
template class MCTS::Mcts<Tic_Tac_Toe::State>;

#include "Ultimate_Tic_Tac_Toe.hpp"
template class MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>;
