/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:57:11 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/16 17:08:15 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*remove_chars(char *line)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] != 13 && line[i] != 10)
			j++;
	}
	res = my_malloc(j + 1, 0);
	j = -1;
	i = -1;
	while (line[++i])
	{
		if (line[i] != 13 && line[i] != 10)
			res[++j] = line[i];
	}
	res[++j] = '\0';
	return (res);
}

int	check_map(char *file, t_list **list)
{
	int		fd;
	char	*line;
	int		l;

	(void)list;
	l = ft_strlen(file);
	if (l < 5 || (file[--l] != 'b' || file[--l] != 'u'
			|| file[--l] != 'c' || file[--l] != '.'))
		return (1);
	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		add_line(list, remove_chars(line));
		line = get_next_line(fd);
	}
	return (0);
}
