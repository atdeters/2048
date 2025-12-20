#include "../inc/game.h"

void	bzero_stack(uint8_t *stack, uint8_t grid_size) {
	for (uint8_t i = 0; i < grid_size; i++) {
		stack[i] = 0;
	}
}

void	fill_stack(uint8_t *stack, unsigned int grid[5][5], uint8_t i, uint8_t grid_size, enum e_dir direction) {
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
	unsigned int	top = 0;
	unsigned int	next = 0;
	uint8_t			len_to_top = 0;
	uint8_t			len_to_next = 0;

	if (grid_size == 1)
		return ;
	for (uint8_t x = 0; x < grid_size; x++) {
		if (stack[x]) {
			top = stack[x];
			len_to_top = x;
			for (uint8_t y = x + 1; y < grid_size; y++) {
				if (stack[y]) {
					next = stack[y];
					len_to_next = y;
					break ;
				}
			}
			break ;
		}
	}
	if (top == 0 && next == 0) {
		return ;
	}
	else if (top > 0 && next == 0) {
		*stack = top;
		if (len_to_top > 0)
			*(stack + len_to_top) = 0;
		if (len_to_next > 0)
			*(stack + len_to_next) = 0;
	}
	else if (top > 0 && next > 0 && top == next) {
		*stack = top * 2;
		if (len_to_top > 0)
			*(stack + len_to_top) = 0; // THIS TOO :D
		if (len_to_next > 0)
			*(stack + len_to_next) = 0;
	}
	else if (top > 0 && next > 0 && top != next) {
		*stack = top;
		if (len_to_top > 0)
			*(stack + len_to_top) = 0;
		if (len_to_next > 0 && *(stack + len_to_next) == 0)
			*(stack + len_to_next) = 0;
	}
	evaluate_stack(stack + 1, i, grid_size - 1);
}

void	store_stack(uint8_t *stack, unsigned int grid[5][5], uint8_t i, uint8_t grid_size, enum e_dir direction) {
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

/*
void    update_grid(unsigned int grid[5][5], uint8_t grid_size, enum e_dir direction) {
	uint8_t	stack[grid_size];

    for (uint8_t i = 0; i < grid_size; i++) {
		bzero_stack(stack, grid_size);
		fill_stack(stack, grid, i, grid_size, direction);
		evaluate_stack(stack, i, grid_size);
		store_stack(stack, grid, i, grid_size, direction);
	}
}
*/

void    update_grid(Data *data, enum e_dir direction) {
	uint8_t	stack[data->grid_size];

    for (uint8_t i = 0; i < data->grid_size; i++) {
		bzero_stack(stack, data->grid_size);
		fill_stack(stack, data->grid, i, data->grid_size, direction);
		evaluate_stack(stack, i, data->grid_size);
		store_stack(stack, data->grid, i, data->grid_size, direction);
	}
}

// int main(void)
// {
// 	unsigned int grid[5][5] = {0};
// 	grid[0][0] = 4;
// 	grid[0][1] = 4;
// 	grid[0][2] = 4;
// 	grid[0][3] = 8;

// 	printf("before:\n");
// 	for (int i = 0; i < 4; i++) {
// 		for (int x = 0; x < 4; x++) {
// 			printf("%u", grid[i][x]);
// 		}
// 		printf("\n");
// 	}
// 	update_grid(grid, 4, RIGHT);
// 	printf("=====\n");
// 	printf("after:\n");
// 	for (int i = 0; i < 4; i++) {
// 		for (int x = 0; x < 4; x++) {
// 			printf("%u", grid[i][x]);
// 		}
// 		printf("\n");
// 	}
// }
