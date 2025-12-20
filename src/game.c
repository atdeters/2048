#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "data.h"
#include "game.h"
#include "state_play.h"
#include "state_menu.h"

#include "locale.h"

uint8_t get_rand_nb(void) {
    return (rand() % 100 <= CHANCE_4 ? 4 : 2);
}

uint8_t get_rand_pos(Data *data) {
    return (rand() % (data->grid_size * data->grid_size));
}

void init(Data *data) {

	if (!is_power_of_2(WIN_VALUE))
		exit(1);
    // Initialize game data

    data->grid_size = 4;
    data->state = ST_MENU;

    // Initialize ncurses
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();              // Like mlx_init for ncurses basically
    cbreak();               // Disable line buffering (So you don't need to press enter to get a key input)
    noecho();               // Do not display typed characters
    keypad(stdscr, TRUE);   // Enable function keys (like arrow keys)
    curs_set(0);            // Hide cursor on screen (usually it is blinking in the shell)
    if (has_colors()) {
        start_color();
    }
}

void quit(void) {
    endwin();

    exit(0);
}

void run(Data *data) {
    while(true) {
        switch (data->state) {
            case ST_MENU:
                menu(data);
                break;
            case ST_PLAY:
                play(data);
                break;
            case ST_EXIT:
                quit();
        }
    }
}
