#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once
#include <iostream>
#include <array>
namespace Game
{
class Player
{
public:
    enum class Mark : int
    {
        None,
        Draw,
        X,
        O,

        Size
    };
    static constexpr std::array<char,static_cast<size_t>(Mark::Size)> symbols{'-', '#', 'X', 'O'};
    inline Player() = default;
    inline Player(Player const &) = default;
    inline Player(Player &&) = default;
    inline Player &operator=(Player const &) = default;
    inline Player &operator=(Player &&) = default;
    constexpr Player(const Mark &m) : mark(m) {}
    constexpr bool operator==(const Player &p) const & { return mark == p.mark; }
    constexpr bool operator!=(const Player &p) const & { return mark != p.mark; }
    constexpr bool operator<(const Player &p) const & { return mark < p.mark; }
    friend std::ostream &operator<<(std::ostream &os, const Player &p);
    constexpr bool isNone() const & { return mark == Mark::None; }
    constexpr bool isDraw() const & { return mark == Mark::Draw; }
    inline Mark operator()() const & { return mark; };
    constexpr Player otherPlayer() const & { return (mark == Mark::X) ? Mark::O : Mark::X; };
private:
    Mark mark;
};
} // namespace Game
#endif // !PLAYER_HPP
