/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:54 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 17:18:28 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	up(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player->movespeed * cos(map->player->rotangle);
	new_y = map->player->movespeed * sin(map->player->rotangle);
	if (!is_wall((map->player->pos.x + round(new_x)),
			(map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	down(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player->movespeed
		* cos(normangle(map->player->rotangle + M_PI));
	new_y = map->player->movespeed
		* sin(normangle(map->player->rotangle + M_PI));
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	left(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = cos(normangle(map->player->rotangle - M_PI_2))
		* map->player->movespeed;
	new_y = sin(normangle(map->player->rotangle - M_PI_2))
		* map->player->movespeed;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	right(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = cos(normangle(map->player->rotangle + M_PI_2))
		* map->player->movespeed;
	new_y = sin(normangle(map->player->rotangle + M_PI_2))
		* map->player->movespeed;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}
