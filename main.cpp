#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "game_logic.h"
#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()

const int SCREEN_W = 800;
const int SCREEN_H = 600;

void draw_message(const std::string& message, float x, float y, ALLEGRO_COLOR color) {
    const int CHAR_WIDTH = 20;
    const int CHAR_HEIGHT = 30;
    srand(time(nullptr));


    al_draw_filled_rectangle(x - 10, y - CHAR_HEIGHT / 2 - 10, x + CHAR_WIDTH * message.size() + 10, y + CHAR_HEIGHT / 2 + 10, al_map_rgb(0, 0, 0));

    for (int i = 0; i < message.size(); ++i) {
        int char_x = x + i * CHAR_WIDTH*2;
        switch (message[i]) {
    case 'Y': case 'y':
        al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x, y, char_x + CHAR_WIDTH / 2, y - CHAR_HEIGHT / 2, color, 2);
        break;
    case 'O': case 'o':
        al_draw_circle(char_x + CHAR_WIDTH / 2, y, CHAR_HEIGHT / 2, color, 2);
        break;
    case 'U': case 'u':
        al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x, y - CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2);
        break;
            case 'W': case 'w':
                // Draw the 'W' shape using 4 lines
                al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x, y - CHAR_HEIGHT / 2, color, 2); // Left vertical line
            al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH / 4, y - CHAR_HEIGHT / 4, color, 2); // Left diagonal up
            al_draw_line(char_x + CHAR_WIDTH / 4, y - CHAR_HEIGHT / 4, char_x + 3 * CHAR_WIDTH / 4, y - CHAR_HEIGHT / 4, color, 2); // Middle horizontal
            al_draw_line(char_x + 3 * CHAR_WIDTH / 4, y - CHAR_HEIGHT / 4, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2); // Right diagonal down
            al_draw_line(char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2); // Right vertical line
            break;


            case 'N': case 'n':
    al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x, y + CHAR_HEIGHT / 2, color, 2);                // Left vertical line
            al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);    // Diagonal line
            al_draw_line(char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2); // Right vertical line
            break;

    case 'A': case 'a':
        al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH / 2, y - CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH / 2, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH / 2, y, char_x, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH / 2, y, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);
        break;
            case 'S': case 's':
            al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2);
            al_draw_line(char_x, y, char_x + CHAR_WIDTH, y, color, 2); // Middle line
            al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2); // Bottom line
            al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x, y, color, 2); // Left vertical line (top half)
            al_draw_line(char_x + CHAR_WIDTH, y, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2); // Right vertical line (bottom half)
            break;

    case 'E': case 'e':
        al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x, y, char_x + CHAR_WIDTH, y, color, 2);
        al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x, y + CHAR_HEIGHT / 2, color, 2);
        break;
    case 'T': case 't':
        al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH / 2, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH / 2, y + CHAR_HEIGHT / 2, color, 2);
        break;
    case 'I': case 'i':
        al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y - CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x + CHAR_WIDTH / 2, y - CHAR_HEIGHT / 2, char_x + CHAR_WIDTH / 2, y + CHAR_HEIGHT / 2, color, 2);
        al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2);
        break;
            case 'L': case 'l':
            al_draw_line(char_x, y - CHAR_HEIGHT / 2, char_x, y + CHAR_HEIGHT / 2, color, 2); // Vertical line
            al_draw_line(char_x, y + CHAR_HEIGHT / 2, char_x + CHAR_WIDTH, y + CHAR_HEIGHT / 2, color, 2); // Horizontal line at the bottom
            break;
            default:
                break;


        }

    }
}

int real_main(int argc, char **argv) {
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_W, SCREEN_H);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_KEYBOARD_STATE keyState;

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    Game game;

    al_start_timer(timer);

    bool redraw = true;
    bool doexit = false;

    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        game.lastBallSpawnTime++;
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_get_keyboard_state(&keyState);

            if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
                game.movePaddle(-game.getPaddle().speed);
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
                game.movePaddle(game.getPaddle().speed);
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_R)) {
                // Restart the game logic
                game = Game();
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_B)) {
                game.spawnBalls();
            }

            game.updateBalls();
            game.handleCollisions();
            game.activatePowerUp();

            if (game.checkLossCondition()) {
                doexit = true;
            }
            if (game.checkWinCondition()) {
                doexit = true;
            }

            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            const Paddle& paddle = game.getPaddle();
            al_draw_filled_rectangle(paddle.x, paddle.y, paddle.x + 100, paddle.y + 20, al_map_rgb(255, 255, 255));

            for (const auto& ball : game.getBalls()) {
                al_draw_filled_circle(ball.x, ball.y, 10, al_map_rgb(255, 0, 0));
            }

            for (const auto& powerUp : game.getPowerUps()) {
                if (powerUp.active) {
                    al_draw_filled_rectangle(powerUp.x, powerUp.y, powerUp.x + 20, powerUp.y + 20, al_map_rgb(0, 255, 0));
                }
            }

            for (const auto& brick : game.getBricks()) {
                if (!brick.destroyed) {
                    al_draw_filled_rectangle(brick.x, brick.y, brick.x + 60, brick.y + 20, brick.color);
                }
            }

            if (game.checkLossCondition()) {
                draw_message("You Lose", SCREEN_W / 3, SCREEN_H / 2, al_map_rgb(255, 0, 0));
            }
            if (game.checkWinCondition()) {
                draw_message("You Win", SCREEN_W / 3, SCREEN_H / 2, al_map_rgb(0, 255, 0));
            }

            al_flip_display();
        }
    }
    al_rest(5.0);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}
int main(int argc, char **argv) {
    return real_main(argc, argv);
}