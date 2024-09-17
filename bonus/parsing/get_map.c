/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:53:03 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/17 21:12:23 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*rm_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

void	set_null(t_map *map)
{
	map->so = NULL;
	map->no = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->texture = my_malloc(sizeof (t_texture), 0);
	map->texture->no = NULL;
	map->texture->so = NULL;
	map->texture->ea = NULL;
	map->texture->we = NULL;
	map->texture->door = NULL;
}

void	get_map(t_list *list, t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	map->height = lst_len(&list);
	map->arr = my_malloc(map->height * sizeof(char *), 0);
	while (list)
	{
		if (empty_line(list->line))
		{
			ft_putstr("map error: empty line\n", 2);
			exit (0);
		}
		list->checked = 1;
		line = list->line;
		map->arr[i++] = ft_strdup(line);
		list = list->next;
	}
	clear_map(map);
}

int	check_player(char **map, int height)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (i <= 0 || i >= height - 1 || j <= 0
					|| j >= ft_strlen(map[i]) - 1)
					return (1);
				if (map[i - 1][j] == '*' || map[i + 1][j] == '*'
					|| map[i][j - 1] == '*' || map[i][j + 1] == '*')
					return (1);
			}
		}
	}
	return (0);
}
