#ifndef TTT3_HPP
#define TTT3_HPP
#pragma once
#include "game.hpp"
#include "player.hpp"
#include <array>
#include <cstdint>

namespace Tic_Tac_Toe_V3 {
class State : public Game::State<State> {
    using Player = Game::Player;
    using Move = Game::Move;
    using ui32 = std::uint32_t;
    using Moves = std::vector<Move>;

  public:
    [[nodiscard]] decltype(auto) do_get_board(this auto &&self) { return (self.flags); }
    [[nodiscard]] constexpr decltype(auto) do_get_player(this auto &&self) {
        if ((self.flags & xTurn) == xTurn) {
            return (Game::PlayerX);
        }
        return (Game::PlayerO);
    }
    [[nodiscard]] constexpr decltype(auto) do_get_winner(this auto &&self) {
        if ((self.flags & xWon) == xWon) {
            return (Game::PlayerX);
        }
        if ((self.flags & oWon) == oWon) {
            return (Game::PlayerO);
        }
        if ((self.flags & Draw) == Draw) {
            return (Game::Draw);
        }
        return (Game::None);
    }
    [[nodiscard]] decltype(auto) do_get_moves(this auto &&self) { return (self.valid_moves); }

    constexpr State() = default;
    constexpr explicit State(ui32 flags_) : flags(flags_) {
        const Player player = do_get_player();
        Player winner;
        if (auto checked_winner = do_compute_winner(player); checked_winner.is_none()) {
            winner = do_compute_winner(player.other_player());
        } else {
            winner = checked_winner;
        }
        set_winner(winner);
        init_valid_moves();
    }

    [[nodiscard]] constexpr bool do_is_over() const & {
        return ((flags & (xWon | oWon | Draw)) != 0);
    }
    [[nodiscard]] constexpr bool do_is_first_move() const & { return !last_move; }
    [[nodiscard]] constexpr bool do_is_draw() const & { return ((flags & Draw) == Draw); }
    void do_debugBoard() const & {
        if (last_move) {
            std::cerr << do_get_player().other_player() << " moved to (" << *last_move << ")\n";
        }
        std::cerr << flags;
        std::cerr << "-------\n";
        for (ui32 i = 0; i < 3; i++) {
            std::cerr << '|';
            for (ui32 j = 0; j < 3; j++) {
                const auto index = move2index(Move{i, j});
                if ((flags & index) != 0U) {
                    std::cerr << Game::PlayerX << '|';
                } else if ((flags & (index << 9U)) != 0U) {
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
        return ((flags | oFlags()) & full_board) == full_board;
    }
    [[nodiscard]] constexpr Player do_compute_winner(const Player &test_player) const & {
        const ui32 player_board = [&, test_player]() {
            if (test_player == Game::PlayerX) {
                return flags;
            }
            // if (test_player == Game::PlayerO)
            return oFlags();
        }();
        if (std::ranges::any_of(XwinMasks, [player_board](const ui32 mask) {
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
        auto win_los = std::ranges::fold_left(
            Xtwo_in_rowMasks, 0,
            [Xflags = flags, Oflags = oFlags()](int Xwin_los, const auto &mask) {
                if ((Xflags & mask) == mask) {
                    Xwin_los++;
                }
                if ((Oflags & mask) == mask) {
                    Xwin_los--;
                }
                return Xwin_los;
            });
        if ((flags & xTurn) != xTurn) {
            win_los *= -1;
        }
        return color * depth * win_los;
    }
    void do_updateState(const Move &move) {
        const auto index = move2index(move);
        if ((flags & xTurn) == xTurn) {
            flags |= index;
        } else {
            flags |= (index << 9U);
        }
        last_move = move;
        Player player{Game::PlayerO};
        if ((flags & xTurn) == xTurn) {
            player = Game::PlayerX;
        }
        const auto winner = do_compute_winner(player);
        set_winner(winner);
        do_change_player();
        set_valid_moves(move);
    }
    constexpr void do_change_player() { flags ^= xTurn; }

    ///////static
    constexpr static ui32 xWon = 1U << 18U;
    constexpr static ui32 oWon = 1U << 19U;
    constexpr static ui32 Draw = 1U << 20U;
    constexpr static ui32 xTurn = 1U << 21U;

    constexpr static std::array<ui32, 8> XwinMasks = {7, 56, 448, 73, 146, 292, 273, 84};
    // 7  :000000111
    // 56 :000111000
    // 448:111000000
    // 73 :001001001
    // 146:010010010
    // 292:100100100
    // 273:100010001
    // 84 :001010100
    constexpr static std::array<ui32, 24> Xtwo_in_rowMasks = {6,   5,  3,   48,  40,  24,  384, 320,
                                                              192, 72, 65,  9,   144, 130, 18,  288,
                                                              260, 36, 272, 257, 17,  80,  68,  20};
    // 6  :000000110
    // 5  :000000101
    // 3  :000000011
    // 48 :000110000
    // 40 :000101000
    // 24 :000011000
    // 384:110000000
    // 320:101000000
    // 192:011000000
    // 72 :001001000
    // 65 :001000001
    // 9  :000001001
    // 144:010010000
    // 130:010000010
    // 18 :000010010
    // 288:100100000
    // 260:100000100
    // 36 :000100100
    // 272:100010000
    // 257:100000001
    // 17 :000010001
    // 80 :001010000
    // 68 :001000100
    // 20 :000010100
    constexpr static ui32 full_board = 511;
    // 511:111111111
  private:
    ui32 flags{xTurn};
    // xTurn,Draw,Owon,Xwon,Opositions(9),Xpositions(9)
    // 21   ,  20,  19,  18,     17  -  9,      8  -  0
    std::optional<Move> last_move{std::nullopt};
    Moves valid_moves{{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};

    void set_valid_moves(const Move &move) {
        const auto move_index = std::ranges::find(valid_moves, move);
        if (move_index != valid_moves.end()) {
            valid_moves.erase(move_index);
        }
    }
    void init_valid_moves() {
        for (ui32 i = 0U; i < 3U * 3U; i++) {
            if (((flags | oFlags()) & (1U << i)) == 0U) {
                valid_moves.push_back(index2move(i));
            }
        }
    }
    void set_winner(const Player winner) {
        if (winner == Game::PlayerX) {
            flags |= xWon;
        } else if (winner == Game::PlayerO) {
            flags |= oWon;
        } else if (winner == Game::Draw) {
            flags |= Draw;
        }
    }
    [[nodiscard]] static constexpr ui32 move2index(const Move move) {
        return static_cast<ui32>(1U << ((move.x * 3U) + move.y));
    }
    [[nodiscard]] static constexpr Move index2move(const ui32 index) {
        return {index / 3U, index % 3U};
    }
    [[nodiscard]] constexpr ui32 oFlags() const & { return (flags >> 9U); }
};
} // namespace Tic_Tac_Toe_V3
#endif // !TTT3_HPP
