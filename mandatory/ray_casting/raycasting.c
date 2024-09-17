/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:30:10 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 20:48:29 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *new_ray, double ray_angle)
{
	new_ray->ray_angle = ray_angle;
	new_ray->is_up = 1;
	if (ray_angle > 0 && ray_angle < M_PI)
		new_ray->is_up = 0;
	new_ray->is_right = 1;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		new_ray->is_right = 0;
	new_ray->found_x_inter = 0;
	new_ray->found_y_inter = 0;
}

void	its_horz(t_ray *new_ray)
{
	new_ray->x_inter = new_ray->h_x_inter;
	new_ray->y_inter = new_ray->h_y_inter;
	new_ray->ray_dis = new_ray->h_dis;
	new_ray->ray_dir = 1;
}

void	its_vert(t_ray *new_ray)
{
	new_ray->x_inter = new_ray->v_x_inter;
	new_ray->y_inter = new_ray->v_y_inter;
	new_ray->ray_dis = new_ray->v_dis;
	new_ray->ray_dir = 2;
}

void	cast_rays(t_map *map)
{
	int		z;
	double	ray_angle;

	z = -1;
	ray_angle = normangle(map->player->rotangle - map->player->fov / 2);
	while (++z < WIDTH)
	{
		init_ray(&(map->rays[z]), ray_angle);
		check_horz(&map->rays[z], map);
		check_vert(&map->rays[z], map);
		map->rays[z].h_dis = calc_h_dis(*map, map->rays[z]);
		map->rays[z].v_dis = calc_v_dis(*map, map->rays[z]);
		if (map->rays[z].h_dis <= map->rays[z].v_dis)
			its_horz(&map->rays[z]);
		else
			its_vert(&map->rays[z]);
		ray_angle = normangle(map->player->fov / (WIDTH) + ray_angle);
	}
}
