#ifndef DATA_H
# define DATA_H

# include <stdint.h>
# include <stdbool.h>

enum e_states {
    ST_MENU,
    ST_PLAY,
    ST_EXIT
};

typedef struct s_data {
    uint8_t grid_size;
    uint8_t grid[5];
    enum e_states state;
    bool has_colors;
    uint16_t max_y;
    uint16_t max_x;
} Data;

#endif // ! DATA_H
