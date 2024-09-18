/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:05:59 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/16 17:05:59 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	open_win(t_map *map)
{
	map->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!map->mlx)
		clear_all(map);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
		clear_all(map);
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
		clear_all(map);
}

void	setup_map(t_map *map)
{
	optimize_map(map);
	open_win(map);
	init_player(map);
	cast_rays(map);
	render(map);
	mlx_loop_hook(map->mlx, &handle_key, map);
	mlx_loop(map->mlx);
	clear_all(map);
	mlx_terminate(map->mlx);
}

void ft_exit(void)
{
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	atexit(ft_exit);
	t_map	*map;
	t_list	*list;

	list = NULL;
	map = my_malloc(sizeof(t_map), 0);
	if (ac != 2)
		return (ft_putstr("Error\nargs\n", 2), 0);
	if (check_map(av[1], &list))
		return (ft_putstr("Erorr\nfile\n", 2), 0);
	map = parse_map(list);
	if (check_arr(map) || check_textures(map, list))
		return (ft_putstr("Error\nmap\n", 2), 0);
	setup_map(map);
	return (0);
}
