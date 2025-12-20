#include "state_play.h"
#include "game.h"
#include <stdint.h>
#include <ncursesw/curses.h>


void draw_borders(Data *data) {


    getmaxyx(stdscr, data->max_y, data->max_x);
    uint16_t block_size = 4 * data->grid_size;
    uint16_t len = block_size;

    clear();
    for (uint16_t k = 0; k < data->grid_size; k++) {
        for (uint16_t i = 0; i < 2*len; i++) {
            printw("█");
        }
        addch('\n');
        for (uint16_t j = 0; j < block_size - 1; j++) {
            for (uint16_t i = 0; i < 2*len; i++) {
                if (i % block_size == 0 || i == len - 1) {
                    printw("█");
                }
                else {
                    addch(' ');
                }
            }
            addch('\n');
        }
    }
    for (uint16_t i = 0; i < len; i++) {
        addch('#');
    }
    refresh();
    move(0,0);
}

void play(Data *data) {

    getmaxyx(stdscr, data->max_y, data->max_x);
    draw_borders(data);

    while(true) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->max_y, data->max_x);
            draw_borders(data);
            refresh();
        }
        if (DEBUG && ch == '0') {
            data->state = ST_MENU;
            return;
        }
		if (DEBUG && ch == '\x1B') {
            data->state = ST_EXIT;
            return;
        }
    }
}
