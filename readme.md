# Arkanoid
## Made by Dawid Rej
- using c++ with allegro5
- u move with left and right arrow
- <b>features</b>
    - R to reset
    - B to cheat in balls

- to compile you need allegro 5 
```
g++ -std=c++11 main.cpp game_logic.cpp -o arkanoid `pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_primitives-5` -D_REENTRANT
```

- to write and run tests, you're on your own