//
// Created by Dawid Rej on 04/09/2024.
//

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <vector>
#include <allegro5/allegro.h>

struct Ball {
    float x, y, dx, dy;
};

struct Brick {
    float x, y;
    bool destroyed;
    ALLEGRO_COLOR color;
};

struct Paddle {
    float x, y;
    float speed;
};

struct PowerUp {
    float x, y;
    bool active;
};

class Game {
public:
    Game();

    void movePaddle(float dx);
    void updateBalls();
    void handleCollisions();
    void activatePowerUp();
    void spawnBalls();
    bool checkWinCondition() const;
    bool checkLossCondition() const;
    std::vector<Ball>& getBalls() { return balls; }
    std::vector<Brick>& getBricks() { return bricks; }
    std::vector<PowerUp>& getPowerUps() { return powerUps; }
    Paddle& getPaddle() { return paddle; }
    const std::vector<Ball>& getBalls() const;
    const std::vector<Brick>& getBricks() const;
    const std::vector<PowerUp>& getPowerUps() const;
    const Paddle& getPaddle() const;
    int lastBallSpawnTime;

private:
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Brick> bricks;
    std::vector<PowerUp> powerUps;

    int ballSpawnDelay;

    bool won;
    bool doexit;
    bool redraw;
};

#endif //GAME_LOGIC_H
