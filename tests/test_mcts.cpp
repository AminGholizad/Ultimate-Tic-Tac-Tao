#include "Tic_Tac_Toe.hpp"
#include "Tic_Tac_Toe_V2.hpp"
#include "Tic_Tac_Toe_V3.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "mcts.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("mcts strategy chooses a valid move within time limit for UTTT", "[MCTS]") {
    auto time_limit = Timer::milliseconds_t{100};
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto mcts_strategy1 = MCTS::Mcts<Ultimate_Tic_Tac_Toe::State>(time_limit);
    auto timer = Timer::Timer{};
    auto move = mcts_strategy1.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
TEST_CASE("mcts strategy chooses a valid move within time limit for TTT", "[MCTS]") {
    auto game = Tic_Tac_Toe::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto mcts_strategy2 = MCTS::Mcts<Tic_Tac_Toe::State>(time_limit);
    auto timer = Timer::Timer{};
    auto move = mcts_strategy2.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
TEST_CASE("mcts strategy chooses a valid move within time limit for TTT2", "[MCTS]") {
    auto game = Tic_Tac_Toe_V2::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto mcts_strategy3 = MCTS::Mcts<Tic_Tac_Toe_V2::State>(time_limit);
    auto timer = Timer::Timer{};
    auto move = mcts_strategy3.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}

TEST_CASE("mcts strategy chooses a valid move within time limit for TTT3", "[MCTS]") {
    auto game = Tic_Tac_Toe_V3::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto mcts_strategy3 = MCTS::Mcts<Tic_Tac_Toe_V3::State>(time_limit);
    auto timer = Timer::Timer{};
    auto move = mcts_strategy3.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
