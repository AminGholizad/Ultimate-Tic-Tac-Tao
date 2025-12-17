#include "player.hpp"
#include "ttt.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TTT row win X") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 2});
    Game::moveTo(game, {2, 0});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT col win X") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {0, 2});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT diag win X") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {2, 2});
    REQUIRE(game.get_winner() == Game::PlayerX);
}

TEST_CASE("TTT row win O") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 2});
    Game::moveTo(game, {2, 0});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT col win O") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {2, 2});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {0, 2});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT diag win O") {
    auto game = TTT::Tic_Tac_Toe();
    Game::moveTo(game, {0, 1});
    Game::moveTo(game, {0, 0});
    Game::moveTo(game, {1, 0});
    Game::moveTo(game, {1, 1});
    Game::moveTo(game, {1, 2});
    Game::moveTo(game, {2, 2});
    REQUIRE(game.get_winner() == Game::PlayerO);
}

TEST_CASE("TTT same board") {
    auto game1 = TTT::Tic_Tac_Toe();
    Game::moveTo(game1, {0, 0});
    Game::moveTo(game1, {0, 1});
    Game::moveTo(game1, {1, 0});
    Game::moveTo(game1, {0, 2});
    Game::moveTo(game1, {2, 0});

    auto game2 = TTT::Tic_Tac_Toe();
    Game::moveTo(game2, {1, 0});
    Game::moveTo(game2, {0, 2});
    Game::moveTo(game2, {0, 0});
    Game::moveTo(game2, {0, 1});
    Game::moveTo(game2, {2, 0});

    REQUIRE(game1 == game2);
}
