#ifndef  COLORS_H
# define COLORS_H

// Just macros for the different colors
#define COL1 0x007BA7   // Figma: Cerulean
#define COL2 0xFFC067   // Figma: Pastel Orange
#define COL3 0x98A869   // Figma: Green Sage
#define COL4 0xC11C84   // Figma: Dark Pink
#define COL5 0xCD1C18   // Figma: Chili Red
#define COL6 0x6D8196   // Figma: Slate Gray
#define COL7 0x2E6F40   // Figma: Forrest Green
#define COL8 0x636B2F   // Firma: Olive Green
#define COL9 0x4682B4   // Figma: Steel Blue
#define COL10 0xF88379  // Figma: Coral Pink
#define COL11 0xFFA6C9  // Figma: Carnation Pink
#define COL12 0xE40078  // Figma: Red Purple
#define COL13 0xE4D00A  // Figma: Citrine Color
#define COL14 0xE4D96F  // Figma: Straw
#define COL15 0xFA5053  // Figma: Strawberry
#define COL16 0x873260  // Figma: Boysenberry
#define COL_BACK 0x000000

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
    BACKGROUND
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
    PBACK
};

void init_color_rgb(short col, short r, short g, short b);
void init_color_hex(short pair, int hex);

#endif // ! COLORS_H

