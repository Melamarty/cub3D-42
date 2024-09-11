#include "parsing.h"

int allowed_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == ' ' || c == '*' || c == '\n' || c == 'W' || c == 'E' || c == 'D' || c == 'C'
		|| c == 'S')
		return (1);
	return (0);
}

//s
int	check_arr(t_map *map)
{
	int	i;
	int	j;
	char	c;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < ft_strlen(map->arr[i]))
		{
			c = map->arr[i][j];
			if (!allowed_char(c))
				return (printf("c = %d,  %d %d\n", c, i, j), 1);
			if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
			{
				map->player->pos.x = j;
				map->player->pos.y = i;
				map->player->dir = c;
				count++;
			}
			j++;
		}
		i++;
	}
	if (check_walls(map->arr, map->height, map->width) || count != 1)
		return(1);
	return (0);
}

int empty_line(char *line)
{
	int	i;

	i= 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != 13)
			return (0);
		i++;
	}
	return (1);
}

int check_line(char *line)
{
	int	i;
	char **spl;

	i = 0;
	spl = ft_split(line, ' ');
	if (!spl)
		return (1);
	while (spl[i++]);
	if (i != 3)
		return (printf ("here0 %d\n", i),1);
	if (ft_strcmp(spl[0], "NO") && ft_strcmp(spl[0], "SO")
		&& ft_strcmp(spl[0], "WE") && ft_strcmp(spl[0], "EA")
		&& ft_strcmp(spl[0], "F") && ft_strcmp(spl[0], "C"))
		return (printf ("here\n"),1);
	return (0);
}

int check_textures (t_list *list)
{
	while (list)
	{
		if (!list->checked && !empty_line(list->line))
		{
			if (check_line(list->line))
				return (1);
		}
		list = list->next;
	}
	return (0);
}