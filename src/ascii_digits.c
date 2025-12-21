#include "../inc/ascii_digits.h"



const char	**get_ascii_digit(unsigned int digit)
{

	static const char *g_ascii_digits[10][4] =
	{
		/* 0 */
		{
			" _ ",
			"| |",
			"|_|",
			NULL
		},

		/* 1 */
		{
			"  ",
			"/|",
			" |",
			NULL
		},

		/* 2 */
		{
			" _ ",
			" _|",
			"|_ ",
			NULL
		},

		/* 3 */
		{
			" _ ",
			" _|",
			" _|",
			NULL
		},

		/* 4 */
		{
			"   ",
			"|_|",
			"  |",
			NULL
		},

		/* 5 */
		{
			" _ ",
			"|_ ",
			" _|",
			NULL
		},

		/* 6 */
		{
			" _ ",
			"|_ ",
			"|_|",
			NULL
		},

		/* 7 */
		{
			" _ ",
			"  |",
			"  |",
			NULL
		},

		/* 8 */
		{
			" _ ",
			"|_|",
			"|_|",
			NULL
		},

		/* 9 */
		{
			" _ ",
			"|_|",
			" _|",
			NULL
		}
	};

	return (g_ascii_digits[digit]);
}

static void	safe_cleanup(char *num, char **ascii_arr, char *line)
{
	if (line)
		free(line);
	if (ascii_arr)
		free_split(ascii_arr);
	if (num)
		free(num);
}

int	print_ascii_digits(unsigned int nb, int x_center, int y_center)
{
	char		*num;
	int			i;
	int			j;
	int			len;
	char		*line;
	char		*new_line;
	const char	**glyph;
	char		**ascii_arr;



	num = ft_itoa((int)nb);
	if (!num)
		exit(1);

	len = 0;
	while (num[len])
		len++;

	ascii_arr = ft_calloc(4, sizeof(char *));
	if (!ascii_arr)
	{
		safe_cleanup(num, NULL, NULL);
		return (1);
	}
	i = 0;
	while (i < 3)   ///each ascii art row
	{
		line = NULL;
		j = 0;
		while (j < len) //len = number of digits
		{
			int d = num[j] - '0';
			if (d < 0 || d > 9)
			{
				safe_cleanup(num, ascii_arr, line);
				return (1);
			}
			glyph = get_ascii_digit(d);
			if (!glyph || !glyph[i])
			{
				safe_cleanup(num, ascii_arr, line);
				return (1);
			}

			//////////////// append glyph row
			if (!line)
			{
				line = ft_strdup(glyph[i]);
				if (!line)
				{
					safe_cleanup(num, ascii_arr, NULL);
					return (1);
				}
			}
			else
			{
				new_line = ft_strjoin(line, glyph[i]);
				free(line);
				line = new_line;
				if (!line)
				{
					safe_cleanup(num, ascii_arr, NULL);
					return (1);
				}
			}

			////append space between digits (not after last digit)
			if (j != len - 1)
			{
				new_line = ft_strjoin(line, " ");
				free(line);
				line = new_line;
				if (!line)
				{
					safe_cleanup(num, ascii_arr, NULL);
					return (1);
				}
			}
			j++;
		}
		ascii_arr[i] = line;
		i++;
	}

	//print_split(ascii_arr);
	i = 0;
	int x_start   = x_center - (ft_strlen(ascii_arr[0]) / 2);
	int y_start = y_center - 2;

	while(i < 3)
	{
		move(y_start + i, x_start);
		printw("%s", ascii_arr[i]);
		i++;
	}
	free_split(ascii_arr);
	free(num);
	return (0);
}
