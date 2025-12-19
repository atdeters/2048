#ifndef GAME_H
# define GAME_H

# include <stdint.h>
# include "data.h"

# ifndef CHANCE_4
#   define CHANCE_4 5 // Chance in % to get a 4 instead of 2
# endif // CHANCE_4

#define DEBUG true

enum e_const {
    WIN_VALUE = 2048
};

void init(Data *data);
void run(Data *data);

#endif // ! GAME_H
