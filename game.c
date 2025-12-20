#include <stdint.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "data.h"
#include "game.h"
#include "state_play.h"
#include "state_menu.h"

enum e_nums {
	N0 = (0b0),
	N2 = (0b1),
	N4 = (0b1 + 1),
	N8 = (0b1 + 2),
	N16 = (0b1 + 3),
	N32 = (0b1 + 4),
	N64 = (0b1 + 5),
	N128 = (0b1 + 6),
	N256 = (0b1 + 7),
	N512 = (0b1 + 8),
	N1024 = (0b1 + 9),
	N2048 = (0b1 + 10),
	N4096 = (0b1 + 11)
};

uint8_t	get_rand_nb(void) {
	return (rand() % 100 <= CHANCE_4 ? 4 : 2);
}

uint8_t	get_rand_pos(Data *data) {
	return (rand() % (data->grid_size * data->grid_size));
}
//			0			1			2			4			5			6			7			8			9			10			...
// grid => [0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000   0000 0000]

uint8_t	read_nb(uint8_t x, uint8_t y, uint8_t *grid, uint8_t grid_size) {
	uint8_t	nb = 0;
}

void	store_nb(uint8_t x, uint8_t y, uint8_t *grid, uint8_t grid_size, enum e_nums nb) {
	if (grid_size == 4)
	{
		
	}
	uint8_t	byte_index = y *
}

void	init(Data *data) {
	// Initialize game data
	data->grid_size = 4;
	data->state = ST_MENU;

	// Initialize ncurses
	srand(time(NULL));
	initscr();              // Like mlx_init for ncurses basically
	cbreak();               // Disable line buffering (So you don't need to press enter to get a key input)
	noecho();               // Do not display typed characters
	keypad(stdscr, TRUE);   // Enable function keys (like arrow keys)
	curs_set(0);            // Hide cursor on screen (usually it is blinking in the shell)
	if (has_colors()) {
		start_color();
	}
}

void	quit(void) {
	endwin();
	exit(0);
}

void	run(Data *data) {
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
