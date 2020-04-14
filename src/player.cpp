#include "player.hpp"
namespace Game
{
std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << Player::symbols.at(static_cast<size_t>(p()));
    return os;
}
} // namespace Game
