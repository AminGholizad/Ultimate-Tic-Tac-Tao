#include "uttt.hpp"
namespace UTTT
{
bool State::operator==(const State &s) const &
{
    if (player != s.player)
        return false;
    if (lastMove != s.lastMove)
        return false;
    for (auto i = 0ull; i < 9; ++i)
        for (auto j = 0ull; j < 9; ++j)
            if (board[i][j] != s.board[i][j])
                return false;
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (largeboard[i][j] != s.largeboard[i][j])
                return false;
    return true;
}
bool State::operator!=(const State &s) const &
{
    return !((*this)==s);
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
void State::debugSubboard(const size_t &x, const size_t &y) const &
{
    std::cerr << "-------\n";
    for (auto row =0ull; row<3; ++row)
    {
        std::cerr << "|";
        for (auto col=0ull; col<3; ++col)
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
    for (auto i = 0ull; i < 9; ++i)
    {
        if (i % 3 == 0)
            std::cerr << "-----------------------\n";
        std::cerr << "|";
        for (auto j = 0ull; j < 9; ++j)
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
    for (auto i = 0ull; i < 3; ++i)
    {
        for (auto j = 0ull; j < 3; ++j)
        {
            if (largeboard[i][j] == player)
            {
                ++MEsum;
            }
            else if (largeboard[i][j] == player.otherPlayer())
            {
                ++OPsum;
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
        }
        while (!is_valid(m));
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
    for (auto i = 0; i < 9; ++i)
        for (auto j = 0; j < 9; ++j)
            valid_moves.emplace_back(i, j);
}
void State::get_valid_moves()
{
    valid_moves.clear();
    auto [lx, ly] = lastMove % 3;
    size_t sx = lx * 3;
    size_t sy = ly * 3;
    if (largeboard[lx][ly].isNone())
    {
        for (auto i = 0ull; i < 3; ++i)
            for (auto j = 0ull; j < 3; ++j)
                if (board[i + sx][j + sy].isNone())
                    valid_moves.emplace_back(i + sx, j + sy);
    }
    else
    {
        for (auto i = 0ull; i < 9; ++i)
            for (auto j = 0ull; j < 9; ++j)
                if (board[i][j].isNone())
                    valid_moves.emplace_back(i, j);
    }
}
bool State::is_largeboard_full() const &
{
    for (auto i = 0ull; i < 3; ++i)
        for (auto j = 0ull; j < 3; ++j)
            if (largeboard[i][j].isNone())
                return false;
    return true;
}
State::Player State::compute_winner(const Player &p) const &
{
    for (auto i = 0ull; i < 3; ++i)
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
    return Player::Mark::None;
} // namespace UTTT
bool State::is_sub_winner(const size_t &x, const size_t &y, const Player &p) const &
{
    for (auto i = 0ull; i < 3; ++i)
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
bool State::is_sub_full(const size_t &x, const size_t &y) const &
{
    for (auto i = x; i < x + 3; ++i)
        for (auto j = y; j < y + 3; ++j)
            if (board[i][j].isNone())
                return false;
    return true;
}
void State::fill_sub(const size_t &x, const size_t &y, const Player &p)
{
    for (auto i = x; i < x + 3; ++i)
        for (auto j = y; j < y + 3; ++j)
            board[i][j] = p;
}
void State::updateState(const Move &m)
{
    board[m.X()][m.Y()] = player;
    lastMove = m;
    auto [lx,ly] = m / 3;
    auto sx = lx * 3;
    auto sy = ly * 3;
    if (is_sub_winner(sx, sy, player))
    {
        largeboard[lx][ly] = player;
        fill_sub(sx, sy, player);
        winner = compute_winner(player);
    }
    else if (is_sub_full(sx, sy))
    {
        largeboard[lx][ly] = Player::Mark::Draw;
        fill_sub(sx, sy, Player::Mark::Draw);
        winner = compute_winner(player);
    }
}
void State::moveTo(const Move &m)
{
    updateState(m);
    std::cerr << player << " Moved to ";
    std::cout << lastMove << '\n';
    player = player.otherPlayer();
}
State State::sim_move(const Move &m) const &
{
    auto cp = *this;
    cp.updateState(m);
    cp.player = cp.player.otherPlayer();
    cp.set_valid_moves();
    return cp;
}
} // namespace UTTT
