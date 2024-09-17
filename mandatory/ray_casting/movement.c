/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:30:01 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 20:45:27 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall(int new_x, int new_y, t_map map)
{
	double	ang;
	int		px;
	int		py;
	int		i;

	i = 0;
	ang = map.player->rotangle;
	while (i < 360)
	{
		px = (new_x) + 70 * cos(ang);
		py = (new_y) + 70 * sin(ang);
		ang += 180 / M_PI;
		if (px < 0 || px / TILE_SIZE >= map.width || py < 0
			|| py / TILE_SIZE >= map.height
			|| map.arr[py / TILE_SIZE][px / TILE_SIZE] == '1')
			return (1);
		i++;
	}
	return (0);
}

void	key_move(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player->rotangle = normangle(map->player->rotspeed
				+ map->player->rotangle);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player->rotangle = normangle(map->player->rotangle
				- map->player->rotspeed);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP))
		up(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		down(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		left(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		right(map);
}

int	key_listenter(t_map *map)
{
	if (!key_pressed(map))
		return (0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		clear_all(map);
	key_move(map);
	rerender(map);
	return (0);
}

void	handle_key(void *p)
{
	t_map	*map;

	map = (t_map *)p;
	key_listenter(map);
}

int	key_pressed(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_A)
		|| mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D)
		|| mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(map->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		return (1);
	return (0);
}
