#include "../inc/state_play.h"
#include "../inc/game.h"
#include "../inc/colors.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>


void play(Data *data) {

    // put 2 random nums in grid
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    render_grid(data, &data->cell);

    while(true) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            render_grid(data, &data->cell);  			// calcs cell_w & cell_h
			//move_and_merge_numbers();
			//color_grid(data, data->cell);				// fills cells with different colors

			refresh();
        }
        // if (MO)
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
