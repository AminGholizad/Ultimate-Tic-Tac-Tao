#ifndef USER_MOVE_HPP
#define USER_MOVE_HPP
#pragma once

#include "game.hpp"
namespace USER_MOVE {
class User_Move : public Game::Strategy<User_Move> {
  public:
    std::optional<Game::Move> do_choose_move(Game::GameState auto &state) {
        std::optional<Game::Move> move;
        state.debugValidMoves();
        if (state.is_first_move()) {
            std::cerr << "Enter your move (-1 -1 to start as second player):\n";
        }
        switch (1) {
        case 0:
            do {
                std::cerr << "Please enter a valid move\n";
                [[fallthrough]];
            case 1:
                std::cin >> move;
                std::cin.ignore();
                if (!move && state.is_first_move()) {
                    // state.get_player() = state.get_player().other_player();
                    // state.get_moves().clear();
                    return move;
                }
            } while (!state.is_valid_move(*move));
        }
        return move;
    }
};
} // namespace USER_MOVE

#endif // !USER_MOVE_HPP
