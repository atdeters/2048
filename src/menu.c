#include "../inc/menu.h"
#include "../inc/data.h"
#include "../inc/colors.h"
#include <ncurses.h>

void print_label(const char *label) {
    attron(COLOR_PAIR(PGRID));
    addstr("||");
    attroff(COLOR_PAIR(PGRID));

    attron(A_UNDERLINE);
    addstr(label);
    attroff(A_UNDERLINE);

    for (int i = 0; i < MENU_WIDTH - 2 - ft_strlen(label); i++) {
        addch(' ');
    }
    attron(COLOR_PAIR(PGRID));
    addstr("||");
    attroff(COLOR_PAIR(PGRID));
}

void print_border(unsigned int len) {
    attron(COLOR_PAIR(PGRID));
    addch('+');
    for (size_t i = 0; i < len; i++) {
        addch('-');
    }
    addch('+');
    attroff(COLOR_PAIR(PGRID));
}

void print_botton(char *name, char *buttons, bool highlight) {
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

// Menu Renders
void render_menu_off(Data *data) {
    clear();
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - ((MENU_MAIN_FIELDS_OFF + 2) / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    print_botton("Play", "p", data->menu_state == FLD_PLAY ? 1 : 0);
    move(y+2, x);
    print_botton("Settings", "e", data->menu_state == FLD_SETT ? 1 : 0);
    move(y+3, x);
    print_botton("Quit", "q", data->menu_state == FLD_QUIT ? 1 : 0);
    move(y+4, x);
    print_border(MENU_WIDTH);
    refresh();
}

void render_menu_on(Data *data) {
    clear();
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - ((MENU_MAIN_FIELDS_ON + 2) / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    print_botton("Resume", "p", data->menu_state == FLD_PLAY ? 1 : 0);
    move(y+2, x);
    print_botton("Restart", "r", data->menu_state == FLD_RESTART ? 1 : 0);
    move(y+3, x);
    print_botton("Settings", "e", data->menu_state == FLD_SETT ? 1 : 0);
    move(y+4, x);
    print_botton("Quit", "q", data->menu_state == FLD_QUIT ? 1 : 0);
    move(y+5, x);
    print_border(MENU_WIDTH);
    refresh();
}

void render_popup_won(Data *data) {
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - ((MENU_MAIN_FIELDS_ON + 2) / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    print_label("Game won!");
    move(y+2, x);
    print_botton("Resume", "p", data->menu_state == FLD_PLAY ? 1 : 0);
    move(y+3, x);
    print_botton("Restart", "r", data->menu_state == FLD_RESTART ? 1 : 0);
    move(y+4, x);
    print_botton("Menu", "m", data->menu_state == FLD_SETT ? 1 : 0);
    move(y+5, x);
    print_botton("Quit", "q", data->menu_state == FLD_QUIT ? 1 : 0);
    move(y+6, x);
    print_border(MENU_WIDTH);
    refresh();
}

void render_popup_over(Data *data, enum e_end end) {
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - ((MENU_MAIN_FIELDS_ON + 2) / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    if (end == WON_OVER) {
        print_label("You won! But now its Game over!");
    }
    else if (end == LOSE) {
        print_label("Game over!");
    }
    else {
        print_label("2048 reached! Congrats");
    }
    move(y+2,x);
    print_botton("Restart", "r", data->menu_state == FLD_RESTART ? 1 : 0);
    move(y+3, x);
    print_botton("Menu", "m", data->menu_state == FLD_SETT ? 1 : 0);
    move(y+4, x);
    print_botton("Quit", "q", data->menu_state == FLD_QUIT ? 1 : 0);
    move(y+5, x);
    print_border(MENU_WIDTH);
    refresh();
}


