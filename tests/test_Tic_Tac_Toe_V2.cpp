#include "Tic_Tac_Toe_V2.hpp"
#include "game.hpp"
#include "player.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto X = Game::PlayerX;
constexpr auto O = Game::PlayerO;
constexpr auto E = Game::Player{};
constexpr auto D = Game::Player{Game::Player::Mark::Draw};

TEST_CASE("TTT2 col win X", "[TTT2]") {
    // X, O, O, //
    // X, E, E, //
    // X, E, E
    Tic_Tac_Toe_V2::State::Board board{73, 6};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 row win X", "[TTT2]") {
    // {X, X, X, //
    // O, E, O, //
    // E, E, E};
    Tic_Tac_Toe_V2::State::Board board{7, 40};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{0, 2});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 diag win X", "[TTT2]") {
    // {X, E, E, //
    // O, X, O, //
    // E, E, X};
    Tic_Tac_Toe_V2::State::Board board{273, 40};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{2, 2});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 col win O", "[TTT2]") {
    // {O, X, X, //
    // O, X, E, //
    // O, E, E};
    Tic_Tac_Toe_V2::State::Board board{22, 73};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 row win O", "[TTT2]") {
    // {O, O, O, //
    // X, E, X, //
    // E, E, X};
    Tic_Tac_Toe_V2::State::Board board{296, 7};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{2, 2});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{0, 2});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 diag win O", "[TTT2]") {
    // {O, X, E, //
    // X, O, X, //
    // E, E, O};
    Tic_Tac_Toe_V2::State::Board board{42, 273};
    auto game = Tic_Tac_Toe_V2::State();
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{2, 2});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 O wins with init with a finished board", "[TTT2]") {
    // {O, X, E, //
    //  X, O, X, //
    //  E, E, O};
    Tic_Tac_Toe_V2::State::Board board{42, 273};
    auto game = Tic_Tac_Toe_V2::State(board);
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 X wins with init with a finished board", "[TTT2]") {
    // {O, O, E, //
    //  X, X, X, //
    //  E, E, O};
    Tic_Tac_Toe_V2::State::Board board{56, 259};
    auto game = Tic_Tac_Toe_V2::State(board);
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 Draw with init with a finished board", "[TTT2]") {
    // {O, X, O, //
    //  O, X, X, //
    //  X, O, O};
    Tic_Tac_Toe_V2::State::Board board{114, 397};
    auto game = Tic_Tac_Toe_V2::State(board);
    REQUIRE(game.get_winner() == D);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 No winner init with a half full board", "[TTT2]") {
    // {O, X, O, //
    //  O, E, X, //
    //  X, O, O};
    Tic_Tac_Toe_V2::State::Board board{98, 397};
    auto game = Tic_Tac_Toe_V2::State(board);
    REQUIRE(game.get_winner() == E);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT2 same board", "[TTT2]") {
    // {X, O, O, //
    //  X, E, E, //
    //  X, E, E};
    Tic_Tac_Toe_V2::State::Board board{73, 6};
    auto game1 = Tic_Tac_Toe_V2::State();
    Game::moveTo(game1, Game::Move{0, 0});
    Game::moveTo(game1, Game::Move{0, 1});
    Game::moveTo(game1, Game::Move{1, 0});
    Game::moveTo(game1, Game::Move{0, 2});
    Game::moveTo(game1, Game::Move{2, 0});

    auto game2 = Tic_Tac_Toe_V2::State();
    Game::moveTo(game2, Game::Move{1, 0});
    Game::moveTo(game2, Game::Move{0, 2});
    Game::moveTo(game2, Game::Move{0, 0});
    Game::moveTo(game2, Game::Move{0, 1});
    Game::moveTo(game2, Game::Move{2, 0});

    REQUIRE(game1 == game2);
    REQUIRE(game1.get_board() == board);
}
