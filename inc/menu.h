#ifndef MENU_H
# define MENU_H

# include "data.h"

# define MENU_MAIN_FIELDS_ON 4 // Cannot be smaller than 2
# define MENU_MAIN_FIELDS_OFF 3 // Cannot be smaller than 2
# define SETTINGS_FIELDS 4
# define MENU_WIDTH 30

// TODO: Make these part of a theme!
# define PUIHL P2
# define PUINHL 0

void print_border(unsigned int len);
void print_botton(char *name, char *buttons, bool highlight);
void render_menu_off(Data *data);
void render_menu_on(Data *data);
void print_label(const char *label);

#endif // !MENU_H

