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
    [[nodiscard]] constexpr bool is_none() const & { return mark == Mark::None; }
    [[nodiscard]] constexpr bool is_draw() const & { return mark == Mark::Draw; }
    [[nodiscard]] constexpr Mark operator()() const & { return mark; };
    [[nodiscard]] constexpr Player other_player() const & {
        return (mark == Mark::X) ? Player{Mark::O} : Player{Mark::X};
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
constexpr auto PlayerX = Player{Player::Mark::X};
constexpr auto PlayerO = Player{Player::Mark::O};
} // namespace Game
#endif // !PLAYER_HPP
