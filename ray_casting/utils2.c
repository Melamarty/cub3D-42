/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:22:03 by houamrha          #+#    #+#             */
/*   Updated: 2024/09/16 14:33:50 by houamrha         ###   ########.fr       */
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

void	clean_all(t_map *map)
{
	destroy_textures(map);
	my_malloc(0, 1);
	exit(1);
}

void	re_render(t_map *map)
{
	cast_rays(map);
	render(map);
	mini_map(map);
}
