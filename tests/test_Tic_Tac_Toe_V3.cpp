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
    auto board{73U | (6U << 9U) | Tic_Tac_Toe_V3::State::xWon |
               (7U << Tic_Tac_Toe_V3::State::last_move_start)};
    auto game = Tic_Tac_Toe_V3::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT3 col win O", "[TTT3]") {
    // O, X, X, //
    // O, E, E, //
    // O, E, E
    auto board{6U | (73U << 9U) | Tic_Tac_Toe_V3::State::oWon | Tic_Tac_Toe_V3::State::xTurn |
               (7U << Tic_Tac_Toe_V3::State::last_move_start)};
    auto game = Tic_Tac_Toe_V3::State();
    Game::moveTo(game, std::nullopt);
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}
