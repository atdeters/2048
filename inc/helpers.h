#ifndef HELPERS_C
# define HELPERS_C

#include <stdint.h>
#include "stdio.h"
#include "data.h"

uint16_t min(uint16_t a, uint16_t b);
int	is_power_of_2(unsigned int n);
void add_nb_to_grid(Data *data, uint8_t field_nb, uint8_t value);

void test_filling_grid(Data *data);
void display_grid(Data *data);
void add_rnd(Data *data);
bool is_lost(Data *data);

#endif // ! HELPERS_C
