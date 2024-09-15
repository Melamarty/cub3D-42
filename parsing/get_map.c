/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:36:10 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 13:37:20 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing.h"

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
		if (!empty_line(list->line))
			map->arr[i++] = ft_strdup(line);
		list = list->next;
	}
	clear_map(map);
}
