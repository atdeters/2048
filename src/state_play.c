#include "../inc/state_play.h"
#include "../inc/game.h"
#include <stdint.h>
#include <ncursesw/curses.h>

static void compute_cell_size(Data *data, int *cell_w, int *cell_h)
{

    int usable_w = data->max_x - (data->grid_size + 1);		//Calculate the usable width of the window for the grid.
    int usable_h = data->max_y - (data->grid_size + 1);		//same for height

    if (usable_w < data->grid_size || usable_h < data->grid_size) // Safety check: if the usable area is smaller than the grid
    {
        *cell_w = 1;
        *cell_h = 1;
        return;
    }
	*cell_w = usable_w / data->grid_size;					//calc usable cell witdh and height by dividing evenly
	*cell_h = usable_h / data->grid_size;
	if (*cell_w < 3)										//enforce minimum cellsize for cell_w and cell_h
	    *cell_w = 3;
	if (*cell_h < 1)
	    *cell_h = 1;
}


void render_grid(Data *data)
{
    getmaxyx(stdscr, data->max_y, data->max_x);

    int cell_w;
    int cell_h;
    compute_cell_size(data, &cell_w, &cell_h);

    int grid = data->grid_size;

    clear();

    int y = 0;
    for (int row = 0; row < grid; row++)
    {

        int x = 0;
        for (int col = 0; col < grid; col++)
        {
            mvaddch(y, x++, '+');
            for (int i = 0; i < cell_w; i++)
                mvaddch(y, x++, '-');
        }
        mvaddch(y, x, '+');
        y++;


        for (int h = 0; h < cell_h; h++)
        {
            x = 0;
            for (int col = 0; col < grid; col++)
            {
                mvaddch(y, x++, '|');
                for (int i = 0; i < cell_w; i++)
                    mvaddch(y, x++, ' ');
            }
            mvaddch(y, x, '|');
            y++;
        }
    }


    int x = 0;
    for (int col = 0; col < grid; col++)
    {
        mvaddch(y, x++, '+');
        for (int i = 0; i < cell_w; i++)
            mvaddch(y, x++, '-');
    }
    mvaddch(y, x, '+');

    refresh();
}


void play(Data *data) {

    getmaxyx(stdscr, data->max_y, data->max_x);
    render_grid(data);

    while(true) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, data->max_y, data->max_x);
            render_grid(data);
            refresh();
        }
        if (DEBUG && ch == '0') {
            data->state = ST_MENU;
            return;
        }
		if (DEBUG && ch == '\x1B') {
            data->state = ST_EXIT;
            return;
        }

    }
}
