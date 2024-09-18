/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_cast_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:30 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/18 14:26:01 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	calc_horz(t_ray *new_ray, t_map *map)
{
	new_ray->f_y_inter = (map->player->pos.y / TILE_SIZE) * TILE_SIZE;
	if (!new_ray->is_up)
		new_ray->f_y_inter += TILE_SIZE;
	new_ray->f_x_inter = map->player->pos.x
		+ (new_ray->f_y_inter - map->player->pos.y) / tan(new_ray->ray_angle);
	new_ray->y_steps = TILE_SIZE;
	if (new_ray->is_up)
		new_ray->y_steps *= -1;
	new_ray->x_steps = TILE_SIZE / tan(new_ray->ray_angle);
	if (!new_ray->is_right && new_ray->x_steps > 0)
		new_ray->x_steps *= -1;
	if (new_ray->is_right && new_ray->x_steps < 0)
		new_ray->x_steps *= -1;
}

int	horz_hit(t_ray *new_ray, t_map *map)
{
	if (map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
		/ TILE_SIZE][(int)(new_ray->f_x_inter)
		/ TILE_SIZE] == 'O')
	{
		new_ray->is_close_door = 1;
		new_ray->c_door_dis = calc_d_dis(*map, *new_ray, 1);
		new_ray->x_door = (new_ray->f_x_inter) / TILE_SIZE;
		new_ray->y_door = (new_ray->f_y_inter - new_ray->is_up)
			/ TILE_SIZE;
	}
	if (map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
		/ TILE_SIZE][(int)(new_ray->f_x_inter)
		/ TILE_SIZE] == '1'
	|| map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
		/ TILE_SIZE][(int)(new_ray->f_x_inter) / TILE_SIZE] == 'D')
	{
		if (map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
			/ TILE_SIZE][(int)(new_ray->f_x_inter) / TILE_SIZE] == 'D' && map->door_ray)
			map->door_ray->c_door_dis = calc_d_dis(*map, *map->door_ray, 1);
		new_ray->found_x_inter = 1;
		return (1);
	}
	return (0);
}

void	check_horz(t_ray *new_ray, t_map *map)
{
	calc_horz(new_ray, map);
	while (1 && new_ray->f_y_inter < map->height * TILE_SIZE
		&& new_ray->f_x_inter < map->width * TILE_SIZE
		&& new_ray->f_x_inter >= 0
		&& new_ray->f_y_inter >= 0)
	{
		new_ray->h_x_inter = (int)(new_ray->f_x_inter);
		new_ray->h_y_inter = (int)(new_ray->f_y_inter);
		if (map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
			/ TILE_SIZE][(int)(new_ray->f_x_inter) / TILE_SIZE] == '1'
		|| map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
				/ TILE_SIZE][(int)(new_ray->f_x_inter) / TILE_SIZE] == 'D'
		|| map->arr[(int)(new_ray->f_y_inter - new_ray->is_up)
				/ TILE_SIZE][(int)(new_ray->f_x_inter) / TILE_SIZE] == 'O')
		{
			if (horz_hit(new_ray, map))
				break ;
		}
		new_ray->f_x_inter += new_ray->x_steps;
		new_ray->f_y_inter += new_ray->y_steps;
	}
}
