#include "../inc/state_menu.h"
#include "../inc/data.h"
#include "../inc/game.h"
#include "../inc/menu.h"
#include "../inc/settings.h"
#include <ncurses.h>

void menu(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    while(true) {

        if (data->game_on) {
            render_menu_on(data);
        }
        else {
            render_menu_off(data);
        }

        int ch = getch();

        // Special keys
		if (ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return;
        }
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            continue;
        }

        else if (ch == 'p' || ch == 'P') {
            data->state = ST_PLAY;
            data->game_on = true;
            return;
        }
        else if (data->game_on && (ch == 'r' || ch == 'R')) {
            data->state = ST_RESTART;
            return;
        }
        else if (ch == 'q' || ch == 'Q') {
            data->state = ST_EXIT;
            return;
        }
        else if (ch == 'e' || ch == 'E') {
            settings(data);
            if (data->state == ST_EXIT) {
                return;
            }
        }

        // Enter key depending on the current state
        else if (ch == KEY_ENTER) {
            switch (data->menu_state) {
                case FLD_PLAY:
                    data->state = ST_PLAY;
                    data->game_on = true;
                    return;
                case FLD_QUIT:
                    data->state = ST_EXIT;
                    return;
                case FLD_SETT:
                    settings(data);
                    if (data->state == ST_EXIT) {
                        return;
                    }
                    break;
                case FLD_RESTART:
                    data->state = ST_RESTART;
                    return;
            }
        }

        // Going up and down in the menu
        else if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == 'k' || ch == 'K') {
            if (data->game_on == false && data->menu_state == FLD_SETT) {
                data->menu_state -= 2;
            }
            if (data->menu_state != FLD_PLAY) {
                data->menu_state -= 1;
            }
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S' || ch == 'j' || ch == 'J') {
            if (data->game_on == false && data->menu_state == FLD_PLAY) {
                data->menu_state += 2;
            }
            else if (data->menu_state != FLD_QUIT) {
                data->menu_state += 1;
            }
        }
    }
}
