#ifndef  COLORS_H
# define COLORS_H

// These are set to a ceratin rgb value
enum e_colors {
    CL1 = 9,
    CL2,
    CL3,
    CL4,
    CL5,
    CL6,
    CL7,
    CL8,
    CL9,
    CL10,
    CL11,
    CL12,
    CL13,
    CL14,
    CL15,
    CL16,
    BACKGROUND,
    GRID,
    FONT1,
    FONT2,
};

// These are a mix of background and foreground color
enum e_pairs {
    P1 = 1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7,
    P8,
    P9,
    P10,
    P11,
    P12,
    P13,
    P14,
    P15,
    P16,
    PBACK,
    PGRID
};

void init_color_rgb(short col, short r, short g, short b);
void init_color_hex(short pair, int hex);

#endif // ! COLORS_H

