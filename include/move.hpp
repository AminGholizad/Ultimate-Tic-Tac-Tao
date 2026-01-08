#ifndef MOVE_HPP
#define MOVE_HPP
#pragma once
#include <iostream>
namespace Game {
struct Move {
    size_t x{0};
    size_t y{0};

    constexpr Move() = default;
    constexpr Move(size_t x_in, size_t y_in) : x{x_in}, y{y_in} {}

    // friends
    // refer to https://youtu.be/T08YxaCG_OY?si=YROuX5ikK8vKA0Mh
    [[nodiscard]] friend constexpr auto operator*(const Move &move, const size_t scale) {
        return std::make_pair(move.x * scale, move.y * scale);
    }
    [[nodiscard]] friend constexpr auto operator/(const Move &move, const size_t scale) {
        return std::make_pair(move.x / scale, move.y / scale);
    }
    [[nodiscard]] friend constexpr auto operator%(const Move &move, const size_t scale) {
        return std::make_pair(move.x % scale, move.y % scale);
    }
    [[nodiscard]] friend constexpr bool operator==(const Move &lhs, const Move &rhs) = default;
    friend std::ostream &operator<<(std::ostream &ostream, const Move &move) {
        ostream << move.x << ' ' << move.y;
        return ostream;
    }
    friend std::istream &operator>>(std::istream &istream, std::optional<Move> &move) {
        int x_in{};
        int y_in{};
        istream >> x_in >> y_in;
        if (x_in < 0 || y_in < 0) {
            move = {};
        } else {
            move = {static_cast<size_t>(x_in), static_cast<size_t>(y_in)};
        }
        return istream;
    }
};
} // namespace Game
#endif // !MOVE_HPP
