/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:49:02 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 15:11:27 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_ceill(t_map *map, int topPixel, int i)
{
	int	y;

	y = -1;
	while (++y < topPixel)
		mlx_put_pixel(map->img, i, y, create_color(map->ceiling->r,
				map->ceiling->g, map->ceiling->b, 255));
}

void	draw_floor(t_map *map, int bottomPixel, int i)
{
	int	y;

	y = bottomPixel - 1;
	while (++y < HEIGHT)
		mlx_put_pixel(map->img, i, y, create_color(map->ceiling->r,
				map->floor->g, map->floor->b, 255));
}

t_wall	*get_wall_info(int top, int bottom, int x)
{
	static t_wall	*wall;

	if (!wall)
	{
		wall = my_malloc(sizeof(t_wall), 0);
		if (!wall)
		{
			ft_putstr("memory error\n", 2);
			exit (1);
		}
	}
	wall->botm = bottom;
	wall->top = top;
	wall->x = x;
	return (wall);
}
