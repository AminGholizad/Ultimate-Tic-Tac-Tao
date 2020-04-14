#include "player.hpp"
namespace Game
{
const std::map<Player, char> Player::symbols{{X, 'X'}, {O, 'O'}, {None, '-'}, {Draw, '#'}};
std::ostream &operator<<(std::ostream &os, const Player &p)
{
    os << Player::symbols.at(p);
    return os;
}
} // namespace Game