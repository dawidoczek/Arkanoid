//
// Created by Dawid Rej on 04/09/2024.
//
#include "game_logic.h"
#include <algorithm> // For std::all_of
#include <cstdlib>   // For rand()

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int BALL_SIZE = 10;
const int BRICK_W = 60;
const int BRICK_H = 20;
const int PADDLE_W = 100;
const int PADDLE_H = 20;
const int BALL_CD = 5;

Game::Game()
    : paddle{SCREEN_W / 2 - PADDLE_W / 2, SCREEN_H - PADDLE_H - 10, 10},
      balls{Ball{SCREEN_W / 2, SCREEN_H * 0.6, 5, -5}},
      lastBallSpawnTime(0),
      ballSpawnDelay(5),
      won(false),
      doexit(false),
      redraw(true) {
    std::vector<ALLEGRO_COLOR> colors = {
        al_map_rgb(128, 128, 128),
        al_map_rgb(255, 0, 0),
        al_map_rgb(255, 255, 0),
        al_map_rgb(0, 0, 255),
        al_map_rgb(255, 0, 255),
        al_map_rgb(0, 255, 0)
    };
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 10; ++j) {
            bricks.push_back(Brick{
                static_cast<float>(j * (BRICK_W + 10) + 50),
                static_cast<float>(i * (BRICK_H + 10) + 50),
                false,
                colors[i]
            });
        }
    }
}

void Game::movePaddle(float dx) {
    paddle.x += dx;
    // Ensure paddle stays within screen bounds
    if (paddle.x < 0) paddle.x = 0;
    if (paddle.x > SCREEN_W - PADDLE_W) paddle.x = SCREEN_W - PADDLE_W;
}

void Game::spawnBalls() {
        if(lastBallSpawnTime>BALL_CD) {
            balls.push_back(Ball{paddle.x + PADDLE_W, paddle.y-50, 0, -5 });
            this->lastBallSpawnTime = 0;
        }

}

void Game::updateBalls() {
    for (auto& ball : balls) {
        ball.x += ball.dx;
        ball.y += ball.dy;

        // Check for boundary collisions
        if (ball.x <= 0 || ball.x >= SCREEN_W - BALL_SIZE) {
            ball.dx = -ball.dx;
        }
        if (ball.y <= 0) {
            ball.dy = -ball.dy;
        }
    }
}

void Game::handleCollisions() {
    for (auto& ball : balls) {
        // Paddle collision
        if (ball.x + BALL_SIZE >= paddle.x && ball.x <= paddle.x + PADDLE_W &&
            ball.y + BALL_SIZE >= paddle.y && ball.y <= paddle.y + PADDLE_H) {
            ball.dy = -ball.dy;
        }

        // Brick collision
        for (auto& brick : bricks) {
            if (!brick.destroyed &&
                ball.x + BALL_SIZE >= brick.x && ball.x <= brick.x + BRICK_W &&
                ball.y + BALL_SIZE >= brick.y && ball.y <= brick.y + BRICK_H) {
                ball.dy = -ball.dy;
                brick.destroyed = true;
                if (rand() % 5 == 0) {
                    powerUps.push_back(PowerUp{brick.x + BRICK_W / 2, brick.y, true});
                }
                break;
            }
        }
    }
}

void Game::activatePowerUp() {
    for (auto& powerUp : powerUps) {
        if (powerUp.active &&
            powerUp.y + BALL_SIZE >= paddle.y && powerUp.y <= paddle.y + PADDLE_H &&
            powerUp.x + BALL_SIZE >= paddle.x && powerUp.x <= paddle.x + PADDLE_W) {
            balls.push_back(Ball{paddle.x + PADDLE_W / 2, paddle.y - BALL_SIZE, 5, -5});
            balls.push_back(Ball{paddle.x + PADDLE_W / 2, paddle.y - BALL_SIZE, -5, -5});
            balls.push_back(Ball{paddle.x + PADDLE_W / 2, paddle.y - BALL_SIZE, 0, -5});
            powerUp.active = false;
        }
        powerUp.y += 2.5f;
    }
}

bool Game::checkWinCondition() const {
    return std::all_of(bricks.begin(), bricks.end(), [](const Brick& b) { return b.destroyed; });
}

bool Game::checkLossCondition() const {
    return std::all_of(balls.begin(), balls.end(), [](const Ball& b) { return b.y >= SCREEN_H; });
}

const std::vector<Ball>& Game::getBalls() const { return balls; }
const std::vector<Brick>& Game::getBricks() const { return bricks; }
const std::vector<PowerUp>& Game::getPowerUps() const { return powerUps; }
const Paddle& Game::getPaddle() const { return paddle; }
