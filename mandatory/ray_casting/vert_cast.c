/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:30:22 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 20:47:41 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_vert(t_ray *new_ray, t_map *map)
{
	new_ray->f_x_inter = (map->player->pos.x / TILE_SIZE) * TILE_SIZE;
	if (new_ray->is_right)
		new_ray->f_x_inter += TILE_SIZE;
	new_ray->f_y_inter = map->player->pos.y
		+ (new_ray->f_x_inter - map->player->pos.x) * tan(new_ray->ray_angle);
	new_ray->x_steps = TILE_SIZE;
	if (!new_ray->is_right)
		new_ray->x_steps *= -1;
	new_ray->y_steps = TILE_SIZE * tan(new_ray->ray_angle);
	if (new_ray->is_up && new_ray->y_steps > 0)
		new_ray->y_steps *= -1;
	if (!new_ray->is_up && new_ray->y_steps < 0)
		new_ray->y_steps *= -1;
}

int	vert_hit(t_ray *new_ray, t_map *map)
{
	if (map->arr[(int)(new_ray->f_y_inter)
		/ TILE_SIZE][(int)(new_ray->f_x_inter
			+ new_ray->is_right - 1)
		/ TILE_SIZE] == '1')
	{
		new_ray->found_y_inter = 2;
		return (1);
	}
	return (0);
}

void	check_vert(t_ray *new_ray, t_map *map)
{
	calc_vert(new_ray, map);
	while (1 && new_ray->f_y_inter < map->height * TILE_SIZE
		&& new_ray->f_x_inter < map->width * TILE_SIZE
		&& new_ray->f_y_inter >= 0
		&& new_ray->f_x_inter >= 0)
	{
		new_ray->v_x_inter = (int)(new_ray->f_x_inter);
		new_ray->v_y_inter = (int)(new_ray->f_y_inter);
		if (map->arr[(int)(new_ray->f_y_inter)
			/ TILE_SIZE][(int)(new_ray->f_x_inter
				+ new_ray->is_right - 1)
			/ TILE_SIZE] == '1')
		{
			if (vert_hit(new_ray, map))
				break ;
		}
		new_ray->f_x_inter += new_ray->x_steps;
		new_ray->f_y_inter += new_ray->y_steps;
	}
}
