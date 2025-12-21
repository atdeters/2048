#include "../inc/state_play.h"
#include "../inc/render_grid.h"
#include "../inc/grid_manipulation.h"
#include "../inc/game.h"
#include "../inc/helpers.h"
#include "../inc/menu.h"
#include "../inc/config.h"
#include "../inc/colors.h"
#include <ncurses.h>
#include <stdint.h>
#include <ncursesw/curses.h>
#include "stdlib.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

void    set_new_highscore(Data *data, size_t moves) {
    time_t      timer;
    char        buffer[26];
    struct tm   *tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    // ft_fprintf(data->highscores_fd, "Score:%zu, Moves:%zu\n", data->score, moves, buffer);

    dprintf(data->highscores_fd, "Score:%zu, Moves:%zu, ", data->score, moves);
    dprintf(data->highscores_fd, "%s", buffer);
    dprintf(data->highscores_fd, "\n");
    data->highscore = data->score;

    return ;
}

int popup(Data *data, enum e_end end) {
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
            return 2;
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
        else if (ch == 'q' || ch == 'Q' || ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return 1;
        }
        else if (ch == 'm' || ch == 'M') {
            data->state = ST_MENU;
            return 1;
        }
        else if (ch == KEY_ENTER) {
            switch (data->popup_state) {
                case FLD_PLAY:
                    data->state = ST_PLAY;
                    data->game_on = true;
                    return 0;
                case FLD_QUIT:
                    data->state = ST_EXIT;
                    return 1;
                case FLD_SETT:
                    data->state = ST_MENU;
                    return 1;
                    break;
                case FLD_RESTART:
                    data->state = ST_RESTART;
                    return 1;
            }
        }
        else if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == 'k' || ch == 'K') {
            if (end != WON && data->popup_state != FLD_RESTART) {
                data->popup_state -= 1;
            }
            else if (end == WON && data->popup_state != FLD_PLAY) {
                data->popup_state -= 1;
            }
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S' || ch == 'j' || ch == 'J') {
            if (data->popup_state != FLD_QUIT) {
                data->popup_state += 1;
            }
        }

    }
    return 0;
}

int play(Data *data) {
    int res;
    size_t  moves = 0;

    data->score = 0;
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    data->menu_state = FLD_PLAY;
    while(true) {
        res = 0;
        /*
        getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
        if (data->grid_max_x < 10 || data->grid_max_y < 17) {
            clear();
            printw("Window too small!\n");
            getch();
            continue;
        }
        */



        if (render_grid(data, &data->cell)) {
            return 1;
        }
        move(0, 1);
        if (data->score > data->highscore)
            set_new_highscore(data, moves);
        attron(COLOR_PAIR(PSCORE));
        printw("Score: %zu Moves: %zu. Best: %zu", data->score, moves, data->highscore);
        attroff(COLOR_PAIR(PSCORE));
        // move(1, 0);

        if (!data->cont && is_won(data)) {
            data->won = true;
            if (WIN_VALUE != 2048 && is_lost(data)) { // In this case just checks if 2048 got reached
                data->popup_state = FLD_RESTART;
                res = popup(data, END);
                if (res == 2) {
                    continue;
                }
                else if (res) {
                    return 0;
                }
            }
            else {
                res = popup(data, WON);
                if (res == 2) {
                    continue;
                }
                else if (res) {
                    data->popup_state = FLD_PLAY;
                    return 0;
                }
            }


            data->cont = true;
            continue;
        }
        else if (is_lost(data)) {
            data->popup_state = FLD_RESTART;
            if (data->won) {
                res = popup(data, WON_OVER);
                if (res == 2) {
                    continue;
                }
                else if (res) {
                    return 0;
                }
            }
            else {
                res = popup(data, LOSE);
                if (res == 2) {
                    continue;
                }
                else if (res) {
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
                    moves++;
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
