// #include "mcts.hpp"
#include "Tic_Tac_Toe.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "game.hpp"
#include "mcts.hpp"
#include "negamax.hpp"
#include "random_move.hpp"
#include "user_move.hpp"
#include <Timer.hpp>
#include <iostream>
#include <string>
#include <vector>

constexpr Timer::milliseconds_t THOUSAND{1000};
constexpr Timer::milliseconds_t HONDRED{100};
constexpr Timer::milliseconds_t ONE{1};

void ttt_rndVSnegamax(Timer::milliseconds_t time = THOUSAND) {
    auto game = Tic_Tac_Toe::State();
    auto negamax_strategy = NEGAMAX::Negamax(time);
    auto random_strategy = RANDOM_MOVE::Random_Move();

    Game::run_game(game, negamax_strategy, random_strategy);
}
void ttt_userVSnegamax(Timer::milliseconds_t time = THOUSAND) {
    auto game = Tic_Tac_Toe::State();
    auto user = USER_MOVE::User_Move();
    auto negamax_strategy = NEGAMAX::Negamax(time);

    Game::run_game(game, user, negamax_strategy);
}
void ttt_rndVSmcts(Timer::milliseconds_t time = THOUSAND) {
    auto game = Tic_Tac_Toe::State();
    auto mcts_strategy = MCTS::Mcts<Tic_Tac_Toe::State>(time);
    auto random_strategy = RANDOM_MOVE::Random_Move();

    Game::run_game(game, mcts_strategy, random_strategy);
}
void ttt_negamaxVSnegamax(const Timer::milliseconds_t time1 = THOUSAND,
                          const Timer::milliseconds_t time2 = HONDRED + ONE) {
    auto game = Tic_Tac_Toe::State();
    auto player1_strategy = NEGAMAX::Negamax(time1);
    auto player2_strategy = NEGAMAX::Negamax(time2);

    Game::run_game(game, player1_strategy, player2_strategy);
}

void uttt_rndVSmcts(Timer::milliseconds_t time = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto mcts_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time);
    auto random_strategy = RANDOM_MOVE::Random_Move();

    Game::run_game(game, mcts_strategy, random_strategy);
}
void uttt_rndVsnegamax(Timer::milliseconds_t time = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto negamax_strategy = NEGAMAX::Negamax(time);
    auto random_strategy = RANDOM_MOVE::Random_Move();

    Game::run_game(game, negamax_strategy, random_strategy);
}
void uttt_negamaxVsnegamax(const Timer::milliseconds_t time1 = THOUSAND,
                           const Timer::milliseconds_t time2 = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto player1_strategy = NEGAMAX::Negamax(time1);
    auto player2_strategy = NEGAMAX::Negamax(time2);

    Game::run_game(game, player1_strategy, player2_strategy);
}
void uttt_mctsVSmcts(const Timer::milliseconds_t time1 = THOUSAND,
                     const Timer::milliseconds_t time2 = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto player1_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time1);
    auto player2_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time2);

    Game::run_game(game, player1_strategy, player2_strategy);
}
void uttt_userVSmcts(const Timer::milliseconds_t time = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto player1_strategy = USER_MOVE::User_Move();
    auto player2_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time);

    Game::run_game(game, player1_strategy, player2_strategy);
}
void uttt_userVSngm(const Timer::milliseconds_t time = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto player1_strategy = USER_MOVE::User_Move();
    auto player2_strategy = NEGAMAX::Negamax(time);
    std::cerr << "Enter your move (-1 -1 to start as second player):\n";
    Game::run_game(game, player1_strategy, player2_strategy);
}
void uttt_mctsVSnegamax(const Timer::milliseconds_t time1 = THOUSAND,
                        const Timer::milliseconds_t time2 = THOUSAND) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto player1_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time1);
    auto player2_strategy = NEGAMAX::Negamax(time2);
    Game::run_game(game, player1_strategy, player2_strategy);
}

int main(int argc, const char **argv) {
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
        cout << "enter ai engine (mcts, ngm) and their thinking time\n";
    }*/

    // uttt_mctsVSmcts();
    // uttt_rndVSmcts();
    // uttt_rndVsnegamax();
    // uttt_negamaxVsnegamax();
    ttt_userVSnegamax();
    return 0;
}
