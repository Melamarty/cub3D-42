/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:48 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 14:36:28 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_rot(void *p)
{
	t_map	*map;

	map = (t_map *)p;
	if (map->is_rot == 1)
	{
		cast_rays(map);
		render(map);
		mini_map(map);
		map->is_rot = 0;
	}
}

void	mouse_handler(double x, double y, void *p)
{
	t_map	*map;
	int		half_width;

	map = (t_map *)p;
	if (map->is_rot == 2)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	half_width = WIDTH / 2;
	if (x > half_width)
	{
		map->player->rotAngle = normangle(map->player->rotAngle
				+ map->player->rotSpeed);
		map->is_rot = 1;
	}
	else
	{
		map->player->rotAngle = normangle(map->player->rotAngle
				- map->player->rotSpeed);
		map->is_rot = 1;
	}
	mlx_set_mouse_pos(map->mlx, half_width, HEIGHT / 2);
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
}
