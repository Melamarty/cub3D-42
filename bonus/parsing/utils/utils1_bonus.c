/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:14:43 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 15:14:43 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d_bonus.h"

int	ft_putstr(char *str, int fd)
{
	write(fd, str, ft_strlen (str));
	return (0);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n)
		i++;
	if (i == ft_strlen(str2))
		return (0);
	return (1);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while ((str1[i] || str2[i]))
	{
		if ((unsigned char) str1[i] != (unsigned char) str2[i])
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		i++;
	}
	return (0);
}

int	get_player_pos(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->arr[i][j] == 'N' || map->arr[i][j] == 'S'
				|| map->arr[i][j] == 'W' || map->arr[i][j] == 'E')
			{
				map->player->pos.x = j;
				map->player->pos.y = i;
				map->player->dir = map->arr[i][j];
				return (0);
			}
		}
	}
	return (1);
}
