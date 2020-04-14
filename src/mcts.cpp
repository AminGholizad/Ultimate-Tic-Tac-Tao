#include "mcts.hpp"
namespace MCTS
{
template <class State>
Node<State>::Node_Sptr Node<State>::getChild() const &
{
    return (std::all_of(children.begin(), children.end(), [](auto child) { return child->visits > 0; }))
               ? ucb1()
               : getRandomChild();
}
template <class State>
Node<State>::Node_Sptr Node<State>::ucb1() const &
{
    const auto lnTotal = log(visits);
    const auto p = state.getPlayer();
    return *std::max_element(children.begin(), children.end(),
                             [p, lnTotal](auto a, auto b) { return a->ucb1Score(p, lnTotal) < b->ucb1Score(p, lnTotal); });
}
template <class State>
Node<State>::Node_Sptr Node<State>::bestChild() const &
{
    const auto p = state.getPlayer();
    return *std::max_element(children.begin(), children.end(),
                             [p](auto a, auto b) { return a->score(p) < b->score(p); });
}
template <class State>
void Node<State>::status() const &
{
    auto player = state.getPlayer();
    std::cerr << "(#v " << visits << " ,{";
    std::cerr << player << ':' << wins.at(player) << ", "
              << player.otherPlayer() << ':' << wins.at(player.otherPlayer()) << "}) Score:"
              << wins.at(player) - wins.at(player.otherPlayer()) << "\n";
}
template <class State>
void Node<State>::allChildernStatus() const &
{
    std::cerr << "Player:" << state.getPlayer() << " #childern " << children.size() << std::endl;
    for (auto child : children)
        child->status();
    std::cerr << "best is: ";
    bestChild()->status();
}
template <class State>
Node<State>::Node_Sptr Node<State>::choose_move(int const &duration)
{
    auto tmp = getThis();
    if (state.get_moves().empty())
        state.set_valid_moves();
    for (auto m : state.get_moves())
        addChild(tmp, state.sim_move(m));
    auto start = timer::now();
    while (timer::isTimeRemaining(start, duration))
        simulate();
    auto best = bestChild();
    state.moveTo(best->state.getMove());
    return best;
}
template <class State>
void Node<State>::simulate()
{
    auto tmp = getChild();
    double depth = 0;
    while (!tmp->state.isOver())
    {
        if (tmp->children.size() == 0)
            for (auto m : tmp->state.get_moves())
                tmp->addChild(tmp, tmp->state.sim_move(m));
        tmp = tmp->getChild();
        depth++;
    }
    if (auto winner = tmp->state.getWinner(); !winner.isDraw())
        while (tmp != nullptr)
        {
            tmp->visited();
            tmp->won(winner, depth);
            tmp = tmp->parent.lock();
        }
    else
        while (tmp != nullptr)
        {
            tmp->visited();
            tmp = tmp->parent.lock();
        }
}
template <class State>
Node<State>::Node_Sptr Node<State>::userMove()
{
    auto s = state;
    s.set_valid_moves();
    s.userMove();
    for (auto child : children)
        if (child->state == s)
            return child;
    return std::make_shared<Node>(Node(getThis(), s));
}
} // namespace MCTS
#include "uttt.hpp"
template class MCTS::Node<UTTT::State>;