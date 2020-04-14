#include "ttt.hpp"
namespace TTT
{
bool State::operator==(const State &s) const &
{
    if (player != s.player)
        return false;
    if (lastMove != s.lastMove)
        return false;
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (board[i][j] != s.board[i][j])
                return false;
    return true;
}
bool State::operator!=(const State &s) const &
{
    if (player == s.player)
        return false;
    if (lastMove == s.lastMove)
        return false;
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (board[i][j] == s.board[i][j])
                return false;
    return true;
}
void State::debugBoard() const &
{
    if (lastMove != Move({-1, -1}))
        std::cerr << player.otherPlayer() << " moved to (" << lastMove << ")\n";
    std::cerr << "-------\n";
    for (auto &row : board)
    {
        std::cerr << '|';
        for (auto &elem : row)
            std::cerr << elem << '|';
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::debugValidMoves() const &
{
    std::cerr << "Your valid moves are:\n";
    for (auto &move : valid_moves)
        std::cerr << '(' << move << ")\n";
    std::cerr << '\n';
}
void State::userMove()
{
    Move m;
    switch (1)
    {
    case 0:
        do
        {
            std::cerr << "Please enter a valid move\n";
            [[fallthrough]];
        case 1:
            std::cin >> m;
            std::cin.ignore();
            if (m == Move({-1, -1}))
                return;
        }
        while (!is_valid(m));
    }
    updateState(m);
    set_valid_moves();
}
void State::set_valid_moves()
{
    valid_moves.clear();
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (board[i][j].isNone())
                valid_moves.emplace_back(i, j);
}
State::Player State::compute_winner(Player const &p) const &
{
    for (auto i = 0ull; i < 3; ++i)
    {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
            return p;
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p)
            return p;
    }
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p)
        return p;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p)
        return p;
    if (is_board_full())
        return Player::Mark::Draw;
    return Player::Mark::None;
}
bool State::is_board_full() const &
{
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (board[i][j].isNone())
                return false;
    return true;
}
void State::updateState(const Move &m)
{
    board[m.X()][m.Y()] = player;
    lastMove = m;
    winner = compute_winner(player);
    player = player.otherPlayer();
}
void State::moveTo(const Move &m)
{
    updateState(m);
    std::cerr << player << " Moved to :";
    std::cout << lastMove << '\n';
}
State State::sim_move(const Move &m) const &
{
    auto cp = *this;
    cp.updateState(m);
    cp.set_valid_moves();
    return cp;
}
} // namespace TTT
