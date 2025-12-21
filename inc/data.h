#ifndef DATA_H
# define DATA_H

#include <ncurses.h>
# include <stdint.h>
# include <stdbool.h>
# include "set.h"
# include "../inc/libft.h"

enum e_states {
    ST_MENU,
    ST_PLAY,
    ST_EXIT,
    ST_RESTART
};

enum e_menu {
    FLD_PLAY,
    FLD_RESTART,
    FLD_SETT,
    FLD_QUIT
};

enum e_sett {
    FLD_4,
    FLD_5,
    FLD_BACK
};

typedef struct s_cell {

    int	w;
	int	h;
}   Cell;

typedef struct s_data {
    uint8_t         grid_size;
    unsigned int    grid[5][5];
    enum e_states   state;
    uint16_t        grid_max_y;
    uint16_t        grid_max_x;
	Cell            cell;
    uint16_t        max_y;
    uint16_t        max_x;
    Set             empty_fields;
    enum e_menu     menu_state;
    enum e_sett     settings_state;
    enum e_menu     popup_state;
    bool            game_on;
    bool            won;
    bool            cont;
} Data;

#endif // ! DATA_H
