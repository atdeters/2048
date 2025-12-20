#include "../inc/state_menu.h"
#include <ncurses.h>

void menu(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    clear();
    while(true) {
        int ch = getch();
		if (ch == '\x1B') {
            data->state = ST_EXIT;
            return;
        }
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
        }
        if (ch == '1' || ch == 'p' || ch == 'r') {
            data->state = ST_PLAY;
            return;
        }
    }
}
