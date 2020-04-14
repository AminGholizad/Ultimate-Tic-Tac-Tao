#include <vector>
#include <string>
#include "negamax.hpp"
#include "mcts.hpp"
#include "uttt.hpp"
using namespace std;

void mctsVSmcts(int t1 = 1000, int t2 = 100);
void userVSmcts(int t = 1000);

void userVSngm(int t = 1000);
void ngmVSngm(int t1 = 1000, int t2 = 100);
void mctsVSngm(int t1 = 100, int t2 = 2000);

int main(int argc, const char **argv)
{
    std::vector<std::string> args(argv, argv + argc);
    /*if (args.size() == 3)
    {
        if (args[1] == "mcts")
            userVSmcts(stoi(args[2]));
        else if (args[1] == "ngm")
            userVSngm(stoi(args[2]));
    }
    else if (args.size() == 4)
    {
        if (args[1] == "mcts")
            mctsVSmcts(stoi(args[2]), stoi(args[3]));
        else if (args[1] == "ngm")
            ngmVSngm(stoi(args[2]), stoi(args[3]));
    }
    else
    {
        cout << "enter ai engin (mcts, ngm) and their thinking time\n";
    }*/
    mctsVSngm();
    return 0;
}
void mctsVSmcts(int t1, int t2)
{
    auto tmp = MCTS::Node<UTTT::State>().Ptr();
    tmp->debugBoard();
    int t = t1;
    while (!tmp->isOver())
    {
        tmp = tmp->choose_move(t);
        tmp->debugBoard();
        tmp->reset();
        t = (t == t1) ? t2 : t1;
    }
    tmp->debugLargeboard();
    if (auto winner = tmp->getWinner(); !winner.isDraw())
        cout << winner << " wins!\n";
    else
        cout << "It's a Draw!\n";
}
void userVSmcts(int t)
{
    auto tmp = MCTS::Node<UTTT::State>().Ptr();
    tmp->debugBoard();
    std::cerr << "Enter your move (-1 -1 to start as second player):\n";
    while (!tmp->isOver())
    {
        tmp = tmp->userMove();
        tmp->debugBoard();
        if (tmp->isOver())
            break;
        tmp = tmp->choose_move(t);
        tmp->debugBoard();
        tmp->reset();
    }
    tmp->debugLargeboard();
    if (auto winner = tmp->getWinner(); !winner.isDraw())
        cout << winner << " wins!\n";
    else
        cout << "It's a Draw!\n";
}

void userVSngm(int t)
{
    auto tmp = NEGAMAX::Negamax<UTTT::State>();
    tmp.debugBoard();
    std::cerr << "Enter your move (-1 -1 to start as second player):\n";
    while (!tmp.isOver())
    {
        tmp = tmp.userMove();
        tmp.debugBoard();
        if (tmp.isOver())
            break;
        tmp = tmp.choose_move(t);
        tmp.debugBoard();
    }
    tmp.debugLargeboard();
    if (auto winner = tmp.getWinner(); !winner.isDraw())
        cout << winner << " wins!\n";
    else
        cout << "It's a Draw!\n";
}
void ngmVSngm(int t1, int t2)
{
    auto tmp = NEGAMAX::Negamax<UTTT::State>();
    tmp.debugBoard();
    int t = t1;
    while (!tmp.isOver())
    {
        tmp = tmp.choose_move(t);
        tmp.debugBoard();
        t = (t == t1) ? t2 : t1;
    }
    tmp.debugLargeboard();
    if (auto winner = tmp.getWinner(); !winner.isDraw())
        cout << winner << " wins!\n";
    else
        cout << "It's a Draw!\n";
}
void mctsVSngm(int t1, int t2)
{
    auto state = UTTT::State{};
    auto mcts_bot = MCTS::Node(state).Ptr();
    auto ngm_bot = NEGAMAX::Negamax(state);
    state.debugBoard();
    while (!state.isOver())
    {
        cerr << "mcts: \n";
        state = mcts_bot->choose_move(t1)->getState();
        ngm_bot = NEGAMAX::Negamax(state);
        //state.debugBoard();
        if (state.isOver())
            break;
        cerr << "ngm: \n";
        state = ngm_bot.choose_move(t2).getState();
        mcts_bot = MCTS::Node(state).Ptr();
        //state.debugBoard();
    }
    state.debugLargeboard();
    if (auto winner = state.getWinner(); !winner.isDraw())
        cout << winner << " wins!\n";
    else
        cout << "It's a Draw!\n";
}
