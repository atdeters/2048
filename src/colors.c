#include "../inc/colors.h"
#include "ncurses.h"

static short norm_color(short raw_color)
{
	return ((short)(((double)raw_color/256) * 1000));
}

void init_color_rgb(short col, short r, short g, short b)
{
	init_color(col, norm_color(r), norm_color(g), norm_color(b));
}

void init_color_hex(short pair, int hex)
{
	short r = (short)((hex>>16) & 0xFF);
	short g = (short)((hex>>8) & 0xFF);
	short b = (short)(hex & 0xFF);
	init_color(pair, norm_color(r), norm_color(g), norm_color(b));
}
