#include "../inc/state_menu.h"
#include "../inc/data.h"
#include "../inc/libft.h"
#include "../inc/colors.h"
#include "../inc/game.h"
#include <ncurses.h>


# define MENU_MAIN_FIELDS 3 // Cannot be smaller than 2
# define MENU_WIDTH 30
# define MENU_HEIGHT (MENU_MAIN_FIELDS + 2)

// TODO: Make these part of a theme!
# define PUIHL P2
# define PUINHL 0

static void print_border(unsigned int len) {
    attron(COLOR_PAIR(PGRID));
    addch('+');
    for (size_t i = 0; i < len; i++) {
        addch('-');
    }
    addch('+');
    attroff(COLOR_PAIR(PGRID));
}

static void print_botton(char *name, char *buttons, bool highlight) {


    attron(COLOR_PAIR(PGRID));
    addstr("||");
    attroff(COLOR_PAIR(PGRID));
    if (highlight) {
        attron(COLOR_PAIR(PUIHL));
    }
    else {
        attron(COLOR_PAIR(PUINHL));
    }
    printw(" %s", name);
    size_t space = MENU_WIDTH - 4 - ft_strlen(name) - ft_strlen(buttons);
    for (size_t i = 0; i < space; i++) {
        addch(' ');
    }
    printw("%s ", buttons);
    if (highlight) {
        attroff(COLOR_PAIR(PUIHL));
    }
    else {
        attroff(COLOR_PAIR(PUINHL));
    }
    attron(COLOR_PAIR(PGRID));
    addstr("||");
    attroff(COLOR_PAIR(PGRID));
}

void render_menu_main(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    clear();
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - (MENU_HEIGHT / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    print_botton("Play", "p", data->menu_state == FLD_PLAY ? 1 : 0);
    move(y+2, x);
    print_botton("Settings", "s", data->menu_state == FLD_SETT ? 1 : 0);
    move(y+3, x);
    print_botton("Quit", "q", data->menu_state == FLD_QUIT ? 1 : 0);
    move(y+4, x);
    print_border(MENU_WIDTH);
    refresh();
}

void menu(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    while(true) {

        render_menu_main(data);

        int ch = getch();

		if (ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return;
        }
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            continue;
        }
        else if (ch == '1' || ch == 'p' || ch == 'P') {
            data->state = ST_PLAY;
            return;
        }
        else if (ch == '2' || ch == 'r' || ch == 'R') {
            data->state = ST_PLAY;
            return;
        }
        if (ch == KEY_ENTER) {
            switch (data->menu_state) {
                case FLD_PLAY:
                    data->state = ST_PLAY;
                    return;
                case FLD_QUIT:
                    data->state = ST_EXIT;
                    return;
                case FLD_SETT:
                    data->state = ST_PLAY;
                    return;
            }
        }
        else if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == 'k' || ch == 'K') {
            if (data->menu_state != FLD_PLAY) {
                data->menu_state -= 1;
            }
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S' || ch == 'j' || ch == 'J') {
            if (data->menu_state != FLD_QUIT) {
                data->menu_state += 1;
            }
        }
    }
}
