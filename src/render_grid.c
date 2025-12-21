#include <ncurses.h>
#include <stdint.h>
#include "../inc/render_grid.h"
#include <ncursesw/curses.h>
#include "../inc/colors.h"
#include "../inc/ascii_digits.h"

int	ft_count_digits(int n)
{
	int			digits;
	long int	num;

	num = n;
	digits = 0;
	if (num == 0)
		digits = 1;
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		num = num / 10;
		digits++;
	}
	return (digits);
}

int	getmax_digit(Data *data)
{
	int y = 0;
	int x;

	int max = 0;
	while (y < data->grid_size) // loops through each cell per col
	{
		x = 0;
		while (x < data->grid_size) // loops through each cell per row
		{
			if (data->grid[y][x] > (unsigned int) max)
				max = data->grid[y][x];
			x++;
		}
		y++;
	}
	int max_digits = ft_count_digits(max);
	return (max_digits);
}


short	get_color(unsigned int nb)
{
    if (nb == 0) {
        return PBACK;
    }
    else if (nb == (1 << 1))
		return P2;
    else if (nb == (1 << 2))
		return P4;
    else if (nb == (1 << 3))
		return P8;
    else if (nb == (1 << 4))
		return P16;
    else if (nb == (1 << 5))
		return P32;
    else if (nb == (1 << 6))
		return P64;
    else if (nb == (1 << 7))
		return P128;
    else if (nb == (1 << 8))
		return P256;
    else if (nb == (1 << 9))
		return P512;
    else if (nb == (1 << 10))
		return P1024;
    else if (nb == (1 << 11))
		return P2048;
    else if (nb == (1 << 12))
		return P4096;
    else if (nb == (1 << 13))
		return P8192;
    else if (nb == (1 << 14))
		return P16384;
    else if (nb == (1 << 15))
		return P32768;
	return P65536;
}

int	color_cell(Data *data, Cell *cell, int x, int y, int max_digits)
{
	unsigned int grid_num = data->grid[y][x];
	int start_x = 1 + x * (cell->w + 1);
	int start_y = 1 + y * (cell->h + 1);

	short color = get_color(grid_num);
	for (int row = 0; row < cell->h; row++){
		move(start_y + row, start_x);
		if( start_y < data->grid_max_y)
			chgat(cell->w, A_NORMAL, color, NULL);
	}
	int digits = ft_count_digits(grid_num);

	int x_center = start_x + (cell->w / 2);
	int y_center = start_y + (cell->h / 2);

	if (grid_num != 0 && x_center < data->grid_max_x && y_center < data->grid_max_y)
	{
		attron(COLOR_PAIR(color));
		//render ascii_digits if big enough
		if (cell->h >= 5 && cell->w >= max_digits * 3 + max_digits + 1) //ascii digit is size 3 + spaces between digits and spaces between start and end!
		{
			if (print_ascii_digits(grid_num, x_center, y_center))
				return (1);
		}
		else	/// if small grid render normal ascii chars
		{
			int textstart   = x_center - (digits / 2);
			move(y_center, textstart);
                printw("%u", grid_num);
		}
		attroff(COLOR_PAIR(color));
	}
	return (0);
}

int	color_grid(Data *data, Cell *cell)
{

	int		x = 0;
	int y = 0;
	int max_digits = getmax_digit(data);

	while (y < data->grid_size) // loops through each cell per col
	{
		x = 0;
		while (x < data->grid_size) // loops through each cell per row
		{
			if (color_cell(data, cell, x, y, max_digits))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void compute_cell_size(Data *data, Cell *cell)
{

    int usable_w = data->grid_max_x - (data->grid_size + 1);		//Calculate the usable width of the window for the grid.
    int usable_h = data->grid_max_y - (data->grid_size + 1);		//same for height

    if (usable_w < data->grid_size || usable_h < data->grid_size) // Safety check: if the usable area is smaller than the grid
    {
        cell->w = 12;
        cell->h = 6;
        return;
    }
	cell->w = usable_w / data->grid_size;					//calc usable cell witdh and height by dividing evenly
	cell->h = usable_h / data->grid_size;
	if (cell->w < 3)										//enforce minimum cellsize for cell_w and cell_h
	    cell->w = 12;
	if (cell->h < 3)
	    cell->h = 6;
}


int render_grid(Data *data, Cell *cell)
{
    attron(COLOR_PAIR(PGRID));
    getmaxyx(stdscr, data->grid_max_y, data->grid_max_x);
	compute_cell_size(data, cell);

	int grid = data->grid_size;

    clear();

    int y = 0;
    for (int row = 0; row < grid; row++)
    {

        int x = 0;
        for (int col = 0; col < grid; col++)
        {
            mvaddch(y, x++, '+');
            for (int i = 0; i < cell->w; i++)
                mvaddch(y, x++, '-');
        }
        mvaddch(y, x, '+');
        y++;


        for (int h = 0; h < cell->h; h++)
        {
            x = 0;
            for (int col = 0; col < grid; col++)
            {
                mvaddch(y, x++, '|');
                for (int i = 0; i < cell->w; i++){
                    mvaddch(y, x++, ' ');
				}
            }
            mvaddch(y, x, '|');
            y++;
        }
    }
    int x = 0;
    for (int col = 0; col < grid; col++)
    {
        mvaddch(y, x++, '+');
        for (int i = 0; i < cell->w; i++)
            mvaddch(y, x++, '-');
    }
    mvaddch(y, x, '+');
	attroff(COLOR_PAIR(PGRID));
	if (color_grid(data, &data->cell))
		return (1);		// fills cells with different colors
    refresh();
	return (0);
}

