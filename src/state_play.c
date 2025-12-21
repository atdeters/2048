#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/grid_manipulation.h"
#include "../inc/game.h"
#include "../inc/helpers.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>
#include "stdlib.h"

int play(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    data->menu_state = FLD_PLAY;
    while(true) {

        if (render_grid(data, &data->cell)) {
            return 1;
        }

        if (!data->won && is_won(data)) {
            // TODO: Add a pop up
            move(1,1);
            printw("You won the game!\n");
            // Continue, Restart, Menu, Quit
            getch();
            data->won = true;
        }
        else if (is_lost(data)) {
            move(1,1);
            printw("You lost the game!\n");

            // TODO: Make this a pop up
            //
            // Restart, Menu, Quit
            getch();
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
