/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:17 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 13:31:17 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_comma(char *line)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			comma++;
	}
	return (comma);
}

t_color	*parse_color(char *line)
{
	char	**colors;
	t_color	*color;
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl || spl_len(spl) > 1)
		return (NULL);
	if (!spl[0] || check_comma(spl[0]) != 2)
		return (NULL);
	color = my_malloc(sizeof (t_color), 0);
	colors = ft_split(spl[0], ',');
	if (spl_len(colors) != 3)
		return (NULL);
	if (!is_digits(colors[0]) || !is_digits(colors[1]) || !is_digits(colors[2]))
		return (NULL);
	if (ft_strlen(colors[0]) > 3 || ft_strlen(colors[1]) > 3
		|| ft_strlen(colors[2]) > 3)
		return (NULL);
	color->r = ft_atoi(colors[0]);
	color->g = ft_atoi(colors[1]);
	color->b = ft_atoi(colors[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (NULL);
	return (color);
}

char	*full_line(char *line, int len)
{
	int		i;
	char	*res;

	res = my_malloc(len + 1, 0);
	i = -1;
	while (++i < len)
	{
		if (i < ft_strlen(line) && line[i] != ' ')
			res[i] = line[i];
		else
			res[i] = '*';
	}
	res [i + 1] = '\0';
	return (res);
}

void	clear_map(t_map *map)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (++i < map->height)
	{
		if (tmp < ft_strlen(map->arr[i]))
			tmp = ft_strlen(map->arr[i]);
	}
	i = -1;
	map->width = tmp;
	i = -1;
	while (++i < map->height)
		map->arr[i] = full_line(map->arr[i], map->width);
}

t_map	*parse_map(t_list *list)
{
	t_map	*map;

	map = my_malloc(sizeof(t_map), 0);
	set_null(map);
	while (list)
	{
		if (!ft_strncmp(rm_spaces(list->line), "NO", 2))
			map->no = get_texture(rm_spaces(list->line));
		else if (!ft_strncmp(rm_spaces(list->line), "SO", 2))
			map->so = get_texture(rm_spaces(list->line));
		else if (!ft_strncmp(rm_spaces(list->line), "WE", 2))
			map->we = get_texture(rm_spaces(list->line));
		else if (!ft_strncmp(rm_spaces(list->line), "EA", 2))
			map->ea = get_texture(rm_spaces(list->line));
		else if (rm_spaces(list->line)[0] == 'F')
			map->floor = parse_color(rm_spaces(list->line) + 2);
		else if (rm_spaces(list->line)[0] == 'C')
			map->ceiling = parse_color(rm_spaces(list->line) + 2);
		else if (ft_strchr(list->line, '1') || ft_strchr(list->line, '0'))
			return (get_map(list, map), map);
		list = list->next;
	}
	return (map);
}
