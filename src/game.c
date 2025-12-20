#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "locale.h"
#include "../inc/data.h"
#include "../inc/game.h"
#include "../inc/state_play.h"
#include "../inc/state_menu.h"
#include "../inc/colors.h"

uint8_t get_rand_nb(void) {
    return (rand() % 100 <= CHANCE_4 ? 4 : 2);
}

uint8_t get_rand_pos(Data *data) {
    return (rand() % (data->grid_size * data->grid_size));
}

void	bzero_stack(uint8_t *stack, uint8_t grid_size) {
	for (uint8_t i = 0; i < grid_size; i++) {
		stack[i] = 0;
	}
}

void	fill_stack(uint8_t *stack, unsigned int **grid, uint8_t i, uint8_t grid_size, enum e_dir direction) {
	for (uint8_t x = 0; x < grid_size; x++) {
		switch (direction) {
			case LEFT:
				stack[x] = grid[i][x];
				break ;
			case RIGHT:
				stack[x] = grid[i][grid_size - 1 - x];
				break ;
			case DOWN:
				stack[x] = grid[grid_size - 1 - x][i];
				break ;
			case UP:
				stack[x] = grid[x][i];
				break ;
		}
	}
}

void	evaluate_stack(uint8_t *stack, uint8_t i, uint8_t grid_size) {
	uint8_t			cur_ind = 0;
	unsigned int	top = -1;
	unsigned int	next = -1;

	if (grid_size == 1)
		return ;
	for (uint8_t x = 0; x < grid_size; x++) {
		if (stack[x]) {
			top = stack[x];
			for (uint8_t y = x + 1; y < grid_size; y++) {
				if (stack[y]) {
					next = stack[y];
					break ;
				}
			}
			break ;
		}
	}
	if (top == -1 && next == -1) {
		return ;
	}
	else if (top > -1 && next == -1) {
		*stack = top;
		*(stack + 1) = 0; // NOT SURE ABOUT THIS.
	}
	else if (top > -1 && next > -1 && top == next) {
		*stack = top * 2;
		*(stack + 1) = 0; // THIS TOO :D
		stack++;
	}
	evaluate_stack(stack + 1, i, grid_size - 1);
}

void	store_stack(uint8_t *stack, unsigned int **grid, uint8_t i, uint8_t grid_size, enum e_dir direction) {
	for (uint8_t x = 0; x < grid_size; x++) {
		switch (direction) {
			case LEFT:
				grid[i][x] = stack[x];
				break ;
			case RIGHT:
				grid[i][grid_size - 1 - x] = stack[x];
				break ;
			case DOWN:
				grid[grid_size - 1 - x][i] = stack[x];
				break ;
			case UP:
				grid[x][i] = stack[x];
				break ;
		}
	}
}

void    move_grid(unsigned int **grid, uint8_t grid_size, enum e_dir direction) {
	uint8_t	stack[grid_size];

    for (uint8_t i = 0; i < grid_size; i++) {
		bzero_stack(stack, grid_size);
		fill_stack(stack, grid, i, grid_size, direction);
		evaluate_stack(stack, i, grid_size);
		store_stack(stack, grid, i, grid_size, direction);
		// move_arr(grid[i], grid_size, direction);
	}
}

void init(Data *data) {

	if (!is_power_of_2(WIN_VALUE))
		exit(1);
    // Initialize game data

    data->grid_size = 4;
    data->state = ST_MENU;

    // Initialize ncurses
    srand(time(NULL));
    setlocale(LC_ALL, "");
    initscr();              // Like mlx_init for ncurses basically
    cbreak();               // Disable line buffering (So you don't need to press enter to get a key input)
    noecho();               // Do not display typed characters
    keypad(stdscr, TRUE);   // Enable function keys (like arrow keys)
    curs_set(0);            // Hide cursor on screen (usually it is blinking in the shell)

    // Colors
    start_color();          // TODO: Check if this is dangerous if terminal doesnt allow colors
    init_color_hex(CL1, COL1);
    init_color_hex(CL2, COL2);
    init_color_hex(CL3, COL3);
    init_color_hex(CL4, COL4);
    init_color_hex(CL5, COL5);
    init_color_hex(CL6, COL6);
    init_color_hex(CL7, COL7);
    init_color_hex(CL8, COL8);
    init_color_hex(CL9, COL9);
    init_color_hex(CL10, COL10);
    init_color_hex(CL11, COL11);
    init_color_hex(CL12, COL12);
    init_color_hex(CL13, COL13);

    init_pair(P1, COLOR_BLACK, CL1);
    init_pair(P2, COLOR_BLACK, CL2);
    init_pair(P3, COLOR_BLACK, CL3);
    init_pair(P4, COLOR_BLACK, CL4);
    init_pair(P5, COLOR_BLACK, CL5);
    init_pair(P6, COLOR_BLACK, CL6);
    init_pair(P7, COLOR_BLACK, CL7);
    init_pair(P8, COLOR_BLACK, CL8);
    init_pair(P9, COLOR_BLACK, CL9);
    init_pair(P10, COLOR_BLACK, CL10);
    init_pair(P11, COLOR_BLACK, CL11);
    init_pair(P12, COLOR_BLACK, CL12);
    init_pair(P13, COLOR_BLACK, CL13);
}


void quit(void) {
    endwin();

    exit(0);
}

void run(Data *data) {
    while(true) {
        switch (data->state) {
            case ST_MENU:
                menu(data);
                break;
            case ST_PLAY:
                play(data);
                break;
            case ST_EXIT:
                quit();
        }
    }
}
