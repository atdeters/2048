#include "../inc/state_menu.h"
#include "../inc/data.h"
#include "../inc/libft.h"
#include "../inc/colors.h"
#include "../inc/game.h"
#include <ncurses.h>


# define MENU_MAIN_FIELDS_ON 4 // Cannot be smaller than 2
# define MENU_MAIN_FIELDS_OFF 3 // Cannot be smaller than 2
# define SETTINGS_FIELDS 4
# define MENU_WIDTH 30

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

void render_settings(Data *data) {
    clear();
    int x = (data->grid_max_x / 2) - (MENU_WIDTH / 2);
    int y = (data->grid_max_y / 2) - ((SETTINGS_FIELDS + 2) / 2);

    move(y, x);
    print_border(MENU_WIDTH);
    move(y+1, x);
    print_label("Grid size");
    move(y+2,x);
    if (data->grid_size == 4) {
        print_botton("[x] 4x4", "4", data->settings_state == FLD_4 ? 1 : 0);
    }
    else {
        print_botton("[ ] 4x4", "4", data->settings_state == FLD_4 ? 1 : 0);
    }
    move(y+3, x);
    if (data->grid_size == 5) {
        print_botton("[x] 5x5", "5", data->settings_state == FLD_5 ? 1 : 0);
    }
    else {
        print_botton("[ ] 5x5", "5", data->settings_state == FLD_5 ? 1 : 0);
    }
    move(y+4, x);
    print_botton("Go Back", "b", data->settings_state == FLD_BACK ? 1 : 0);
    move(y+5, x);
    print_border(MENU_WIDTH);
    refresh();
}


void settings(Data *data) {
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
    int grid_size_before = data->grid_size;
    while(true) {
        render_settings(data);
        int ch = getch();

        // Special keys
        if (ch == KEY_ESCAPE) {
            data->state = ST_EXIT;
            return;
        }
        else if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
            continue;
        }
        else if (ch == '4') {
            data->grid_size = 4;
        }
        else if (ch == '5') {
            data->grid_size = 5;
        }
        else if (ch == 'b' || ch == 'B') {
            data->state = ST_MENU;
            return;
        }

        else if (ch == KEY_ENTER) {
            switch (data->settings_state) {
                case FLD_4:
                    if (data->grid_size == 4) {
                        if (data->grid_size != grid_size_before) {
                            init_data(data, data->grid_size);
                        }
                        return;
                    }
                    else {
                        data->grid_size = 4;
                    }
                    break;
                case FLD_5:
                    if (data->grid_size == 5) {
                        if (data->grid_size != grid_size_before) {
                            init_data(data, data->grid_size);
                        }
                        return;
                    }
                    else {
                        data->grid_size = 5;
                    }
                    break;
                case FLD_BACK:
                    return;
            }
        }

        // Going up and down in the menu
        else if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == 'k' || ch == 'K') {
            if (data->settings_state != FLD_4) {
                data->settings_state -= 1;
            }
        }
        else if (ch == KEY_DOWN || ch == 's' || ch == 'S' || ch == 'j' || ch == 'J') {
            if (data->settings_state != FLD_BACK) {
                data->settings_state += 1;
            }
        }

    }

}


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
        // TODO:
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
