/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:42 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/15 18:31:27 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	render_map(t_map *map)
{
	t_mmap	mmap;

	mmap.x_start = (map->player->pos.x - (5 * TILE_SIZE)) * m_cube / TILE_SIZE;
	mmap.y_start = (map->player->pos.y - (3 * TILE_SIZE)) * m_cube / TILE_SIZE;
	42 && (mmap.y_start_save = mmap.y_start, mmap.i = -1);
	while (++mmap.i < 10 * m_cube)
	{
		mmap.y_start = mmap.y_start_save;
		mmap.j = 0;
		while (mmap.j < 6 * m_cube)
		{
			get_color(&mmap, map);
			mlx_put_pixel(map->img, mmap.i, mmap.j, mmap.color);
			mmap.y_start ++;
			mmap.j++;
		}
		mmap.x_start ++;
	}
}

void	render_player(t_map *map)
{
	t_mmap	mmap;

	mmap.x_start = 5 * m_cube - 5;
	mmap.y_start = 3 * m_cube - 5;
	mmap.color = create_color(255, 0, 0, 255);
	mmap.i = 0;
	mmap.j = 0;
	while (mmap.i < 10)
	{
		mmap.j = 0;
		while (mmap.j < 10)
		{
			mlx_put_pixel(map->img, mmap.x_start + mmap.j,
				mmap.y_start + mmap.i, mmap.color);
			mmap.j ++;
		}
		mmap.i ++;
	}
	draw_rays(map);
}

void	draw_cercle(t_map *map)
{
	int		px;
	int		py;
	double	ang;
	int		i;

	ang = map->player->rotAngle;
	i = 0;
	while (i < 360)
	{
		px = (5 * m_cube) + 10 * cos(ang);
		py = (3 * m_cube) + 10 * sin(ang);
		ang += 180 / M_PI;
		mlx_put_pixel(map->img, px, py, create_color(255, 255, 255, 51));
		i++;
	}
}

void	mini_map(t_map *map)
{
	render_map(map);
	render_player(map);
	draw_cercle(map);
}
