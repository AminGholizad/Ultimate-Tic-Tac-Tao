#include "Tic_Tac_Toe.hpp"
#include <iostream>
#include <ranges>
namespace Tic_Tac_Toe {
void State::do_debugBoard() const & {
    if (last_move != Move({-1, -1})) {
        std::cerr << player.other_player() << " moved to (" << last_move << ")\n";
    }
    std::cerr << "-------\n";
    for (const auto &row : board) {
        std::cerr << '|';
        for (const auto &cell : row) {
            std::cerr << cell << '|';
        }
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::do_debugValidMoves() const & {
    std::cerr << "Your valid moves are:\n";
    for (const auto &move : valid_moves) {
        std::cerr << '(' << move << ")\n";
    }
    std::cerr << '\n';
}

void State::set_valid_moves() {
    valid_moves.clear();
    for (const auto &[x, row] : std::views::enumerate(board)) {
        for (const auto &[y, cell] : std::views::enumerate(row)) {
            if (cell.is_none()) {
                valid_moves.emplace_back(x, y);
            }
        }
    }
}
Game::Player State::do_compute_winner(const Game::Player &test_player) const & {
    for (auto i = 0ULL; i < 3; ++i) {
        if (board[i][0] == test_player && board[i][1] == test_player &&
            board[i][2] == test_player) {
            return test_player;
        }
        if (board[0][i] == test_player && board[1][i] == test_player &&
            board[2][i] == test_player) {
            return test_player;
        }
    }
    if (board[0][0] == test_player && board[1][1] == test_player && board[2][2] == test_player) {
        return test_player;
    }
    if (board[0][2] == test_player && board[1][1] == test_player && board[2][0] == test_player) {
        return test_player;
    }
    if (is_board_full()) {
        return Player{Player::Mark::Draw};
    }
    return Player{Player::Mark::None};
}
void State::do_updateState(const Move &move) {
    board[move.X()][move.Y()] = player;
    last_move = move;
    winner = do_compute_winner(player);
    player = player.other_player();
    set_valid_moves();
}
State State::do_sim_move(const Move &move) const & {
    auto state_copy = *this;
    state_copy.do_updateState(move);
    return state_copy;
}
} // namespace Tic_Tac_Toe
