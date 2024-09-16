/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:28:59 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/15 19:38:03 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	create_textures(t_map *map)
{
	int	i;

	i = 0;
	map->timing = 0;
	map->is_reload = 0;
	map->is_shot = 0;
	while (i < 31)
	{
		map->sprite[i] = mlx_load_png(
				ft_strjoin(ft_strjoin("./textures/bonus/frame",
						ft_itoa(i + 1)), ".png"));
		i++;
	}
	i = 0;
	while (i < 10)
	{
		map->bullet[i] = mlx_load_png(
				ft_strjoin(ft_strjoin("./textures/bonus/bullet",
						ft_itoa(i + 1)), ".png"));
		i++;
	}
}

void	put_frame(t_map *map)
{
	mlx_delete_image(map->mlx, map->sprite_img);
	map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[map->frame]);
	mlx_image_to_window(map->mlx, map->sprite_img,
		WIDTH - 666 - ((WIDTH - 666) / 2), HEIGHT - 375);
}

void	shot(t_map *map)
{
	if (map->bullet_nb == 0)
	{
		map->is_shot = 0;
		return ;
	}
	put_frame(map);
	if (map->frame == 6)
	{
		map->frame = 0;
		map->is_shot = 0;
		map->bullet_nb --;
		mlx_delete_image(map->mlx, map->bullet_img);
		map->bullet_img = mlx_texture_to_image(map->mlx,
				map->bullet[map->bullet_nb]);
		mlx_image_to_window(map->mlx, map->bullet_img,
			WIDTH - 100, HEIGHT - 100);
	}
	else
		map->frame += 1;
}

void	reload(t_map *map)
{
	if (map->bullet_nb)
	{
		map->is_reload = 0;
		return ;
	}
	if (map->timing == 4)
	{
		put_frame(map);
		if (map->frame == 30)
		{
			map->frame = 0;
			map->timing = 0;
			map->is_reload = 0;
			map->bullet_nb = 9;
			mlx_delete_image(map->mlx, map->bullet_img);
			map->bullet_img = mlx_texture_to_image(map->mlx,
					map->bullet[map->bullet_nb]);
			mlx_image_to_window(map->mlx,
				map->bullet_img, WIDTH - 100, HEIGHT - 100);
		}
		else
			map->frame += 1;
		map->timing = 0;
	}
	map->timing += 1;
}

void	animation(void *p)
{
	t_map	*map;

	map = (t_map *)p;
	if (map->is_reload)
		reload(map);
	else if (map->is_shot)
		shot(map);
}
