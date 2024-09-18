/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:12:57 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/18 15:41:11 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (map->txts[i])
			mlx_delete_texture(map->txts[i]);
		i++;
	}
}

void	clear_all(t_map *map)
{
	destroy_textures(map);
	my_malloc(0, 1);
	exit(1);
}

void	rerender(t_map *map)
{
	cast_rays(map);
	render(map);
}
