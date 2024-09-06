//
// Created by Dawid Rej on 04/09/2024.
//

#include "test_catch2.h"
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "game_logic.h"

TEST_CASE("Paddle movement", "[paddle]") {
    Game game;
    game.movePaddle(10);
    REQUIRE(game.getPaddle().x == 10);
}

TEST_CASE("Ball and paddle collision", "[ball][paddle]") {
    Game game;
    // Assuming initial ball position and paddle position
    game.updateBalls();
    game.handleCollisions();
    REQUIRE_FALSE(game.getBalls().empty());
}

TEST_CASE("Power-up activation", "[powerup]") {
    Game game;
    game.activatePowerUp();
    REQUIRE(game.getBalls().size() == 3);
}

TEST_CASE("Win condition", "[win]") {
    Game game;
    // Assuming some bricks are destroyed
    REQUIRE(game.checkWinCondition() == true);
}

TEST_CASE("Loss condition", "[loss]") {
    Game game;
    // Assuming some balls have fallen below screen
    REQUIRE(game.checkLossCondition() == false);
}