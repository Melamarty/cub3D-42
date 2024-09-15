/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:54 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/15 18:29:56 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	up(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player->moveSpeed * cos(map->player->rotAngle);
	new_y = map->player->moveSpeed * sin(map->player->rotAngle);
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

	new_x = map->player->moveSpeed
		* cos(normangle(map->player->rotAngle + M_PI));
	new_y = map->player->moveSpeed
		* sin(normangle(map->player->rotAngle + M_PI));
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

	new_x = cos(normangle(map->player->rotAngle - M_PI_2))
		* map->player->moveSpeed;
	new_y = sin(normangle(map->player->rotAngle - M_PI_2))
		* map->player->moveSpeed;
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

	new_x = cos(normangle(map->player->rotAngle + M_PI_2))
		* map->player->moveSpeed;
	new_y = sin(normangle(map->player->rotAngle + M_PI_2))
		* map->player->moveSpeed;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}
