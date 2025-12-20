#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "locale.h"
#include "../inc/data.h"
#include "../inc/game.h"
#include "../inc/state_play.h"
#include "../inc/state_menu.h"
#include "../inc/colors.h"

#define INIT_GRID_SIZE 4

static uint8_t get_rand_nb(void) {
    return (rand() % 100 <= CHANCE_4 ? 4 : 2);
}

static uint8_t get_rand_pos(Data *data) {

    uint8_t pos = data->empty_fields.container[rand() % (data->empty_fields.idx + 1)];
    set_remove(&data->empty_fields, pos);
    return pos;
}

void add_rnd(Data *data) {
    uint8_t pos = get_rand_pos(data);
    add_nb_to_grid(data, pos, get_rand_nb());
}

void update_empty_fields(Data *data) {
    set_clear(&data->empty_fields);
    for (size_t i = 0; i < data->grid_size; i++) {
        for (size_t j = 0; j < data->grid_size; j++) {
            if (data->grid[i][j] != 0) {
                set_insert(&data->empty_fields, data->grid[i][j]);
            }
        }
    }
}

void init(Data *data) {

	if (!is_power_of_2(WIN_VALUE))
		exit(1);
    // Initialize game data

    data->grid_size = INIT_GRID_SIZE;
    data->state = ST_MENU;

    // Initialize ncurses
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();              // Like mlx_init for ncurses basically
    cbreak();               // Disable line buffering (So you don't need to press enter to get a key input)
    noecho();               // Do not display typed characters
    keypad(stdscr, TRUE);   // Enable function keys (like arrow keys)
    curs_set(0);            // Hide cursor on screen (usually it is blinking in the shell)

    // Colors
    start_color();          // TODO: Check if this is dangerous if terminal doesnt allow colors
    init_color_hex(CL1, COL1);
    init_color_hex(CL2, COL2);
    init_color_hex(CL3, COL3);
    init_color_hex(CL4, COL4);
    init_color_hex(CL5, COL5);
    init_color_hex(CL6, COL6);
    init_color_hex(CL7, COL7);
    init_color_hex(CL8, COL8);
    init_color_hex(CL9, COL9);
    init_color_hex(CL10, COL10);
    init_color_hex(CL11, COL11);
    init_color_hex(CL12, COL12);
    init_color_hex(CL13, COL13);
    init_color_hex(BACKGROUND, COL_BACK);

    init_pair(P1, COLOR_BLACK, CL1);
    init_pair(P2, COLOR_BLACK, CL2);
    init_pair(P3, COLOR_BLACK, CL3);
    init_pair(P4, COLOR_BLACK, CL4);
    init_pair(P5, COLOR_BLACK, CL5);
    init_pair(P6, COLOR_BLACK, CL6);
    init_pair(P7, COLOR_BLACK, CL7);
    init_pair(P8, COLOR_BLACK, CL8);
    init_pair(P9, COLOR_BLACK, CL9);
    init_pair(P10, COLOR_BLACK, CL10);
    init_pair(P11, COLOR_BLACK, CL11);
    init_pair(P12, COLOR_BLACK, CL12);
    init_pair(P13, COLOR_BLACK, CL13);
    init_pair(PBACK, BACKGROUND, BACKGROUND);

    // Add first, second gets added in game loop
    init_set(&data->empty_fields, INIT_GRID_SIZE * INIT_GRID_SIZE);
    add_rnd(data);
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
