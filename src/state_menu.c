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
        else if (ch == '1' || ch == 'p' || ch == 'P') {
            data->state = ST_PLAY;
            return;
        }
        else if (ch == '2' || ch == 'r' || ch == 'R') {
            data->state = ST_PLAY;
            return;
        }
    }
}
