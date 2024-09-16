/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:17:12 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 13:17:12 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	allowed_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == ' ' || c == '*'
		|| c == '\n' || c == 'W' || c == 'E' || c == 'D' || c == 'O'
		|| c == 'S')
		return (1);
	return (0);
}

int	check_arr(t_map *map)
{
	int				i;
	int				j;
	char			c;
	static int		count;

	i = -1;
	map->player = my_malloc(sizeof(t_player), 0);
	while (++i < map->height)
	{
		j = -1;
		while (++j < ft_strlen(map->arr[i]))
		{
			c = map->arr[i][j];
			if (!allowed_char(c))
				return (1);
			if ((c == 'S' || c == 'N' || c == 'W' || c == 'E'))
				++count;
		}
	}
	if (check_walls(map->arr, map->height, map->width) || count != 1)
		return (1);
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != 13)
			return (0);
		i++;
	}
	return (1);
}

int	check_line(char *line)
{
	int		i;
	char	**spl;

	i = 0;
	spl = ft_split(line, ' ');
	if (!spl)
		return (1);
	while (spl[i++])
		;
	if (i != 3 && (ft_strcmp(spl[0], "F") && ft_strcmp(spl[0], "C")))
		return (1);
	if (ft_strcmp(spl[0], "NO") && ft_strcmp(spl[0], "SO")
		&& ft_strcmp(spl[0], "WE") && ft_strcmp(spl[0], "EA")
		&& ft_strcmp(spl[0], "F") && ft_strcmp(spl[0], "C"))
		return (1);
	return (0);
}

int	check_textures(t_map *map, t_list *list)
{
	int	i;

	i = 0;
	if (!map->ea || !map->no || !map->so || !map->we
		|| !map->floor || !map->ceiling)
		return (1);
	while (list)
	{
		if (!list->checked && !empty_line(list->line))
		{
			if (check_line(list->line))
				return (1);
			i++;
		}
		list = list->next;
	}
	if (i != 6)
		return (1);
	return (0);
}
