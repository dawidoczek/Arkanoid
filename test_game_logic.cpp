//
// Created by Dawid Rej on 04/09/2024.
//

#include "test_game_logic.h"
#include <gtest/gtest.h>
#include "game_logic.h"
class GameTest : public ::testing::Test {
protected:
    Game game;

    void SetUp() override {
        game.getPowerUps().clear();
        game.getBalls().clear();
        game.getBricks().clear();
        game = Game();
    }
};

TEST_F(GameTest, InitialState) {
    EXPECT_EQ(game.getBalls().size(), 1); // Initially 1 ball
    EXPECT_FALSE(game.getBricks().empty()); // Bricks should not be empty
}

// Test moving the paddle
TEST_F(GameTest, PaddleMovement) {
    Paddle initialPaddle = game.getPaddle();
    game.movePaddle(15.0f);

    Paddle newPaddle = game.getPaddle();
    EXPECT_GT(newPaddle.x, initialPaddle.x);

    game.movePaddle(-20.0f);
    newPaddle = game.getPaddle();
    EXPECT_LT(newPaddle.x, initialPaddle.x);

    game.movePaddle(-1000.0f);
    EXPECT_EQ(game.getPaddle().x, 0);

    game.movePaddle(1000.0f);
    EXPECT_EQ(game.getPaddle().x, 1 - 100);
}

TEST_F(GameTest, BallPaddleCollision) {
    Ball testBall = { game.getPaddle().x + 50, game.getPaddle().y - 10, 0, -5 };
    game.getBalls().push_back(testBall);

    game.updateBalls();
    game.handleCollisions();

    EXPECT_LT(testBall.dy, 0);
}

TEST_F(GameTest, BallBrickCollision) {
    Ball testBall = { 60.0f, 60.0f, 0, -5 };
    Brick testBrick = { 50.0f, 50.0f, false, al_map_rgb(255, 0, 0) };

    game.getBalls().push_back(testBall);
    game.getBricks().push_back(testBrick);

    game.updateBalls();
    game.handleCollisions();

    EXPECT_TRUE(game.getBricks()[0].destroyed);
    EXPECT_LT(testBall.dy, 0);
}

// Test power-up activation
TEST_F(GameTest, PowerUpActivation) {
    PowerUp powerUp = { game.getPaddle().x + 50, game.getPaddle().y - 10, true };
    game.getPowerUps().push_back(powerUp);

    game.getBalls().push_back(Ball{ game.getPaddle().x + 50, game.getPaddle().y - 50, 0, -5 });

    game.activatePowerUp();

    EXPECT_TRUE(game.getBalls().size() > 1); // Expect more balls after activation
}

TEST_F(GameTest, WinCondition) {
    for (auto& brick : game.getBricks()) {
        brick.destroyed = true;
    }

    EXPECT_TRUE(game.checkWinCondition());
}

TEST_F(GameTest, LossCondition) {
    // Set up a  state where all balls are below the screen
    for (auto& ball : game.getBalls()) {
        ball.y = 600 + 1; // Ball is below the screen
    }

    EXPECT_TRUE(game.checkLossCondition()); // Should return true
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
