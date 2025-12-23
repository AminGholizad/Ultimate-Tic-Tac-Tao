#include "mcts.hpp"
#include <Timer.hpp>
#include <iostream>
namespace MCTS {
template <Game::GameState State> typename Node<State>::Node_Sptr Node<State>::get_child() const & {
    return (std::all_of(children.begin(), children.end(),
                        [](auto child) { return child->visits > 0; }))
               ? ucb1()
               : get_random_child();
}
template <Game::GameState State> typename Node<State>::Node_Sptr Node<State>::ucb1() const & {
    const auto lnTotal = std::log(visits);
    const auto player = state.get_player();
    return *std::ranges::max_element(children, [player, lnTotal](auto node_a, auto node_b) {
        return node_a->ucb1Score(player, lnTotal) < node_b->ucb1Score(player, lnTotal);
    });
}
template <Game::GameState State> typename Node<State>::Node_Sptr Node<State>::best_child() const & {
    const auto player = state.get_player();
    return *std::ranges::max_element(children, [player](auto node_a, auto node_b) {
        return node_a->score(player) < node_b->score(player);
    });
}
template <Game::GameState State> void Node<State>::status() const & {
    const auto player = state.get_player();
    std::cerr << "(#v " << visits << " ,{";
    std::cerr << player << ':' << wins.at(player) << ", " << player.other_player() << ':'
              << wins.at(player.other_player())
              << "}) Score:" << wins.at(player) - wins.at(player.other_player()) << "\n";
}
template <Game::GameState State> void Node<State>::all_childern_status() const & {
    std::cerr << "Player:" << state.get_player() << " #childern " << children.size() << std::endl;
    for (const auto &child : children) {
        child->status();
    }
    std::cerr << "best is: ";
    best_child()->status();
}
template <Game::GameState State>
typename Node<State>::Node_Sptr Node<State>::do_choose_move(const Timer::milliseconds_t &duration) {
    const auto tmp = get_this();
    // if (state.get_moves().empty()) {
    //     state.set_valid_moves();
    // }
    for (const auto move : state.get_moves()) {
        add_child(tmp, state.sim_move(move));
    }
    const auto timer = Timer::Timer();
    while (timer.is_time_remaining(duration)) {
        simulate();
    }
    auto best = best_child();
    state.moveTo(best->state.get_last_move());
    return best;
}
template <Game::GameState State> void Node<State>::simulate() {
    auto tmp = get_child();
    double depth = 0;
    while (!tmp->state.isOver()) {
        if (tmp->children.size() == 0) {
            for (const auto move : tmp->state.get_moves()) {
                tmp->addChild(tmp, tmp->state.sim_move(move));
            }
        }
        tmp = tmp->get_child();
        depth++;
    }
    if (const auto winner = tmp->state.get_winner(); !winner.is_draw()) {
        while (tmp != nullptr) {
            tmp->visited();
            tmp->won(winner, depth);
            tmp = tmp->parent.lock();
        }
    } else {
        while (tmp != nullptr) {
            tmp->visited();
            tmp = tmp->parent.lock();
        }
    }
}
template <Game::GameState State> typename Node<State>::Node_Sptr Node<State>::userMove() {
    auto state_copy = state;
    // state_copy.set_valid_moves();
    state_copy.userMove();
    for (auto child : children) {
        if (child->state == state_copy) {
            return child;
        }
    }
    return std::make_shared<Node>(Node(get_this(), state_copy));
}
} // namespace MCTS
// #include "uttt.hpp"
// template class MCTS::Node<UTTT::State>;
