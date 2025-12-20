#ifndef DATA_H
# define DATA_H

#include <ncurses.h>
# include <stdint.h>
# include <stdbool.h>
# include "set.h"

enum e_states {
    ST_MENU,
    ST_PLAY,
    ST_EXIT
};

typedef struct s_data {
    uint8_t grid_size;
    unsigned int grid[5][5];
    enum e_states state;
    bool has_colors;
    uint16_t max_y;
    uint16_t max_x;
    Set empty_fields;
} Data;

#endif // ! DATA_H
