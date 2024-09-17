/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:29:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/17 17:21:16 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	open_door(t_map *map)
{
	if (map->can_open)
	{
		map->arr[map->door_ray->y_door][map->door_ray->x_door] = 'O';
		map->can_open = 0;
	}
}

void	close_door(t_map *map)
{
	if (map->can_close)
	{
		map->arr[map->door_ray->y_door][map->door_ray->x_door] = 'D';
		map->can_close = 0;
	}
}
