#include "state_menu.h"
#include "game.h"
#include <ncurses.h>

void menu(Data *data) {
    getmaxyx(stdscr, data->max_y, data->max_x);
    while(true) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->max_y, data->max_x);
            printw("max_x: %d max_y: %d\n", data->max_x, data->max_y);
            refresh();
        }
        if (DEBUG && ch == '1') {
            data->state = ST_PLAY;
            return;
        }
    }
}
