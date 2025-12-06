#include "mcts.hpp"
#include "negamax.hpp"
#include "uttt.hpp"
#include <iostream>
#include <string>
#include <vector>

constexpr int THOUSAND = 1000;
constexpr int HONDRED = 100;

void mctsVSmcts(int time1 = THOUSAND, int time2 = HONDRED);
void userVSmcts(int time = THOUSAND);

void userVSngm(int time = THOUSAND);
void ngmVSngm(int time1 = THOUSAND, int time2 = HONDRED);
void mctsVSngm(int time1 = HONDRED, int time2 = 2 * THOUSAND);

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
  mctsVSngm();
  return 0;
}
void mctsVSmcts(int time1, int time2) {
  auto tmp = MCTS::Node<UTTT::State>().Ptr();
  tmp->debugBoard();
  int time = time1;
  while (!tmp->isOver()) {
    tmp = tmp->choose_move(time);
    tmp->debugBoard();
    tmp->reset();
    time = (time == time1) ? time2 : time1;
  }
  tmp->debugLargeboard();
  if (auto winner = tmp->getWinner(); !winner.isDraw()) {
    std::cout << winner << " wins!\n";
  } else {
    std::cout << "It's a Draw!\n";
  }
}
void userVSmcts(int time) {
  auto tmp = MCTS::Node<UTTT::State>().Ptr();
  tmp->debugBoard();
  std::cerr << "Enter your move (-1 -1 to start as second player):\n";
  while (!tmp->isOver()) {
    tmp = tmp->userMove();
    tmp->debugBoard();
    if (tmp->isOver()) {
      break;
    }
    tmp = tmp->choose_move(time);
    tmp->debugBoard();
    tmp->reset();
  }
  tmp->debugLargeboard();
  if (auto winner = tmp->getWinner(); !winner.isDraw()) {
    std::cout << winner << " wins!\n";
  } else {
    std::cout << "It's a Draw!\n";
  }
}

void userVSngm(int time) {
  auto tmp = NEGAMAX::Negamax<UTTT::State>();
  tmp.debugBoard();
  std::cerr << "Enter your move (-1 -1 to start as second player):\n";
  while (!tmp.isOver()) {
    tmp = tmp.userMove();
    tmp.debugBoard();
    if (tmp.isOver()) {
      break;
    }
    tmp = tmp.choose_move(time);
    tmp.debugBoard();
  }
  tmp.debugLargeboard();
  if (auto winner = tmp.getWinner(); !winner.isDraw()) {
    std::cout << winner << " wins!\n";
  } else {
    std::cout << "It's a Draw!\n";
  }
}
void ngmVSngm(int time1, int time2) {
  auto tmp = NEGAMAX::Negamax<UTTT::State>();
  tmp.debugBoard();
  int time = time1;
  while (!tmp.isOver()) {
    tmp = tmp.choose_move(time);
    tmp.debugBoard();
    time = (time == time1) ? time2 : time1;
  }
  tmp.debugLargeboard();
  if (auto winner = tmp.getWinner(); !winner.isDraw()) {
    std::cout << winner << " wins!\n";
  } else {
    std::cout << "It's a Draw!\n";
  }
}
void mctsVSngm(int time1, int time2) {
  auto state = UTTT::State{};
  auto mcts_bot = MCTS::Node(state).Ptr();
  auto ngm_bot = NEGAMAX::Negamax(state);
  state.debugBoard();
  while (!state.isOver()) {
    std::cerr << "mcts: \n";
    state = mcts_bot->choose_move(time1)->getState();
    ngm_bot = NEGAMAX::Negamax(state);
    // state.debugBoard();
    if (state.isOver()) {
      break;
    }
    std::cerr << "ngm: \n";
    state = ngm_bot.choose_move(time2).getState();
    mcts_bot = MCTS::Node(state).Ptr();
    // state.debugBoard();
  }
  state.debugLargeboard();
  if (auto winner = state.getWinner(); !winner.isDraw()) {
    std::cout << winner << " wins!\n";
  } else {
    std::cout << "It's a Draw!\n";
  }
}
