#ifndef RANDOM_MOVE_HPP
#define RANDOM_MOVE_HPP
#pragma once
#include "game.hpp"
#include <Random-Helper.hpp>
namespace RANDOM_MOVE {
class Random_Move : public Game::Strategy<Random_Move> {
  public:
    Game::Move do_choose_move(Game::GameState auto &state,
                              const Timer::milliseconds_t &unused_param) const & {
        (void)unused_param;
        return rnd::select_randomly_value(state.get_moves());
    }
};
} // namespace RANDOM_MOVE
#endif // !RANDOM_MOVE_HPP
