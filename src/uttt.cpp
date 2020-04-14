#include "uttt.hpp"
namespace UTTT
{
bool State::operator==(State const &s) const &
{
    if (player != s.player)
        return false;
    if (lastMove != s.lastMove)
        return false;
    for (size_t i = 0; i < 9; i++)
        for (size_t j = 0; j < 9; j++)
            if (board[i][j] != s.board[i][j])
                return false;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (largeboard[i][j] != s.largeboard[i][j])
                return false;
    return true;
}
bool State::operator!=(State const &s) const &
{
    if (player == s.player)
        return false;
    if (lastMove == s.lastMove)
        return false;
    for (size_t i = 0; i < 9; i++)
        for (size_t j = 0; j < 9; j++)
            if (board[i][j] == s.board[i][j])
                return false;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            if (largeboard[i][j] == s.largeboard[i][j])
                return false;
    return true;
}
void State::debugLargeboard() const &
{
    std::cerr << "-------\n";
    for (auto &row : largeboard)
    {
        std::cerr << "|";
        for (auto &elem : row)
        {
            std::cerr << elem << "|";
        }
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::debugSubboard(int const &x, int const &y) const &
{
    std::cerr << "-------\n";
    for (auto row : {0, 1, 2})
    {
        std::cerr << "|";
        for (auto col : {0, 1, 2})
        {
            std::cerr << board[row + x][col + y] << "|";
        }
        std::cerr << "\n-------\n";
    }
    std::cerr << '\n';
}
void State::debugBoard() const &
{
    std::cerr << "-----------------------\n";
    for (auto i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            std::cerr << "-----------------------\n";
        std::cerr << "|";
        for (auto j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
                std::cerr << "|";
            std::cerr << board[i][j] << "|";
        }
        std::cerr << "|\n-----------------------\n";
    }
    std::cerr << "-----------------------\n";
} // namespace UTTT
void State::debugValidMoves() const &
{
    std::cerr << "Your valid moves are:\n";
    for (auto &move : valid_moves)
        std::cerr << '(' << move << ")\n";
    std::cerr << '\n';
}
std::pair<int, int> State::sub_win_count() const &
{
    int MEsum = 0;
    int OPsum = 0;
    for (auto i = 0; i < 3; i++)
    {
        for (auto j = 0; j < 3; j++)
        {
            if (largeboard[i][j] == player)
            {
                MEsum += 1;
            }
            else if (largeboard[i][j] == player.otherPlayer())
            {
                OPsum += 1;
            }
        }
    }
    return std::make_pair(MEsum, OPsum);
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
            {
                player = player.otherPlayer();
                valid_moves.clear();
                return;
            }
        } while (!is_valid(m));
    }
    updateState(m);
    player = player.otherPlayer();
    set_valid_moves();
}
void State::set_valid_moves()
{
    if (valid_moves.empty())
        init_valid_moves();

    else
        get_valid_moves();
}
void State::init_valid_moves()
{
    for (auto i = 0; i < 9; i++)
        for (auto j = 0; j < 9; j++)
            valid_moves.emplace_back(i, j);
}
void State::get_valid_moves()
{
    valid_moves.clear();
    int lx = lastMove.X() % 3;
    int ly = lastMove.Y() % 3;
    int sx = lx * 3;
    int sy = ly * 3;
    if (largeboard[lx][ly].isNone())
    {
        for (auto i = 0; i < 3; i++)
            for (auto j = 0; j < 3; j++)
                if (board[i + sx][j + sy].isNone())
                    valid_moves.emplace_back(i + sx, j + sy);
    }
    else
    {
        for (auto i = 0; i < 9; i++)
            for (auto j = 0; j < 9; j++)
                if (board[i][j].isNone())
                    valid_moves.emplace_back(i, j);
    }
}
bool State::is_largeboard_full() const &
{
    for (auto i = 0; i < 3; i++)
        for (auto j = 0; j < 3; j++)
            if (largeboard[i][j].isNone())
                return false;
    return true;
}
State::Player State::compute_winner(Player const &p) const &
{
    for (auto i = 0; i < 3; i++)
    {
        if (largeboard[i][0] == p && largeboard[i][1] == p && largeboard[i][2] == p)
            return p;
        if (largeboard[0][i] == p && largeboard[1][i] == p && largeboard[2][i] == p)
            return p;
    }
    if (largeboard[0][0] == p && largeboard[1][1] == p && largeboard[2][2] == p)
        return p;
    if (largeboard[0][2] == p && largeboard[1][1] == p && largeboard[2][0] == p)
        return p;
    if (is_largeboard_full())
    {
        auto [MEsum, OPsum] = sub_win_count();
        return (MEsum > OPsum) ? player : player.otherPlayer();
    }
    return Player::None;
} // namespace UTTT
bool State::is_sub_winner(int const &x, int const &y, Player const &p) const &
{
    for (auto i = 0; i < 3; i++)
    {
        if (board[i + x][y] == p && board[i + x][1 + y] == p && board[i + x][2 + y] == p)
            return true;
        if (board[x][i + y] == p && board[1 + x][i + y] == p && board[2 + x][i + y] == p)
            return true;
    }
    if (board[x][y] == p && board[1 + x][1 + y] == p && board[2 + x][2 + y] == p)
        return true;
    if (board[x][2 + y] == p && board[1 + x][1 + y] == p && board[2 + x][y] == p)
        return true;
    return false;
}
bool State::is_sub_full(int const &x, int const &y) const &
{
    for (auto i = x; i < x + 3; i++)
        for (auto j = y; j < y + 3; j++)
            if (board[i][j].isNone())
                return false;
    return true;
}
void State::fill_sub(int const &x, int const &y, Player const &p)
{
    for (auto i = x; i < x + 3; i++)
        for (auto j = y; j < y + 3; j++)
            board[i][j] = p;
}
void State::updateState(Move const &m)
{
    board[m.X()][m.Y()] = player;
    lastMove = m;
    int lx = m.X() / 3;
    int ly = m.Y() / 3;
    int sx = lx * 3;
    int sy = ly * 3;
    if (is_sub_winner(sx, sy, player))
    {
        largeboard[lx][ly] = player;
        fill_sub(sx, sy, player);
        winner = compute_winner(player);
    }
    else if (is_sub_full(sx, sy))
    {
        largeboard[lx][ly] = Player::Draw;
        fill_sub(sx, sy, Player::Draw);
        winner = compute_winner(player);
    }
}
void State::moveTo(Move const &m)
{
    updateState(m);
    std::cerr << player << " Moved to ";
    std::cout << lastMove << '\n';
    player = player.otherPlayer();
}
State State::sim_move(Move const &m) const &
{
    auto cp = *this;
    cp.updateState(m);
    cp.player = cp.player.otherPlayer();
    cp.set_valid_moves();
    return cp;
}
} // namespace UTTT
