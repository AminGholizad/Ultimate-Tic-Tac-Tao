#include "Tic_Tac_Toe.hpp"
#include "game.hpp"
#include "player.hpp"
#include <catch2/catch_test_macros.hpp>

constexpr auto X = Game::PlayerX;
constexpr auto O = Game::PlayerO;
constexpr auto E = Game::Player{};
constexpr auto D = Game::Player{Game::Player::Mark::Draw};

TEST_CASE("TTT col win X", "[TTT]") {
    Tic_Tac_Toe::State::Board board{X, O, O, //
                                    X, E, E, //
                                    X, E, E};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT row win X", "[TTT]") {
    Tic_Tac_Toe::State::Board board{X, X, X, //
                                    O, E, O, //
                                    E, E, E};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{0, 2});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT diag win X", "[TTT]") {
    Tic_Tac_Toe::State::Board board{X, E, E, //
                                    O, X, O, //
                                    E, E, X};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{2, 2});
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT col win O", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, X, X, //
                                    O, X, E, //
                                    O, E, E};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 2});
    Game::moveTo(game, Game::Move{2, 0});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT row win O", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, O, O, //
                                    X, E, X, //
                                    E, E, X};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{2, 2});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{0, 2});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT diag win O", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, X, E, //
                                    X, O, X, //
                                    E, E, O};
    auto game = Tic_Tac_Toe::State();
    Game::moveTo(game, Game::Move{0, 1});
    Game::moveTo(game, Game::Move{0, 0});
    Game::moveTo(game, Game::Move{1, 0});
    Game::moveTo(game, Game::Move{1, 1});
    Game::moveTo(game, Game::Move{1, 2});
    Game::moveTo(game, Game::Move{2, 2});
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT O wins with init with a finished board", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, X, E, //
                                    X, O, X, //
                                    E, E, O};
    auto game = Tic_Tac_Toe::State(board);
    REQUIRE(game.get_winner() == O);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT X wins with init with a finished board", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, O, E, //
                                    X, X, X, //
                                    E, E, O};
    auto game = Tic_Tac_Toe::State(board);
    REQUIRE(game.get_winner() == X);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT Draw with init with a finished board", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, X, O, //
                                    O, X, X, //
                                    X, O, O};
    auto game = Tic_Tac_Toe::State(board);
    REQUIRE(game.get_winner() == D);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT No winner init with a half full board", "[TTT]") {
    Tic_Tac_Toe::State::Board board{O, X, O, //
                                    O, E, X, //
                                    X, O, O};
    auto game = Tic_Tac_Toe::State(board);
    REQUIRE(game.get_winner() == E);
    REQUIRE(game.get_board() == board);
}

TEST_CASE("TTT same board", "[TTT]") {
    Tic_Tac_Toe::State::Board board{X, O, O, //
                                    X, E, E, //
                                    X, E, E};
    auto game1 = Tic_Tac_Toe::State();
    Game::moveTo(game1, Game::Move{0, 0});
    Game::moveTo(game1, Game::Move{0, 1});
    Game::moveTo(game1, Game::Move{1, 0});
    Game::moveTo(game1, Game::Move{0, 2});
    Game::moveTo(game1, Game::Move{2, 0});

    auto game2 = Tic_Tac_Toe::State();
    Game::moveTo(game2, Game::Move{1, 0});
    Game::moveTo(game2, Game::Move{0, 2});
    Game::moveTo(game2, Game::Move{0, 0});
    Game::moveTo(game2, Game::Move{0, 1});
    Game::moveTo(game2, Game::Move{2, 0});

    REQUIRE(game1 == game2);
    REQUIRE(game1.get_board() == board);
}
