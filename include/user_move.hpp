#ifndef USER_MOVE_HPP
#define USER_MOVE_HPP
#pragma once

#include "game.hpp"
namespace USER_MOVE {
class User_Move : public Game::Strategy<User_Move> {
  public:
    std::optional<Game::Move> do_choose_move(Game::GameState auto &state) {
        state.debugValidMoves();
        if (state.is_first_move()) {
            std::cerr << "Enter your move (-1 -1 to start as second player):\n";
        }

        std::optional<Game::Move> move;
        bool first = true;
        while (true) {
            if (!first) {
                std::cerr << "Please enter a valid move\n";
            }
            first = false;

            std::cin >> move;
            if (!move && state.is_first_move()) {
                return move;
            }
            if (move && state.is_valid_move(*move)) {
                return move;
            }
            std::cin.ignore();
        }
    }
};
} // namespace USER_MOVE

#endif // !USER_MOVE_HPP
