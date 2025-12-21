#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/grid_manipulation.h"
#include "../inc/game.h"
#include "../inc/helpers.h"
#include "../inc/menu.h"
#include "../inc/config.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>
#include "stdlib.h"


// State: Won: Continue, Restart, Menu, Quit
// State: Won - No More moves: Restart, Menu, Quit
// State: No more moves -> Game Over: Restart, Menu, Quit



int popup(Data *data, enum e_end end) {
    data->popup_state = FLD_PLAY;
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    while(true) {

        if (end == WON) {
            render_popup_won(data);
        }
        else {
            render_popup_over(data, end);
        }

        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            continue;
        }
        else if (ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return 1;
        }
        else if (ch == 'p' || ch == 'P') { // Means resume in this case
            data->state = ST_PLAY;
            data->game_on = true;
            return 0;
        }
        else if ( data->game_on && (ch == 'r' || ch == 'R')) {
            data->state = ST_RESTART;
            return 1;
        }
        else if (ch == 'q' || ch == 'Q') {
            data->state = ST_EXIT;
            return 1;
        }
        else if (ch == 'm' || ch == 'M') {
            data->state = ST_MENU;
            return 1;
        }


    }
    return 0;
}

int play(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    data->menu_state = FLD_PLAY;
    while(true) {
        if (render_grid(data, &data->cell)) {
            return 1;
        }
        if (!data->cont && is_won(data)) {
            data->won = true;
            if (WIN_VALUE != 2048 && is_lost(data)) { // In this case just checks if 2048 got reached
                if (popup(data, END)) {
                    return 0;
                }
            }
            if (popup(data, WON)) {
                return 0;
            }
            data->cont = true;
            continue;
        }
        else if (is_lost(data)) {
            if (data->won) {
                if (popup(data, WON_OVER)) {
                    return 0;
                }
            }
            else {
                if (popup(data, LOSE)) {
                    return 0;
                }
            }
            init_data(data, data->grid_size);
            data->state = ST_MENU;
            data->game_on = false;
            return 0;
        }

        // Get user input
        int ch = getch();

        // Special Keys
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            continue;
        }
        if (ch == 'M' || ch == 'm') {
            data->state = ST_MENU;
            return 0;
        }
        else if (ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return 0;
        }

        // Temporary grid
        unsigned int tmp[5][5];
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                tmp[i][j] = data->grid[i][j];
            }
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


        // Checking with temporary grid
        bool didbreak = false;
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                if (tmp[i][j] != data->grid[i][j]) {
                    add_rnd(data);
                    didbreak = true;
                    break;
                }
            }
            if (didbreak) {
                break;
            }
        }
    }
}
