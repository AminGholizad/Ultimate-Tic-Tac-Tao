#ifndef PLAYER_HPP
#define PLAYER_HPP
#pragma once
#include <iostream>
#include <map>
namespace Game
{
class Player
{
public:
    enum Mark : int
    {
        Draw = -1,
        None = 0,
        X = 1,
        O = 2
    };
    static const std::map<Player, char> symbols;
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
    constexpr bool isNone() const & { return mark == None; }
    constexpr bool isDraw() const & { return mark == Draw; }
    inline Mark operator()() const & { return mark; };
    constexpr Player otherPlayer() const & { return (mark == X) ? O : X; };

private:
    Mark mark;
};
} // namespace Game
#endif // !PLAYER_HPP