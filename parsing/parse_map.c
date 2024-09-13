#include "parsing.h"

int set_checked(t_list *list)
{
	list->checked = 1;
	return (1);
}
char *get_texture(char *line)
{
	char **spl;
	
	spl = ft_split(line, ' ');
	return spl[1];
}

int spl_len(char **spl)
{
	int	i;

	i = -1;
	while (spl[++i]);
	return (i);
}

t_color *parse_color(char *line)
{
	char **colors;
	t_color *color;

	color = my_malloc(sizeof (t_color), 0);
	colors = ft_split(line, ',');
	if (spl_len(colors) != 3)
		return (NULL);
	color->r = ft_atoi(colors[0]);
	color->g = ft_atoi(colors[1]);
	color->b = ft_atoi(colors[2]);
	return (color);
}

char *full_line(char *line, int len)
{
	int	i;
	char	*res;

	res = my_malloc(len + 1, 0);
	i = -1;
	while (++i < len)
	{
		if (!line[i] || line[i] == ' ' || line[i] == '\n')
			res[i] = '*';
		else
			res[i] = line[i];
	}
	res [i + 1] = '\0';
	return (res);
}

void clear_map(t_map *map)
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
	// printf ("map height %d\nmap width %d\n", map->height, map->width);
	while (++i < map->height)
		map->arr[i] = full_line(map->arr[i], map->width);
}

void get_map(t_list *list, t_map *map)
{
	int	i;
	char *line;

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

char *rm_spaces(char *line)
{
    while (*line == ' ')
        line++;
	return line;
}

void set_null(t_map *map)
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

t_map *parse_map(t_list *list)
{
	t_map *map;


	map = my_malloc(sizeof(t_map), 0);
	set_null(map);
	while (list)
	{
		//printf ("%s",rm_spaces(list->line));
		if (!ft_strncmp(rm_spaces(list->line), "NO", 2))
			map->no = get_texture(rm_spaces(list->line));
		else if (!ft_strncmp(rm_spaces(list->line), "SO", 2) )
			map->so = get_texture(rm_spaces(list->line));
		else if (!ft_strncmp(rm_spaces(list->line), "WE", 2))
			map->we = get_texture(rm_spaces(list->line) );
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