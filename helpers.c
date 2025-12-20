#include "helpers.h"

uint16_t min(uint16_t a, uint16_t b) {
    if (a < b)
        return a;
    return b;
}

int	is_power_of_2(unsigned int n)
{
	unsigned int	i;

	i = 1;
	while (i <= n)
	{
		if (i == n)
			return (1);
		i *= 2;
	}
	printf("Error\nWIN_VALUE is not a power of 2\n");
	return (0);
}
