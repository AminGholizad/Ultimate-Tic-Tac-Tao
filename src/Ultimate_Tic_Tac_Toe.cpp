#include "Ultimate_Tic_Tac_Toe.hpp"
namespace Ultimate_Tic_Tac_Toe {
void State::debugLargeboard() const & {
    std::cerr << "-------\n";
    for (const auto &row : largeboard) {
        std::cerr << "|";
        for (const auto &elem : row) {
            std::cerr << elem << "|";
        }
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::debugSubboard(const size_t &x, const size_t &y) const & {
    std::cerr << "-------\n";
    for (auto row = ZERO; row < THREE; ++row) {
        std::cerr << "|";
        for (auto col = ZERO; col < THREE; ++col) {
            std::cerr << board[row + x][col + y] << "|";
        }
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::do_debugBoard() const & {
    std::cerr << "-----------------------\n";
    for (auto i = ZERO; i < NINE; ++i) {
        if (i % THREE == ZERO) {
            std::cerr << "-----------------------\n";
        }
        std::cerr << "|";
        for (auto j = ZERO; j < NINE; ++j) {
            if (j % THREE == ZERO) {
                std::cerr << "|";
            }
            std::cerr << board[i][j] << "|";
        }
        std::cerr << "|\n-----------------------\n";
    }
    std::cerr << "-----------------------\n";
}
void State::do_debugValidMoves() const & {
    std::cerr << "Your valid moves are:\n";
    for (const auto &move : valid_moves) {
        std::cerr << '(' << move << ")\n";
    }
    std::cerr << '\n';
}

bool State::is_largeboard_full() const & {
    for (auto i = ZERO; i < THREE; ++i) {
        for (auto j = ZERO; j < THREE; ++j) {
            if (largeboard[i][j].is_none()) {
                return false;
            }
        }
    }
    return true;
}
State::Player State::do_compute_winner(const Player &test_player) const & {
    for (auto i = ZERO; i < THREE; ++i) {
        if (largeboard[i][0] == test_player && largeboard[i][1] == test_player &&
            largeboard[i][2] == test_player) {
            return test_player;
        }
        if (largeboard[0][i] == test_player && largeboard[1][i] == test_player &&
            largeboard[2][i] == test_player) {
            return test_player;
        }
    }
    if (largeboard[0][0] == test_player && largeboard[1][1] == test_player &&
        largeboard[2][2] == test_player) {
        return test_player;
    }
    if (largeboard[0][2] == test_player && largeboard[1][1] == test_player &&
        largeboard[2][0] == test_player) {
        return test_player;
    }
    if (is_largeboard_full()) {
        auto [MEsum, OPsum] = sub_win_count();
        return (MEsum > OPsum) ? player : player.other_player();
    }
    return Player{Player::Mark::None};
}

State State::do_sim_move(const Move &move) const & {
    auto copy = *this;
    copy.updateState(move);
    copy.player = copy.player.other_player();
    return copy;
}
} // namespace Ultimate_Tic_Tac_Toe
