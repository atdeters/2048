#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/game.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>

void play(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    while(true) {
        add_rnd(data);
        render_grid(data, &data->cell);
        refresh();
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
			//move_and_merge_numbers();
            continue;
        }
        // if (MO)
        if (ch == '0') {
            data->state = ST_MENU;
            return;
        }
		if (ch == '\x1B') {
            data->state = ST_EXIT;
            return;
        }
    }
}
