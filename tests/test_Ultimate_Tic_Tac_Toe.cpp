#include "Ultimate_Tic_Tac_Toe.hpp"
#include "game.hpp"
#include "player.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto X = Game::PlayerX;
constexpr auto O = Game::PlayerO;
constexpr auto E = Game::Player{};
constexpr auto D = Game::Player{Game::Player::Mark::Draw};

TEST_CASE("UTTT row 0 win X", "[UTTT]") {
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{X, X, X, X, X, X, X, X, X, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E};
    auto game = Ultimate_Tic_Tac_Toe::State(board, {0, 8});
    REQUIRE(game.get_winner() == X);
}

TEST_CASE("UTTT row 1 win X", "[UTTT]") {
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{E, E, E, E, E, E, E, E, E, //
                                                X, X, X, X, X, X, X, X, X, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E};
    auto game = Ultimate_Tic_Tac_Toe::State(board, {1, 8});
    REQUIRE(game.get_winner() == X);
}

TEST_CASE("UTTT col 0 win X", "[UTTT]") {
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E};

    auto game = Ultimate_Tic_Tac_Toe::State(board, {8, 0});
    REQUIRE(game.get_winner() == X);
}

TEST_CASE("UTTT col 1 win X", "[UTTT]") {
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E, //
                                                E, X, E, E, E, E, E, E, E};

    auto game = Ultimate_Tic_Tac_Toe::State(board, {8, 1});
    REQUIRE(game.get_winner() == X);
}
