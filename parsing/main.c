#include "parsing.h"

void print_info(t_map *map)
{
    printf ("map width : %d\n", map->width);
    printf ("map height: %d\n", map->height);
    // printf("----- map info -----\n");
    // printf("NO : %s\n", map->no);
    // printf("SO : %s\n", map->so);
    // printf("WE : %s\n", map->we);
    // printf("EA : %s\n", map->ea);
    // printf("floor color : %d, %d, %d\n", map->floor.r, map->floor.g, map->floor.b);
    // printf("ceiling color : %d, %d, %d\n", map->ceiling.r, map->ceiling.g, map->ceiling.b);
    // printf("=========map==========\n");
    // int i = 0;
    // while (i < map->height)
    // {
    //     printf ("-%s-\n", map->arr[i]);
    //     i++;
    // }
    printf ("player position : (x: %d, y: %d)\n", map->player->pos.x, map->player->pos.y);
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
    map->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	map->img = mlx_new_image(map->mlx, map->width * cube_width, map->height * cube_width);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
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
    if (check_arr(map) || check_textures(list))
    {
        ft_putstr("map  error\n", 2);
        return (0);
    }
    // print_info(map);
    // print_list(list);
    open_win(map);
    init_player(map);
    cast_rays(map);
    // while (map->rays)
    // {
    //     printf ("djdgdvd\n");
    //     map->rays = map->rays->next;
    // }
    map->texture = my_malloc(sizeof (t_texture), 0);
    map->texture->no = NULL;
    map->texture->so = NULL;
    render(map);
    mini_map(map);
	mlx_loop_hook(map->mlx, &handle_key, map);
    mlx_cursor_hook(map->mlx, &mouse_handler, map);
    mlx_loop_hook(map->mlx, &mouse_rot, map);
    mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
    return (0);
}
