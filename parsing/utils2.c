/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:53:10 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/16 14:12:06 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int	set_checked(t_list *list)
{
	list->checked = 1;
	return (1);
}

char	*get_texture(char *line)
{
	char	**spl;

	spl = ft_split(line, ' ');
	if (!spl)
	{
		ft_putstr("external error", 2);
		exit (1);
	}
	return (spl[1]);
}

int	spl_len(char **spl)
{
	int	i;

	i = -1;
	while (spl[++i])
		;
	return (i);
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	if (empty_line(str))
		return (0);
	while (str[++i])
		if ((str[i] > '9' || str[i] < '0'))
			return (0);
	return (1);
}

void	optimize_map(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map->width)
	{
		i = 0;
		while (i < map->height && map->arr[i][j] == '*')
			i++;
		if (i != map->height)
			break ;
		i++;
	}
	printf ("j = %d\n", j);
	if (j > 0)
	{
		i = -1;
		while (++i < map->height)
			map->arr[i] = map->arr[i] + j;
	}
	if (get_player_pos(map))
	{
		ft_putstr("map error: no player\n", 2);
		exit (0);
	}
	map->width -= j;
}


