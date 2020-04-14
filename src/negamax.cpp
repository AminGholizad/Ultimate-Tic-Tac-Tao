#include "negamax.hpp"
namespace NEGAMAX
{
template <class State>
const int negamax<State>::INF = 2147483646;

template <class State>
negamax<State> negamax<State>::choose_move(int t)
{
    duration = t;
    state.set_valid_moves();
    auto best_move = state.get_moves()[0];
    auto start = timer::now();
    int depth = 1;
    while (timer::isTimeRemaining(start, duration))
    {
        auto [val, move] = simulate(start, depth);
        if (!timer::isTimeRemaining(start, duration))
            break;
        state.bring_to_first(move);
        best_move = move;
        depth++;
    }
    state.moveTo(best_move);
    return *this;
}
template <class State>
std::pair<int, typename negamax<State>::Move> negamax<State>::simulate(timer::time start, int depth, int alpha, int beta, int color) const &
{
    auto [l, m, o] = state.game_over();
    if (m || o)
        return std::make_pair(color * (m - o) * 100 * (depth + 1), Move());
    if (depth == 0 || l || !timer::isTimeRemaining(start, duration))
    {
        auto [MEsum, OPsum] = state.sub_win_count();
        return std::make_pair(color * (MEsum - 2 * OPsum) * (depth + 1), Move());
    }
    int maxEval = -INF;
    auto best_move = state.get_moves()[0];
    for (auto mov : state.get_moves())
    {
        auto tmp = negamax(state.sim_move(mov), duration);
        auto [val, move] = tmp.simulate(start, depth - 1, -beta, -alpha, -color);
        if (-val > maxEval)
        {
            maxEval = -val;
            best_move = mov;
        }
        alpha = (alpha < maxEval) ? maxEval : alpha;
        if (beta <= alpha)
            break;
    }
    return std::make_pair(maxEval, best_move);
}
template <class State>
negamax<State> negamax<State>::userMove()
{
    auto s = state;
    s.set_valid_moves();
    s.userMove();
    return negamax(s, duration);
}
} // namespace NEGAMAX
#include "uttt.hpp"
template class NEGAMAX::negamax<UTTT::State>;