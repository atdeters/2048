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
    BACKFONT,
    GRID,
};

// These are a mix of background and foreground color
enum e_pairs {
    PBACK = 1,
    PGRID,
    P2,
    P4,
    P8,
    P16,
    P32,
    P64,
    P128,
    P256,
    P512,
    P1024,
    P2048,
    P4096,
    P8192,
    P16384,
    P32768,
    P65536
};

void init_color_rgb(short col, short r, short g, short b);
void init_color_hex(short pair, int hex);

#endif // ! COLORS_H

