/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:30:10 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 17:18:12 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *new_ray, double ray_angle)
{
	new_ray->next = NULL;
	new_ray->is_door = 0;
	new_ray->is_close_door = 0;
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

void	its_horz(t_ray *new_ray, t_map *map)
{
	new_ray->x_inter = new_ray->h_x_inter;
	new_ray->y_inter = new_ray->h_y_inter;
	new_ray->ray_dis = new_ray->h_dis;
	new_ray->ray_dir = 1;
	if (map->arr[(new_ray->y_inter - new_ray->is_up)
			/ TILE_SIZE][(new_ray->x_inter) / TILE_SIZE] == 'D')
	{
		new_ray->is_door = 1;
		new_ray->x_door = (new_ray->x_inter) / TILE_SIZE;
		new_ray->y_door = (new_ray->y_inter - new_ray->is_up) / TILE_SIZE;
	}
}

void	its_vert(t_ray *new_ray, t_map *map)
{
	new_ray->x_inter = new_ray->v_x_inter;
	new_ray->y_inter = new_ray->v_y_inter;
	new_ray->ray_dis = new_ray->v_dis;
	new_ray->ray_dir = 2;
	if (map->arr[(new_ray->y_inter) / TILE_SIZE][(new_ray->x_inter
			+ new_ray->is_right - 1) / TILE_SIZE] == 'D')
	{
		new_ray->is_door = 1;
		new_ray->x_door = (new_ray->x_inter + new_ray->is_right - 1)
			/ TILE_SIZE;
		new_ray->y_door = (new_ray->y_inter) / TILE_SIZE;
	}
}

void	door_check(t_map *map, int z)
{
	if (z == WIDTH / 2 && (map->door_ray->is_door
			|| map->door_ray->is_close_door))
	{
		if (map->door_ray->is_door && map->door_ray->c_door_dis < 200)
			map->can_open = 1;
		else if (map->door_ray->is_close_door && map->door_ray->c_door_dis < 200
			&& map->door_ray->c_door_dis > 100)
			map->can_close = 1;
	}
}

void	cast_rays(t_map *map)
{
	int		z;
	double	ray_angle;

	42 && (map->can_close = 0, map->can_open = 0,
		map->door_ray = NULL, z = -1);
	ray_angle = normangle(map->player->rotangle - map->player->fov / 2);
	while (++z < WIDTH)
	{
		if (z == WIDTH / 2)
			map->door_ray = &map->rays[z];
		init_ray(&(map->rays[z]), ray_angle);
		check_horz(&map->rays[z], map);
		check_vert(&map->rays[z], map);
		map->rays[z].h_dis = calc_h_dis(*map, map->rays[z]);
		map->rays[z].v_dis = calc_v_dis(*map, map->rays[z]);
		if (map->rays[z].h_dis <= map->rays[z].v_dis)
			its_horz(&map->rays[z], map);
		else
			its_vert(&map->rays[z], map);
		door_check(map, z);
		ray_angle = normangle(map->player->fov / (WIDTH) + ray_angle);
	}
}
