#include "Tic_Tac_Toe.hpp"
#include "Ultimate_Tic_Tac_Toe.hpp"
#include "game.hpp"
#include "player.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TTT row win X") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 2});
    Game::moveTo(game, {2, 0});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT col win X") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {0, 2});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT diag win X") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {2, 2});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT row win O") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 2});
    Game::moveTo(game, {2, 0});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT col win O") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {2, 2});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {0, 2});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT diag win O") {
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {2, 2});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT same board") {
    auto game1 = Tic_Tac_Toe::State();
    Game::moveTo(game1, {0, 0});
    Game::moveTo(game1, {0, 1});
    Game::moveTo(game1, {1, 0});
    Game::moveTo(game1, {0, 2});
    Game::moveTo(game1, {2, 0});

    auto game2 = Tic_Tac_Toe::State();
    Game::moveTo(game2, {1, 0});
    Game::moveTo(game2, {0, 2});
    Game::moveTo(game2, {0, 0});
    Game::moveTo(game2, {0, 1});
    Game::moveTo(game2, {2, 0});

    REQUIRE(game1 == game2);
}

TEST_CASE("UTTT row win X") {
    constexpr auto X = Game::PlayerX;
    constexpr auto O = Game::PlayerO;
    constexpr auto E = Game::Player{};
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{E, E, E, E, E, E, X, X, E};
    Ultimate_Tic_Tac_Toe::State::Board3x3 lboard{X, X};
    auto game = Ultimate_Tic_Tac_Toe::State(board, lboard);
    game.updateState({0, 8});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("UTTT col win X") {
    constexpr auto X = Game::PlayerX;
    constexpr auto O = Game::PlayerO;
    constexpr auto E = Game::Player{};
    Ultimate_Tic_Tac_Toe::State::Board9x9 board{X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                X, E, E, E, E, E, E, E, E, //
                                                E, E, E, E, E, E, E, E, E};

    Ultimate_Tic_Tac_Toe::State::Board3x3 lboard{X, E, E, //
                                                 X, E, E, //
                                                 E, E, E};
    auto game = Ultimate_Tic_Tac_Toe::State(board, lboard);
    game.updateState({8, 0});
    REQUIRE(game.get_winner() == Game::PlayerX);
}
