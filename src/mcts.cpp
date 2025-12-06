#include "mcts.hpp"
#include "timer.hpp"
#include <iostream>
namespace MCTS {
template <class State>
typename Node<State>::Node_Sptr Node<State>::getChild() const & {
  return (std::all_of(children.begin(), children.end(),
                      [](auto child) { return child->visits > 0; }))
             ? ucb1()
             : getRandomChild();
}
template <class State>
typename Node<State>::Node_Sptr Node<State>::ucb1() const & {
  const auto lnTotal = log(visits);
  const auto player = state.getPlayer();
  return *std::max_element(children.begin(), children.end(),
                           [player, lnTotal](auto node_a, auto node_b) {
                             return node_a->ucb1Score(player, lnTotal) <
                                    node_b->ucb1Score(player, lnTotal);
                           });
}
template <class State>
typename Node<State>::Node_Sptr Node<State>::bestChild() const & {
  const auto player = state.getPlayer();
  return *std::max_element(
      children.begin(), children.end(), [player](auto node_a, auto node_b) {
        return node_a->score(player) < node_b->score(player);
      });
}
template <class State> void Node<State>::status() const & {
  const auto player = state.getPlayer();
  std::cerr << "(#v " << visits << " ,{";
  std::cerr << player << ':' << wins.at(player) << ", " << player.otherPlayer()
            << ':' << wins.at(player.otherPlayer())
            << "}) Score:" << wins.at(player) - wins.at(player.otherPlayer())
            << "\n";
}
template <class State> void Node<State>::allChildernStatus() const & {
  std::cerr << "Player:" << state.getPlayer() << " #childern "
            << children.size() << std::endl;
  for (const auto &child : children) {
    child->status();
  }
  std::cerr << "best is: ";
  bestChild()->status();
}
template <class State>
typename Node<State>::Node_Sptr Node<State>::choose_move(int const &duration) {
  const auto tmp = getThis();
  if (state.get_moves().empty()) {
    state.set_valid_moves();
  }
  for (const auto move : state.get_moves()) {
    addChild(tmp, state.sim_move(move));
  }
  const auto start = timer::now();
  while (timer::isTimeRemaining(start, duration)) {
    simulate();
  }
  auto best = bestChild();
  state.moveTo(best->state.getMove());
  return best;
}
template <class State> void Node<State>::simulate() {
  auto tmp = getChild();
  double depth = 0;
  while (!tmp->state.isOver()) {
    if (tmp->children.size() == 0) {
      for (const auto move : tmp->state.get_moves()) {
        tmp->addChild(tmp, tmp->state.sim_move(move));
      }
    }
    tmp = tmp->getChild();
    depth++;
  }
  if (const auto winner = tmp->state.getWinner(); !winner.isDraw()) {
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
template <class State> typename Node<State>::Node_Sptr Node<State>::userMove() {
  auto state_copy = state;
  state_copy.set_valid_moves();
  state_copy.userMove();
  for (auto child : children) {
    if (child->state == state_copy) {
      return child;
    }
  }
  return std::make_shared<Node>(Node(getThis(), state_copy));
}
} // namespace MCTS
#include "uttt.hpp"
template class MCTS::Node<UTTT::State>;
