// #include "mcts.hpp"
#include "Tic_Tac_Toe.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "game.hpp"
#include "mcts.hpp"
#include "negamax.hpp"
#include "random_move.hpp"
#include <Timer.hpp>
#include <iostream>
#include <string>
#include <vector>

constexpr Timer::milliseconds_t THOUSAND{1000};
constexpr Timer::milliseconds_t HONDRED{100};
constexpr Timer::milliseconds_t ONE{1};

void uttt_mctsVSmcts(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = HONDRED);
void userVSmcts(Timer::milliseconds_t time = THOUSAND);

void userVSngm(Timer::milliseconds_t time = THOUSAND);
void ngmVSngm(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = HONDRED);
void mctsVSngm(Timer::milliseconds_t time1 = HONDRED, Timer::milliseconds_t time2 = 2 * THOUSAND);

void ttt(Timer::milliseconds_t time1 = THOUSAND, Timer::milliseconds_t time2 = ONE / 100);
void ttt_rndVSnegamax(Timer::milliseconds_t time = 2 * THOUSAND);
void ttt_rndVSmcts(Timer::milliseconds_t time = 2 * THOUSAND);
void uttt_rndVSmcts(Timer::milliseconds_t time = 2 * THOUSAND);
void uttt_rndVsnegamax(Timer::milliseconds_t time = 2 * THOUSAND);
void uttt_negamaxVsnegamax(Timer::milliseconds_t time1 = 10 * THOUSAND,
                           Timer::milliseconds_t time2 = 10 * THOUSAND);

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

    uttt_mctsVSmcts();
    uttt_rndVSmcts();
    uttt_rndVsnegamax();
    uttt_negamaxVsnegamax();
    //     mctsVSngm();
    return 0;
}
void ttt_rndVSnegamax(Timer::milliseconds_t time) {
    auto game = Tic_Tac_Toe::State();
    auto negamax_strategy = NEGAMAX::Negamax();
    auto random_strategy = RANDOM_MOVE::Random_Move();
    while (!game.is_over()) {
        auto move = negamax_strategy.choose_move(game, time);
        Game::moveTo(game, move);
        if (!game.is_over()) {
            move = random_strategy.choose_move(game, time);
            Game::moveTo(game, move);
        }
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
void ttt_rndVSmcts(Timer::milliseconds_t time) {
    auto game = Tic_Tac_Toe::State();
    auto mcts_strategy = MCTS::Mcts<Tic_Tac_Toe::State>();
    auto random_strategy = RANDOM_MOVE::Random_Move();
    while (!game.is_over()) {
        auto move = mcts_strategy.choose_move(game, time);
        Game::moveTo(game, move);
        if (!game.is_over()) {
            move = random_strategy.choose_move(game, time);
            Game::moveTo(game, move);
        }
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
void uttt_rndVSmcts(Timer::milliseconds_t time) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto mcts_strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>();
    auto random_strategy = RANDOM_MOVE::Random_Move();
    while (!game.is_over()) {
        auto move = mcts_strategy.choose_move(game, time);
        Game::moveTo(game, move);
        if (!game.is_over()) {
            move = random_strategy.choose_move(game, time);
            Game::moveTo(game, move);
        }
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
void uttt_rndVsnegamax(Timer::milliseconds_t time) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto negamax_strategy = NEGAMAX::Negamax();
    auto random_strategy = RANDOM_MOVE::Random_Move();
    while (!game.is_over()) {
        auto move = negamax_strategy.choose_move(game, time);
        Game::moveTo(game, move);
        if (!game.is_over()) {
            move = random_strategy.choose_move(game, time);
            Game::moveTo(game, move);
        }
    }
    game.debugBoard();
    if (const auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
void ttt(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
    auto game = Tic_Tac_Toe::State();
    auto strategy = NEGAMAX::Negamax();
    game.debugBoard();
    auto time = time1;
    while (!game.is_over()) {
        auto move = strategy.choose_move(game, time);
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
void uttt_negamaxVsnegamax(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto strategy = NEGAMAX::Negamax();
    game.debugBoard();
    auto time = time1;
    while (!game.is_over()) {
        const auto move = strategy.choose_move(game, time);
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
void uttt_mctsVSmcts(const Timer::milliseconds_t time1, const Timer::milliseconds_t time2) {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto strategy = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>();
    auto time = time1;
    while (!game.is_over()) {
        const auto move = strategy.choose_move(game, time);
        Game::moveTo(game, move);
        time = (time == time1) ? time2 : time1;
    }
    game.debugBoard();
    if (auto winner = game.get_winner(); !winner.is_draw()) {
        std::cout << winner << " wins!\n";
    } else {
        std::cout << "It's a Draw!\n";
    }
}
// void userVSmcts(const Timer::milliseconds_t time) {
//     auto tmp = MCTS::Node<UTTT::State>().ptr();
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
//     auto mcts_bot = MCTS::Node(state).ptr();
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
//         mcts_bot = MCTS::Node(state).ptr();
//         // state.debugBoard();
//     }
//     state.debugLargeboard();
//     if (auto winner = state.getWinner(); !winner.is_draw()) {
//         std::cout << winner << " wins!\n";
//     } else {
//         std::cout << "It's a Draw!\n";
//     }
// }
