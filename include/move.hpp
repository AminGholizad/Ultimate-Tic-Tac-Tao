#ifndef MOVE_HPP
#define MOVE_HPP
#pragma once
#include <iostream>
namespace Game {
class Move {
private:
  int x{0};
  int y{0};

public:
  constexpr Move() = default;
  constexpr Move(int x_in, int y_in) : x{x_in}, y{y_in} {}
  [[nodiscard]] constexpr auto X() const & { return static_cast<size_t>(x); }
  [[nodiscard]] constexpr auto Y() const & { return static_cast<size_t>(y); }

  // friends
  // refer to https://youtu.be/T08YxaCG_OY?si=YROuX5ikK8vKA0Mh
  [[nodiscard]] friend constexpr auto operator*(const Move &move,
                                                const size_t scale) {
    return std::make_pair(static_cast<size_t>(move.x) * scale,
                          static_cast<size_t>(move.y) * scale);
  }
  [[nodiscard]] friend constexpr auto operator/(const Move &move,
                                                const size_t scale) {
    return std::make_pair(static_cast<size_t>(move.x) / scale,
                          static_cast<size_t>(move.y) / scale);
  }
  [[nodiscard]] friend constexpr auto operator%(const Move &move,
                                                const size_t scale) {
    return std::make_pair(static_cast<size_t>(move.x) % scale,
                          static_cast<size_t>(move.y) % scale);
  }
  [[nodiscard]] friend constexpr bool operator==(const Move &lhs,
                                                 const Move &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }
  [[nodiscard]] friend constexpr bool operator!=(const Move &lhs,
                                                 const Move &rhs) {
    return (lhs.x != rhs.x || lhs.y != rhs.y);
  }
  friend std::ostream &operator<<(std::ostream &ostream, const Move &move) {
    ostream << move.x << ' ' << move.y;
    return ostream;
  }
  friend std::istream &operator>>(std::istream &istream, Move &move) {
    istream >> move.x >> move.y;
    return istream;
  }
};
} // namespace Game
#endif // !MOVE_HPP
