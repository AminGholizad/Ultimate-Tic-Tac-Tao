#ifndef MOVE_HPP
#define MOVE_HPP
#include <iostream>
namespace Game
{
class Move
{
private:
    int x{0};
    int y{0};

public:
    inline Move() = default;
    inline ~Move() = default;
    inline Move(Move const &) = default;
    inline Move(Move &&) = default;
    inline Move &operator=(Move const &) = default;
    inline Move &operator=(Move &&) = default;
    inline Move(int x, int y) : x(x), y(y) {}
    constexpr int X() const & { return x; }
    constexpr int Y() const & { return y; }
    constexpr bool operator==(const Move &m) const { return (x == m.x && y == m.y); }
    constexpr bool operator!=(const Move &m) const { return (x != m.x && y != m.y); }
    friend std::ostream &operator<<(std::ostream &os, const Move &m);
    friend std::istream &operator>>(std::istream &is, Move &m);
};
} // namespace Game
#endif // !MOVE_HPP