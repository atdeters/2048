#include "state_play.h"
#include "data.h"
#include <ncurses.h>
#include <stdint.h>

void play(Data *data) {
    getmaxyx(stdscr, data->max_y, data->max_x);
    while(true) {
        clear();
        printw("Playing\n");
        refresh();        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->max_y, data->max_x);
            printw("max_x: %d max_y: %d\n", data->max_x, data->max_y);
            refresh();
        }
        if (DEBUG && ch == '0') {
            data->state = ST_MENU;
            return;
        }
    }
}
