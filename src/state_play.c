#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/grid_manipulation.h"
#include "../inc/game.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>

void play(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    while(true) {
        // Add nb, render grid and refresh
        add_rnd(data);
        render_grid(data, &data->cell);
        refresh();

        // Get user event and do the actions
        int ch = getch();

        if (ch == KEY_LEFT) {
            update_grid(data, LEFT);
        }
        else if (ch == KEY_RIGHT) {
            update_grid(data, RIGHT);
        }
        else if (ch == KEY_UP) {
            update_grid(data, UP);
        }
        else if (ch == KEY_DOWN) {
            update_grid(data, DOWN);
        }
        update_empty_fields(data);


        // Special cases
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
			//move_and_merge_numbers();
            continue;
        }
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
