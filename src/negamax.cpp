#include "negamax.hpp"
#include <Timer.hpp>
namespace NEGAMAX {
auto Negamax::simulate(const Game::GameState auto &state, const Timer::Timer &timer,
                       const Timer::milliseconds_t &duration, int depth, int alpha, int beta,
                       int color) const & {
    {
        auto [no_moves_left, did_I_win, did_opponent_win] = state.game_over();
        if (did_I_win || did_opponent_win) {
            return std::make_pair(
                color * (static_cast<int>(did_I_win) - static_cast<int>(did_opponent_win)) * 100 *
                    (depth + 1),
                Game::Move{});
        }
        if (depth == 0 || no_moves_left || !timer.is_time_remaining(duration)) {
            auto score = state.calc_score(color, depth + 1);
            return std::make_pair(score, Game::Move{});
        }
    }
    int maxEval = -INF;
    auto best_move = state.get_moves()[0];
    for (const auto &mov : state.get_moves()) {
        auto temp_state = state.sim_move(mov);
        auto [val, move] = simulate(temp_state, timer, duration, depth - 1, -beta, -alpha, -color);
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

Game::Move Negamax::do_choose_move(Game::GameState auto &state,
                                   const Timer::milliseconds_t &duration) const & {
    auto best_move = state.get_moves()[0];
    const auto timer = Timer::Timer();
    int depth = 1;
    while (timer.is_time_remaining(duration)) {
        auto [unused, move] = simulate(state, timer, duration, depth);
        if (!timer.is_time_remaining(duration)) {
            break;
        }
        state.bring_to_first(move);
        best_move = move;
        depth++;
    }
    return best_move;
}
} // namespace NEGAMAX

#include "Tic_Tac_Toe.hpp"

template Game::Move
NEGAMAX::Negamax::do_choose_move<Tic_Tac_Toe::State>(Tic_Tac_Toe::State &state,
                                                     const Timer::milliseconds_t &duration) const &;

#include "Ultimate_Tic_Tac_Toe.hpp"

template Game::Move NEGAMAX::Negamax::do_choose_move<Ultimate_Tic_Tac_Toe::State>(
    Ultimate_Tic_Tac_Toe::State &state, const Timer::milliseconds_t &duration) const &;
