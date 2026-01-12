#include "Tic_Tac_Toe.hpp"
#include "Tic_Tac_Toe_V2.hpp"
#include "Tic_Tac_Toe_V3.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "random_move.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("random strategy chooses a valid move UTTT", "[Random]") {
    auto random_strategy = RANDOM_MOVE::Random_Move();

    auto game_uttt = Ultimate_Tic_Tac_Toe::State();
    auto move = random_strategy.choose_move(game_uttt);
    REQUIRE(game_uttt.is_valid_move(move));
}

TEST_CASE("random strategy chooses a valid move TTT", "[Random]") {
    auto random_strategy = RANDOM_MOVE::Random_Move();
    auto game_ttt = Tic_Tac_Toe::State();
    auto move = random_strategy.choose_move(game_ttt);
    REQUIRE(game_ttt.is_valid_move(move));
}

TEST_CASE("random strategy chooses a valid move TTT2", "[Random]") {
    auto random_strategy = RANDOM_MOVE::Random_Move();
    auto game_ttt = Tic_Tac_Toe_V2::State();
    auto move = random_strategy.choose_move(game_ttt);
    REQUIRE(game_ttt.is_valid_move(move));
}

TEST_CASE("random strategy chooses a valid move TTT3", "[Random]") {
    auto random_strategy = RANDOM_MOVE::Random_Move();
    auto game_ttt = Tic_Tac_Toe_V3::State();
    auto move = random_strategy.choose_move(game_ttt);
    REQUIRE(game_ttt.is_valid_move(move));
}
