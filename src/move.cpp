#include "move.hpp"
namespace Game
{
std::ostream &operator<<(std::ostream &os, const Move &m)
{
    os << m.x << ' ' << m.y;
    return os;
}
std::istream &operator>>(std::istream &is, Move &m)
{
    is >> m.x >> m.y;
    return is;
}
} // namespace Game