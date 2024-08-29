#include "parsing.h"

int check_row(char *row)
{
	int	i;

	i = 0;
	while (row[i] == '*')
		i++;
	if (row[i] != '1')
		return (1);
	i = ft_strlen(row) - 1;
	while (row[i] == '*')
		i--;
	if (row[i] != '1')
		return (1);
	return (0);
}

int check_inside(char **map, int height)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '*')
			{
				if (i > 0 && map[i - 1][j] == '0')
					return (1);
				if (i < height - 1 && map[i + 1][j] == '0')
					return (1);
				if (j > 0 && map[i][j - 1] == '0')
					return (1);
				if (j < ft_strlen(map[i]) - 1 && map[i][j + 1] == '0')
					return (1);
			}
		}
	}
	return (0);
}
int check_walls(char **map, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		if (check_row(map[i]))
			return (1);
	}
	j = -1;
	while (++j < width)
	{
		i = 0;
		while (i < height && map[i][j] == '*')
			i++;
		// printf ("%c %d %d\n", map[i][j], i, j);
		if (i >= height || map[i][j] != '1')
			return (printf("here %d %d \n", i, j), 1);
		i = height - 1;
		while (i >= 0 && map[i][j] == '*')
			i--;

		if (i < 0 || map[i][j] != '1')
			return (printf("here1\n"), 1);
	}
	if (check_inside(map, height))
		return (1);
	return (0);
}