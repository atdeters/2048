#include "../inc/settings.h"
#include "../inc/menu.h"
#include "../inc/data.h"
#include "../inc/game.h"

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
        else if (ch == 'b' || ch == 'B' || ch == 'm' || ch == 'M') {
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
                    if (data->grid_size != grid_size_before) {
                        init_data(data, data->grid_size);
                    }
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
