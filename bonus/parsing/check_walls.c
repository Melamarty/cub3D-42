/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:37:39 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 13:37:39 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_row(char *row)
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

int	check_door(char **map, int i, int j, int height)
{
	int	c1;
	int	c2;

	c1 = 0;
	c2 = 0;
	if (i > 0 && map[i - 1][j] == '1')
		c1++;
	if (i < height - 1 && map[i + 1][j] == '1')
		c1++;
	if (j > 0 && map[i][j - 1] == '1')
		c2++;
	if (j < ft_strlen(map[i]) - 1 && map[i][j + 1] == '1')
		c2++;
	if (c1 == 2 && !c2)
		return (0);
	if (c2 == 2 && !c1)
		return (0);
	return (1);
}

int	check_inside(char **map, int height)
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
			if (map[i][j] == 'D' && check_door(map, i, j, height))
				return (1);
		}
	}
	return (0);
}

int	check_walls(char **map, int height)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
		if (check_row(map[i]))
			return (1);
	j = -1;
	if (check_inside(map, height) || check_player(map, height))
		return (1);
	return (0);
}
