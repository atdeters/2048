#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/grid_manipulation.h"
#include "../inc/game.h"
#include "../inc/helpers.h"
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

        if (is_lost(data)) {
            move(1,1);
            printw("You lost the game!\n");
            // TODO: Add new state which is lost -> Back to menu or something
        }

        // Get user event and do the actions
        int ch = getch();

        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            //move_and_merge_numbers();
            continue;
        }
        else if (ch == '0' || ch == 'M' || ch == 'm') {
            data->state = ST_MENU;
            return;
        }
        else if (ch == '\x1B') {
            data->state = ST_EXIT;
            return;
        }
        if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == 'h' || ch == 'H') {
            update_grid(data, LEFT);
        }
        else if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == 'l' || ch == 'L') {
            update_grid(data, RIGHT);
        }
        else if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == 'k' || ch == 'K') {
            update_grid(data, UP);
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S' || ch == 'j' || ch == 'J') {
            update_grid(data, DOWN);
        }
        update_empty_fields(data);
    }
}
