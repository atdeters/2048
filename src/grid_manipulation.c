#include "../inc/game.h"

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
