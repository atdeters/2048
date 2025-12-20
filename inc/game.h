#ifndef GAME_H
# define GAME_H

# include <stdint.h>
# include "data.h"

# ifndef DEBUG
#  define DEBUG true
# endif

# ifndef CHANCE_4
#   define CHANCE_4 5 // Chance in % to get a 4 instead of 2
# endif // CHANCE_4

enum e_dir {
    DOWN,
    UP,
    LEFT,
    RIGHT
};

enum e_const {
    WIN_VALUE = 2048
};

void add_rnd(Data *data);
void update_empty_fields(Data *data);
void init(Data *data);
void quit(void);
void run(Data *data);

#include "helpers.h"
#include "state_menu.h"
#include "state_play.h"
#include "render_grid.h"



#endif // ! GAME_H
