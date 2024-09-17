/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:36 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 22:50:33 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	dda_calc(t_map *map)
{
	map->m_rays->x2 = (map->m_rays->x1 + 1000 * cos(map->m_rays->ray_angle));
	map->m_rays->y2 = (map->m_rays->y1 + 1000 * sin(map->m_rays->ray_angle));
	map->m_rays->dx = map->m_rays->x2 - map->m_rays->x1;
	map->m_rays->dy = map->m_rays->y2 - map->m_rays->y1;
	if (abs(map->m_rays->dx) > abs(map->m_rays->dy))
		map->m_rays->steps = abs(map->m_rays->dx);
	else
		map->m_rays->steps = abs(map->m_rays->dy);
	map->m_rays->xinc = map->m_rays->dx / (double)map->m_rays->steps;
	map->m_rays->yinc = map->m_rays->dy / (double)map->m_rays->steps;
}

int	dda_x(t_map *map, double *x, double *y)
{
	*x += map->m_rays->xinc;
	map->m_rays->rx = (map->player->pos.x + (*x - map->m_rays->x1)
			* TILE_SIZE / M_CUBE);
	map->m_rays->ry = (map->player->pos.y + (*y - map->m_rays->y1)
			* TILE_SIZE / M_CUBE);
	map->m_rays->map_x = (int)round(map->m_rays->rx) / TILE_SIZE;
	map->m_rays->map_y = (int)round(map->m_rays->ry) / TILE_SIZE;
	if (map->m_rays->map_x < 0 || map->m_rays->map_y < 0
		|| map->m_rays->map_x >= map->width
		|| map->m_rays->map_y >= map->height)
		return (1);
	if (map->arr[map->m_rays->map_y][map->m_rays->map_x] == '1'
		|| map->arr[map->m_rays->map_y][map->m_rays->map_x] == 'D')
		return (1);
	return (0);
}

int	dda_y(t_map *map, double *x, double *y)
{
	*y += map->m_rays->yinc;
	map->m_rays->rx = (map->player->pos.x + (*x - map->m_rays->x1)
			* TILE_SIZE / M_CUBE);
	map->m_rays->ry = (map->player->pos.y + (*y - map->m_rays->y1)
			* TILE_SIZE / M_CUBE);
	map->m_rays->map_x = (int)round(map->m_rays->rx) / TILE_SIZE;
	map->m_rays->map_y = (int)round(map->m_rays->ry) / TILE_SIZE;
	if (map->m_rays->map_x < 0 || map->m_rays->map_y < 0
		|| map->m_rays->map_x >= map->width
		|| map->m_rays->map_y >= map->height)
		return (1);
	if (map->arr[map->m_rays->map_y][map->m_rays->map_x] == '1'
		|| map->arr[map->m_rays->map_y][map->m_rays->map_x] == 'D')
		return (1);
	return (0);
}

void	draw_rays(t_map *map)
{
	t_mmap	mmap;

	1 && (map->m_rays = my_malloc(sizeof(t_ray), 0), mmap.j = 0, mmap.i = -1);
	1 && (map->m_rays->x1 = 5 * M_CUBE, map->m_rays->y1 = 3 * M_CUBE);
	map->m_rays->ray_angle = normangle(map->player->rotangle
			- map->player->fov / 2);
	while (++mmap.i < M_CUBE * 30)
	{
		42 && (mmap.x = map->m_rays->x1, mmap.y = map->m_rays->y1, mmap.j = 0);
		dda_calc(map);
		while (mmap.j < map->m_rays->steps)
		{
			if (dda_x(map, &mmap.x, &mmap.y))
				break ;
			if (dda_y(map, &mmap.x, &mmap.y))
				break ;
			if (round(mmap.x) >= 0 && round(mmap.x) < 300
				&& round(mmap.y) >= 0 && round(mmap.y) < 180)
				mlx_put_pixel(map->img, round(mmap.x), round(mmap.y),
					create_color(255, 255, 0, 255));
			mmap.j++;
		}
		map->m_rays->ray_angle = normangle(map->player->fov
				/ (30 * M_CUBE) + map->m_rays->ray_angle);
	}
}

void	get_color(t_mmap *mmap, t_map *map)
{
	if (mmap->y_start < 0 || mmap->x_start < 0
		|| mmap->y_start / M_CUBE >= map->height
		|| mmap->x_start / M_CUBE >= map->width)
		mmap->color = create_color(0, 0, 0, 255);
	else if (map->arr[mmap->y_start
			/ M_CUBE][mmap->x_start / M_CUBE] == '1')
		mmap->color = create_color(50, 50, 50, 255);
	else if (map->arr[mmap->y_start
			/ M_CUBE][mmap->x_start / M_CUBE] == 'D')
		mmap->color = create_color(0, 255, 0, 255);
	else if (map->arr[mmap->y_start
			/ M_CUBE][mmap->x_start / M_CUBE] == 'O')
		mmap->color = create_color(139, 0, 0, 255);
	else
		mmap->color = create_color(211, 211, 211, 255);
}
