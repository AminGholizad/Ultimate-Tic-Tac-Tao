#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once
#include <array>
#include <iostream>
namespace Game {
class Player {
  public:
    enum class Mark : std::uint8_t {
        None,
        Draw,
        X,
        O,

        Size
    };
    static constexpr std::array<char, static_cast<size_t>(Mark::Size)> symbols{'-', '#', 'X', 'O'};
    constexpr Player() = default;
    constexpr explicit Player(const Mark &mark_) : mark{mark_} {}
    [[nodiscard]] constexpr bool isNone() const & { return mark == Mark::None; }
    [[nodiscard]] constexpr bool isDraw() const & { return mark == Mark::Draw; }
    [[nodiscard]] constexpr Mark operator()() const & { return mark; };
    [[nodiscard]] constexpr Player otherPlayer() const & {
        return (mark == Mark::X) ? Player(Mark::O) : Player(Mark::X);
    };
    // friends
    [[nodiscard]] friend constexpr bool operator==(const Player &lhs, const Player &rhs) {
        return lhs.mark == rhs.mark;
    }
    [[nodiscard]] friend constexpr bool operator!=(const Player &lhs, const Player &rhs) {
        return lhs.mark != rhs.mark;
    }
    [[nodiscard]] friend constexpr bool operator<(const Player &lhs, const Player &rhs) {
        return lhs.mark < rhs.mark;
    }
    friend std::ostream &operator<<(std::ostream &ostream, const Player &player) {
        ostream << Player::symbols.at(static_cast<size_t>(player()));
        return ostream;
    }

  private:
    Mark mark{Mark::None};
};
} // namespace Game
#endif // !PLAYER_HPP
