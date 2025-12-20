#include "../inc/helpers.h"
#include "../inc/data.h"
#include <stdint.h>

#include <stdlib.h>

uint16_t min(uint16_t a, uint16_t b) {
    if (a < b)
        return a;
    return b;
}

int	is_power_of_2(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (i <= n)
	{
		if (i == n)
			return (1);
		i *= 2;
	}
	printf("Error\nWIN_VALUE is not a power of 2\n");
	return (0);
}

void add_nb_to_grid(Data *data, uint8_t field_nb, uint8_t value) {
    uint8_t grid_x = field_nb;
    uint8_t grid_y = 0;
    while (grid_x >= (*data).grid_size) {
        grid_x -= (*data).grid_size;
        grid_y++;
    }
    (*data).grid[grid_y][grid_x] = value;
}

void test_filling_grid(Data *data) {
    add_nb_to_grid(data, 0, 0);
    add_nb_to_grid(data, 1, 1);
    add_nb_to_grid(data, 2, 2);
    add_nb_to_grid(data, 3, 3);
    add_nb_to_grid(data, 4, 4);
    add_nb_to_grid(data, 5, 5);
    add_nb_to_grid(data, 6, 6);
    add_nb_to_grid(data, 7, 7);
    add_nb_to_grid(data, 8, 8);
    add_nb_to_grid(data, 9, 9);
    add_nb_to_grid(data, 10, 10);
    add_nb_to_grid(data, 11, 11);
    add_nb_to_grid(data, 12, 12);
    add_nb_to_grid(data, 13, 13);
    add_nb_to_grid(data, 14, 14);
    add_nb_to_grid(data, 15, 15);
    add_nb_to_grid(data, 16, 16);
    add_nb_to_grid(data, 17, 17);
    add_nb_to_grid(data, 18, 18);
    add_nb_to_grid(data, 19, 19);
    add_nb_to_grid(data, 20, 20);
    add_nb_to_grid(data, 21, 21);
    add_nb_to_grid(data, 22, 22);
    add_nb_to_grid(data, 23, 23);
    add_nb_to_grid(data, 24, 24);
    add_nb_to_grid(data, 25, 25);
}

void display_grid(Data *data) {
    for(int i = 0; i < data->grid_size; i++) {
        for (int j = 0; j < data->grid_size; j++) {
            printw("|%u|", data->grid[i][j]);
        }
        printw("\n");
    }
    refresh();
}
