#include "state_play.h"
#include "game.h"
#include <stdint.h>
#include <ncursesw/curses.h>

int	get_end(int nb, Cell *cell)
{
	if (nb == 0)
		return(cell->h);
	if (nb == 1)
		return(2 * cell->h + 1);
	if (nb == 2)
		return(3 * cell->h + 2);
	if (nb == 3)
		return(4 * cell->h + 3);
	else
		return(5 * cell->h + 4);

}

int	get_start(int nb, Cell *cell)
{
	if (nb == 0)
		return(0);
	if (nb == 1)
		return(cell->w + 1);
	if (nb == 2)
		return(2 * cell->w + 2);
	if (nb == 3)
		return(3 * cell->w + 3);
	else
		return(4 * cell->w + 4);
}

void	color_cell(Data *data, unsigned int grid_num, Cell *cell, int x, int y)
{
	int j = 0;
	int i = get_end(y, cell);
	(void) grid_num;
	(void) data;


	while (i <= cell->h)
	{
		j = get_start(x, cell);
		while (j <= cell->w)
		{

			j++;
		}
		i++;
	}
	return ;
}



void	color_grid(Data *data, Cell *cell)
{
	(void) data;
	(void) cell;
	int		x = 0;
	int y = 0;

	while (y < data->grid_size - 1) // loops through each cell per col
	{
		x = 0;
		while (x < data->grid_size - 1) // loops through each cell per row
		{
			color_cell(data, data->grid[y][x], cell, x, y);
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

    refresh();
}

