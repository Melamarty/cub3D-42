/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:12:57 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 19:20:10 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 31 && map->sprite[i])
	{
		mlx_delete_texture(map->sprite[i]);
		i++;
	}
	i = 0;
	while (i < 10 && map->bullet[i])
	{
		mlx_delete_texture(map->bullet[i]);
		i++;
	}
}

void	destroy_hamza(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		if (map->txts[i])
			mlx_delete_texture(map->txts[i]);
	}
}

void	clear_all(t_map *map)
{
	destroy_textures(map);
	destroy_hamza(map);
	my_malloc(0, 1);
	exit(0);
}

void	rerender(t_map *map)
{
	cast_rays(map);
	render(map);
	mini_map(map);
}
