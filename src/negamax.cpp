#include "negamax.hpp"
#include <Timer.hpp>
namespace NEGAMAX {
template <class State>
Negamax<State> Negamax<State>::choose_move(const Timer::milliseconds_t &duration) {
    state.set_valid_moves();
    auto best_move = state.get_moves()[0];
    const auto timer = Timer::Timer();
    int depth = 1;
    while (timer.is_time_remaining(duration)) {
        auto [val, move] = simulate(timer, duration, depth);
        if (!timer.is_time_remaining(duration)) {
            break;
        }
        state.bring_to_first(move);
        best_move = move;
        depth++;
    }
    state.moveTo(best_move);
    return *this;
}
template <class State>
std::pair<int, typename Negamax<State>::Move>
Negamax<State>::simulate(const Timer::Timer &timer, const Timer::milliseconds_t &duration,
                         int depth, int alpha, int beta, int color) const & {
    auto [no_moves_left, did_I_win, did_opponent_win] = state.game_over();
    if (did_I_win || did_opponent_win) {
        return std::make_pair(color * (did_I_win - did_opponent_win) * 100 * (depth + 1), Move());
    }
    if (depth == 0 || no_moves_left || !timer.is_time_remaining(duration)) {
        auto [MEsum, OPsum] = state.sub_win_count();
        return std::make_pair(color * (MEsum - 2 * OPsum) * (depth + 1), Move());
    }
    int maxEval = -INF;
    auto best_move = state.get_moves()[0];
    for (auto mov : state.get_moves()) {
        auto tmp = Negamax(state.sim_move(mov));
        auto [val, move] = tmp.simulate(timer, duration, depth - 1, -beta, -alpha, -color);
        if (-val > maxEval) {
            maxEval = -val;
            best_move = mov;
        }
        alpha = (alpha < maxEval) ? maxEval : alpha;
        if (beta <= alpha) {
            break;
        }
    }
    return std::make_pair(maxEval, best_move);
}
template <class State> Negamax<State> Negamax<State>::userMove() {
    auto state_copy = state;
    state_copy.set_valid_moves();
    state_copy.userMove();
    return Negamax(state_copy);
}
} // namespace NEGAMAX
#include "uttt.hpp"
template class NEGAMAX::Negamax<UTTT::State>;
