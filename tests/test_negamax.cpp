#include "Tic_Tac_Toe.hpp"
#include "Tic_Tac_Toe_V2.hpp"
#include "Tic_Tac_Toe_V3.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "negamax.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("negamax strategy chooses a valid move within time limit for UTTT", "[NEGAMAX]") {
    auto game = Ultimate_Tic_Tac_Toe::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto negamax_strategy = NEGAMAX::Negamax(time_limit);
    auto timer = Timer::Timer{};
    auto move = negamax_strategy.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
TEST_CASE("negamax strategy chooses a valid move within time limit for TTT", "[NEGAMAX]") {
    auto game = Tic_Tac_Toe::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto negamax_strategy = NEGAMAX::Negamax(time_limit);
    auto timer = Timer::Timer{};
    auto move = negamax_strategy.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
TEST_CASE("negamax strategy chooses a valid move within time limit for TTT2", "[NEGAMAX]") {
    auto game = Tic_Tac_Toe_V2::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto negamax_strategy = NEGAMAX::Negamax(time_limit);
    auto timer = Timer::Timer{};
    auto move = negamax_strategy.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
TEST_CASE("negamax strategy chooses a valid move within time limit for TTT3", "[NEGAMAX]") {
    auto game = Tic_Tac_Toe_V3::State();
    auto time_limit = Timer::milliseconds_t{100};
    auto negamax_strategy = NEGAMAX::Negamax(time_limit);
    auto timer = Timer::Timer{};
    auto move = negamax_strategy.choose_move(game);
    auto time = timer.elapsed();
    REQUIRE(game.is_valid_move(move));
    REQUIRE(time < time_limit);
}
