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

#include "../cub3d_bonus.h"

void	open_win(t_map *map)
{
	map->bullet_nb = 9;
	map->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!map->mlx)
		clear_all(map);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
		clear_all(map);
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
		clear_all(map);
	map->bullet_img = mlx_texture_to_image(map->mlx,
			map->bullet[map->bullet_nb]);
	if (mlx_image_to_window(map->mlx, map->bullet_img,
			WIDTH - 100, HEIGHT - 100) == -1)
		clear_all(map);
}

void	setup_map(t_map *map)
{
	optimize_map(map);
	create_textures(map);
	open_win(map);
	init_player(map);
	cast_rays(map);
	map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[0]);
	render(map);
	mlx_image_to_window(map->mlx, map->sprite_img,
		WIDTH - 666 - ((WIDTH - 666) / 2), HEIGHT - 375);
	mini_map(map);
	mlx_loop_hook(map->mlx, &handle_key, map);
	mlx_loop_hook(map->mlx, &animation, map);
	mlx_cursor_hook(map->mlx, &mouse_handler, map);
	mlx_loop_hook(map->mlx, &mouse_rot, map);
	mlx_loop(map->mlx);
	clear_all(map);
	mlx_terminate(map->mlx);
}

int	main(int ac, char **av)
{
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
