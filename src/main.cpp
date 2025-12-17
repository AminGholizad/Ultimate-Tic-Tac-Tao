// #include "mcts.hpp"
//  #include "negamax.hpp"
#include "game.hpp"
#include "ttt.hpp"
#include "uttt.hpp"
#include <Timer.hpp>
#include <iostream>
#include <string>
#include <vector>

constexpr Timer::milliseconds_t THOUSAND{1000};
constexpr Timer::milliseconds_t HONDRED{100};

// void mctsVSmcts(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = HONDRED);
// void userVSmcts(Timer::milliseconds_t time = THOUSAND);

// void userVSngm(Timer::milliseconds_t time = THOUSAND);
// void ngmVSngm(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = HONDRED);
// void mctsVSngm(Timer::milliseconds_t time1 = HONDRED, Timer::milliseconds_t time2 = 2 *
// THOUSAND);

void ttt(Timer::milliseconds_t time1 = HONDRED, Timer::milliseconds_t time2 = HONDRED);
void uttt(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = THOUSAND);

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
        cout << "enter ai engin (mcts, ngm) and their thinking time\n";
    }*/
    uttt();
    // mctsVSngm();
    return 0;
}

void ttt(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
    auto game = TTT::Tic_Tac_Toe();
    game.debugBoard();
    auto time = time1;
    while (!game.is_over()) {
        auto move = Game::choose_move(game, time);
        Game::moveTo(game, move);
        time = (time == time1) ? time2 : time1;
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
void uttt(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
    auto game = UTTT::Ultimate_Tic_Tac_Toe();
    game.debugBoard();
    auto time = time1;
    while (!game.is_over()) {
        auto move = Game::choose_move(game, time);
        Game::moveTo(game, move);
        game.debugBoard();
        time = (time == time1) ? time2 : time1;
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
// void mctsVSmcts(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
//     auto tmp = MCTS::Node<UTTT::State>().Ptr();
//     tmp->debugBoard();
//     auto time = time1;
//     while (!tmp->isOver()) {
//         tmp = tmp->choose_move(time);
//         tmp->debugBoard();
//         tmp->reset();
//         time = (time == time1) ? time2 : time1;
//     }
//     tmp->debugLargeboard();
//     if (auto winner = tmp->getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }
// void userVSmcts(const Timer::milliseconds_t time) {
//     auto tmp = MCTS::Node<UTTT::State>().Ptr();
//     tmp->debugBoard();
//     std::cerr << "Enter your move (-1 -1 to start as second player):\n";
//     while (!tmp->isOver()) {
//         tmp = tmp->userMove();
//         tmp->debugBoard();
//         if (tmp->isOver()) {
//             break;
//         }
//         tmp = tmp->choose_move(time);
//         tmp->debugBoard();
//         tmp->reset();
//     }
//     tmp->debugLargeboard();
//     if (auto winner = tmp->getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }

// void userVSngm(const Timer::milliseconds_t time) {
//     auto tmp = NEGAMAX::Negamax<UTTT::State>();
//     tmp.debugBoard();
//     std::cerr << "Enter your move (-1 -1 to start as second player):\n";
//     while (!tmp.isOver()) {
//         tmp = tmp.userMove();
//         tmp.debugBoard();
//         if (tmp.isOver()) {
//             break;
//         }
//         tmp = tmp.choose_move(time);
//         tmp.debugBoard();
//     }
//     tmp.debugLargeboard();
//     if (auto winner = tmp.getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }
// void ngmVSngm(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
//     auto tmp = NEGAMAX::Negamax<UTTT::State>();
//     tmp.debugBoard();
//     auto time = time1;
//     while (!tmp.isOver()) {
//         tmp = tmp.choose_move(time);
//         tmp.debugBoard();
//         time = (time == time1) ? time2 : time1;
//     }
//     tmp.debugLargeboard();
//     if (auto winner = tmp.getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }
// void mctsVSngm(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
//     auto state = UTTT::State{};
//     auto mcts_bot = MCTS::Node(state).Ptr();
//     auto ngm_bot = NEGAMAX::Negamax(state);
//     state.debugBoard();
//     while (!state.isOver()) {
//         std::cerr << "mcts: \n";
//         state = mcts_bot->choose_move(time1)->getState();
//         ngm_bot = NEGAMAX::Negamax(state);
//         // state.debugBoard();
//         if (state.isOver()) {
//             break;
//         }
//         std::cerr << "ngm: \n";
//         state = ngm_bot.choose_move(time2).getState();
//         mcts_bot = MCTS::Node(state).Ptr();
//         // state.debugBoard();
//     }
//     state.debugLargeboard();
//     if (auto winner = state.getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }
