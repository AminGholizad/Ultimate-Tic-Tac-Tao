#ifndef TTT2_HPP
#define TTT2_HPP
#pragma once
#include "game.hpp"
#include "player.hpp"
#include <array>
#include <cstdint>

namespace Tic_Tac_Toe_V2 {
class State : public Game::State<State> {
    using Player = Game::Player;
    using Move = Game::Move;
    using ui16 = std::uint16_t;
    using Moves = std::vector<Move>;
    struct Board {
        ui16 x_board;
        ui16 o_board;
    };

  public:
    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.board); }
    [[nodiscard]] decltype(auto) do_get_player(this auto &&self) { return (self.player); }
    [[nodiscard]] decltype(auto) do_get_winner(this auto &&self) { return (self.winner); }
    [[nodiscard]] decltype(auto) do_get_moves(this auto &&self) { return (self.valid_moves); }

    [[nodiscard]] constexpr bool do_is_over() const & { return !winner.is_none(); }
    [[nodiscard]] constexpr bool do_is_first_move() const & { return !last_move; }
    [[nodiscard]] constexpr bool do_is_draw() const & { return winner.is_draw(); }
    void do_debugBoard() const & {
        if (last_move) {
            std::cerr << player.other_player() << " moved to (" << *last_move << ")\n";
        }
        std::cerr << "-------\n";
        for (ui16 i = 0; i < 3; i++) {
            std::cerr << '|';
            for (ui16 j = 0; j < 3; j++) {
                const auto index = move2index(Move{i, j});
                if ((x_board & index) != 0U) {
                    std::cerr << Game::PlayerX << '|';
                } else if ((o_board & index) != 0U) {
                    std::cerr << Game::PlayerO << '|';
                } else {
                    std::cerr << Game::None << '|';
                }
            }
            std::cerr << "\n-------\n";
        }
        std::cerr << '\n';
    }
    void do_debugValidMoves() const & {
        std::cerr << "Your valid moves are:\n";
        for (const auto &move : valid_moves) {
            std::cerr << '(' << move << ")\n";
        }
        std::cerr << '\n';
    }
    [[nodiscard]] constexpr State do_sim_move(const Move &move) const & {
        auto copy = *this;
        copy.do_updateState(move);
        return copy;
    }
    [[nodiscard]] constexpr bool do_is_board_full() const & {
        return (board.x_board | board.o_board) == full_board;
    }
    [[nodiscard]] constexpr Player do_compute_winner(const Player &test_player) const & {
        const ui16 player_board = [&, test_player]() {
            if (test_player == Game::PlayerX) {
                return board.x_board;
            }
            // if (test_player == Game::PlayerO)
            return board.o_board;
        }();
        if (std::ranges::any_of(winMasks, [player_board](const ui16 mask) {
                return (player_board & mask) == mask;
            })) {
            return test_player;
        }
        if (do_is_board_full()) {
            return Game::Draw;
        }
        return Game::None;
    }
    [[nodiscard]] int do_calc_score(int color, int depth) const & {
        using WINS = std::pair<int, int>;
        const auto sum =
            std::ranges::fold_left(two_in_rowMasks, WINS{0, 0}, [&](WINS sums, const auto &mask) {
                if ((board.x_board & mask) == mask) {
                    sums.first++;
                }
                if ((board.o_board & mask) == mask) {
                    sums.second++;
                }
                return sums;
            });
        return color * depth * (sum.first - sum.second);
    }
    void do_updateState(const Move &move) {
        const auto index = move2index(move);
        if (player == Game::PlayerX) {
            board.x_board |= index;
        } else {
            board.o_board |= index;
        }
        last_move = move;
        winner = do_compute_winner(player);
        player = player.other_player();
        set_valid_moves(move);
    }

  private:
    Board board{.x_board = 0, .o_board = 0};
    Player player{Game::PlayerX};
    Player winner{Player::Mark::None};
    std::optional<Move> last_move{std::nullopt};
    Moves valid_moves{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};

    constexpr static std::array<ui16, 8> winMasks = {7, 56, 448, 73, 146, 292, 273, 84};
    // 7  :000000111b
    // 56 :000111000b
    // 448:111000000b
    // 73 :001001001b
    // 146:010010010b
    // 292:100100100b
    // 273:100010001b
    // 84 :001010100b
    constexpr static std::array<ui16, 24> two_in_rowMasks = {6,   5,  3,   48,  40,  24,  384, 320,
                                                             192, 72, 65,  9,   144, 130, 18,  288,
                                                             260, 36, 272, 257, 17,  80,  68,  20};
    // 6  :000000110b
    // 5  :000000101b
    // 3  :000000011b
    // 48 :000110000b
    // 40 :000101000b
    // 24 :000011000b
    // 384:110000000b
    // 320:101000000b
    // 192:011000000b
    // 72 :001001000b
    // 65 :001000001b
    // 9  :000001001b
    // 144:010010000b
    // 130:010000010b
    // 18 :000010010b
    // 288:100100000b
    // 260:100000100b
    // 36 :000100100b
    // 272:100010000b
    // 257:100000001b
    // 17 :000010001b
    // 80 :001010000b
    // 68 :001000100b
    // 20 :000010100b
    constexpr static ui16 full_board = 511;
    // 511:111111111b

    void set_valid_moves(const Move &move) {
        const auto move_index = std::ranges::find(valid_moves, move);
        if (move_index != valid_moves.end()) {
            valid_moves.erase(move_index);
        }
    }
    [[nodiscard]] static constexpr ui16 move2index(const Move move) {
        return static_cast<ui16>(1U << ((move.x * 3) + move.y));
    }
};
} // namespace Tic_Tac_Toe_V2
#endif // !TTT2_HPP
