#include <ncurses.h>
#include <stdint.h>
#include "../inc/render_grid.h"
#include <ncursesw/curses.h>
#include "../inc/colors.h"


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

void	color_cell(unsigned int grid_num, Cell *cell, int x, int y)
{
	int start_x = 1 + x * (cell->w + 1);
	int start_y = 1 + y * (cell->h + 1);

/*  	printw("\n\nstart: %i\tend:%i\n", start, end);*/
	short color = get_color(grid_num);

	move(start_y, start_x);
	for (int row = 0; row < cell->h; row++){
		move(start_y + row, start_x);
		chgat(cell->w, A_NORMAL, color, NULL);
	}
}

void	color_grid(Data *data, Cell *cell)
{

	int		x = 0;
	int y = 0;

	while (y < data->grid_size) // loops through each cell per col
	{
		x = 0;
		while (x < data->grid_size) // loops through each cell per row
		{
			color_cell(data->grid[y][x], cell, x, y);
			x++;
		}
		y++;
	}
	// Loop through col 0 - grid_size - 1
	// col 1 --> start from 1st row till cell
	return ;
}


static void compute_cell_size(Data *data, Cell *cell)
{

    int usable_w = data->grid_max_x - (data->grid_size + 1);		//Calculate the usable width of the window for the grid.
    int usable_h = data->grid_max_y - (data->grid_size + 1);		//same for height

    if (usable_w < data->grid_size || usable_h < data->grid_size) // Safety check: if the usable area is smaller than the grid
    {
        cell->w = 8 ;
        cell->h = 4;
        return;
    }
	cell->w = usable_w / data->grid_size;					//calc usable cell witdh and height by dividing evenly
	cell->h = usable_h / data->grid_size;
	if (cell->w < 3)										//enforce minimum cellsize for cell_w and cell_h
	    cell->w = 8;
	if (cell->h < 3)
	    cell->h = 4;
}


void render_grid(Data *data, Cell *cell)
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
	color_grid(data, &data->cell);				// fills cells with different colors
    attroff(COLOR_PAIR(PGRID));
    refresh();
}

