#include "Tic_Tac_Toe_V3.hpp"
#include "game.hpp"
#include "player.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto X = Game::PlayerX;
constexpr auto O = Game::PlayerO;
constexpr auto E = Game::Player{};
constexpr auto D = Game::Player{Game::Player::Mark::Draw};

TEST_CASE("TTT3 col win X", "[TTT3]") {
    // X, O, O, //
    // X, E, E, //
    // X, E, E
    auto board{73 | (6 << 9U) | Tic_Tac_Toe_V3::State::xWon};
    auto game = Tic_Tac_Toe_V3::State();
    game.debugBoard();
    Game::moveTo(game, Game::Move{0, 0});
    game.debugBoard();
    Game::moveTo(game, Game::Move{0, 1});
    game.debugBoard();
    Game::moveTo(game, Game::Move{1, 0});
    game.debugBoard();
    Game::moveTo(game, Game::Move{0, 2});
    game.debugBoard();
    Game::moveTo(game, Game::Move{2, 0});
    game.debugBoard();
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}
