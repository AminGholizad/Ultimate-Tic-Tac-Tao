#include "negamax.hpp"
#include <Timer.hpp>
namespace NEGAMAX {
constexpr int PENALTY{100};
auto Negamax::simulate(const Game::GameState auto &state, const Timer::Timer &timer, int depth,
                       int alpha, int beta, int color) const & {
    {
        auto [no_moves_left, did_I_win, did_opponent_win] = state.game_over();
        if (did_I_win || did_opponent_win) {
            return std::make_pair(
                color * (static_cast<int>(did_I_win) - static_cast<int>(did_opponent_win)) *
                    PENALTY * (depth + 1),
                Game::Move{});
        }
        if (depth == 0 || no_moves_left || !timer.is_time_remaining(time_limit)) {
            auto score = state.calc_score(color, depth + 1);
            return std::make_pair(score, Game::Move{});
        }
    }
    int maxEval = -INF;
    auto best_move = state.get_moves()[0];
    for (const auto &mov : state.get_moves()) {
        auto temp_state = state.sim_move(mov);
        auto [val, move] = simulate(temp_state, timer, depth - 1, -beta, -alpha, -color);
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

std::optional<Game::Move> Negamax::do_choose_move(Game::GameState auto &state) const & {

    const auto timer = Timer::Timer();
    auto best_move = state.get_moves()[0];
    int depth = 1;
    while (timer.is_time_remaining(time_limit)) {
        auto [unused, move] = simulate(state, timer, depth);
        state.bring_to_first(move);
        best_move = move;
        depth++;
    }
    return best_move;
}
} // namespace NEGAMAX

#include "Tic_Tac_Toe.hpp"
template std::optional<Game::Move>
NEGAMAX::Negamax::do_choose_move<Tic_Tac_Toe::State>(Tic_Tac_Toe::State &state) const &;

#include "Tic_Tac_Toe_V2.hpp"
template std::optional<Game::Move>
NEGAMAX::Negamax::do_choose_move<Tic_Tac_Toe_V2::State>(Tic_Tac_Toe_V2::State &state) const &;

#include "Tic_Tac_Toe_V3.hpp"
template std::optional<Game::Move>
NEGAMAX::Negamax::do_choose_move<Tic_Tac_Toe_V3::State>(Tic_Tac_Toe_V3::State &state) const &;

#include "Ultimate_Tic_Tac_Toe.hpp"
template std::optional<Game::Move> NEGAMAX::Negamax::do_choose_move<Ultimate_Tic_Tac_Toe::State>(
    Ultimate_Tic_Tac_Toe::State &state) const &;
