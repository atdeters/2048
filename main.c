#include <stdbool.h>
#include <ncurses.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define CHANCE_4 5

typedef struct s_data {
    uint8_t grid_size;
    uint8_t grid[5];
} Data;

typedef struct s_game {
    void(*run)(struct s_game *game);
    uint8_t(*get_rand_nb)(void);
    uint8_t(*get_rand_pos)(Data *data);
} Game;

uint8_t get_rand_nb(void) {
    return (rand() % 100 <= CHANCE_4 ? 4 : 2);
}

uint8_t get_rand_pos(Data *data) {
    return (rand() % (data->grid_size * data->grid_size));
}

void init_d(Data *data) {
    data->grid_size = 4;
}

void run(Game *game) {

    Data data = {0};
    init_d(&data);
    while(true) {
        (void)game;
        printf("Field Index = %d\n", game->get_rand_pos(&data));
        printf("Number = %d\n", game->get_rand_nb());
        usleep(500);
    }
}

void init_g(Game *game) {
    game->run = run;
    game->get_rand_nb = get_rand_nb;
    game->get_rand_pos = get_rand_pos;
    srand(time(NULL));
    // initscr();
}


int main(void) {
    Game game;
    init_g(&game);
    game.run(&game);
}
