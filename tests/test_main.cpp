#include "ttt.hpp"
#include <cassert>

int main() {
    constexpr auto X = TTT::State::Player{TTT::State::Player::Mark::X};
    constexpr auto O = TTT::State::Player{TTT::State::Player::Mark::O};
    constexpr auto NONE = TTT::State::Player{TTT::State::Player::Mark::None};

    {
        TTT::State game{};
        game.moveTo({0, 0});
        game.moveTo({0, 1});
        game.moveTo({1, 0});
        game.moveTo({0, 2});
        game.moveTo({2, 0});
        assert(game.getWinner() == X);
    }

    {
        TTT::State game{};
        game.moveTo({0, 0});
        game.moveTo({1, 0});
        game.moveTo({0, 1});
        game.moveTo({1, 2});
        game.moveTo({0, 2});
        assert(game.getWinner() == X);
    }

    {
        TTT::State game{};
        game.moveTo({0, 0});
        game.moveTo({1, 0});
        game.moveTo({1, 1});
        game.moveTo({1, 2});
        game.moveTo({2, 2});
        assert(game.getWinner() == X);
    }

    {
        TTT::State game{};
        game.moveTo({1, 1});
        game.moveTo({0, 0});
        game.moveTo({0, 1});
        game.moveTo({1, 0});
        game.moveTo({0, 2});
        game.moveTo({2, 0});
        assert(game.getWinner() == O);
    }

    {
        TTT::State game{};
        game.moveTo({2, 2});
        game.moveTo({0, 0});
        game.moveTo({1, 0});
        game.moveTo({0, 1});
        game.moveTo({1, 2});
        game.moveTo({0, 2});
        assert(game.getWinner() == O);
    }

    {
        TTT::State game{};
        game.moveTo({0, 1});
        game.moveTo({0, 0});
        game.moveTo({1, 0});
        game.moveTo({1, 1});
        game.moveTo({1, 2});
        game.moveTo({2, 2});
        assert(game.getWinner() == O);
    }

    {
        TTT::State game1{};
        game1.moveTo({0, 0});
        game1.moveTo({0, 1});
        game1.moveTo({1, 0});
        game1.moveTo({0, 2});
        game1.moveTo({2, 0});

        TTT::State game2{};
        game2.moveTo({1, 0});
        game2.moveTo({0, 2});
        game2.moveTo({0, 0});
        game2.moveTo({0, 1});
        game2.moveTo({2, 0});

        assert(game1 == game2);
    }
    return 0;
}
