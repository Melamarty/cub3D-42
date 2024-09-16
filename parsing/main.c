#include "../cub3d.h"

void print_map(char **map, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		printf("%s\n", map[i]);
}

void print_info(t_map *map)
{
    printf ("width = %d\n", map->width);
	printf ("height = %d\n", map->height);
	print_map(map->arr, map->height);
}

char *remove_chars(char *line)
{
    int i;
    int j;
    char *res;

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
        if (line[i] != 13 && line[i] != 10 )
            res[++j] = line[i];
    }
    res[++j] = '\0';
    return (res);
}

int check_map(char *file, t_list **list)
{
    int fd;
    char *line;
    int l;

    (void)list;
    l = ft_strlen(file);
    if (l < 5 || (file[--l] != 'b' || file[--l] != 'u' || file[--l] != 'c' || file[--l] != '.'))
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

void    open_win(t_map *map)
{
    map->bullet_nb = 9;
    map->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
    map->bullet_img = mlx_texture_to_image(map->mlx, map->bullet[map->bullet_nb]);
	mlx_image_to_window(map->mlx, map->bullet_img, WIDTH - 100, HEIGHT - 100);
}

int main (int ac, char **av)
{
    t_map *map;
    t_list *list = NULL;

    map = my_malloc(sizeof(t_map), 0);
    if (ac != 2)
    {
        ft_putstr("arguments errror\n", 2);
        return (0);
    }
    if (check_map(av[1], &list))
    {
        ft_putstr("map or file error 1\n", 2);
        return (0);
    }
    map = parse_map(list);
    map->player = my_malloc(sizeof(t_player), 0);
    if (check_arr(map) || check_textures(map, list))
    {
        ft_putstr("map  error\n", 2);
        return (0);
    }
    //print_info(map);
    optimize_map(map);
    //print_info(map);
    // print_info(map);
    // print_list(list);
    create_textures(map);
    open_win(map);
    init_player(map);
    cast_rays(map);
    // while (map->rays)
    // {
    //     printf ("djdgdvd\n");
    //     map->rays = map->rays->next;
    // }
    map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[0]);
    render(map);
	mlx_image_to_window(map->mlx, map->sprite_img, WIDTH - 666 - ((WIDTH - 666) / 2), HEIGHT - 375);
    mini_map(map);
	mlx_loop_hook(map->mlx, &handle_key, map);
    mlx_loop_hook(map->mlx, &animation, map);
    mlx_cursor_hook(map->mlx, &mouse_handler, map);
    mlx_loop_hook(map->mlx, &mouse_rot, map);
    mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
    return (0);
}
