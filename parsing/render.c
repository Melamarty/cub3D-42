/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:48:20 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/16 15:42:38 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/// @brief
//(int)(ratio * img->height) % img->height is the img_y

void	put_img(t_map *map, t_wall *wall, t_ray *ray)
{
	mlx_image_t	*img;
	int			img_x;
	int			of;
	int			y;
	float		ratio;

	img = map->texture->curr;
	if (ray->ray_dir == HIT_VIRT)
		img_x = ray->y_inter % img->width;
	else
		img_x = ray->x_inter % img->width;
	y = wall->top -1;
	if (wall->top < 0)
		y = -1;
	while (++y < wall->botm && y < HEIGHT)
	{
		ratio = (float)(y - wall->top) / (float)(wall->botm - wall->top);
		of = (((int)(ratio * img->height) % img->height)
				* img->width + (img_x)) * 4;
		mlx_put_pixel(map->img, wall->x, y, create_color(img->pixels[of],
				img->pixels[of + 1], img->pixels[of + 2], img->pixels[of + 3]));
	}
}

mlx_texture_t	*load_txt(char	*path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		ft_putstr("texture error\n", 2);
		exit (1);
	}
	return (texture);
}

void	load_textures(t_map *map)
{
	if (!map->texture->no)
		map->texture->no = mlx_texture_to_image(map->mlx, load_txt(map->no));
	if (!map->texture->so)
		map->texture->so = mlx_texture_to_image(map->mlx, load_txt(map->so));
	if (!map->texture->we)
		map->texture->we = mlx_texture_to_image(map->mlx, load_txt(map->we));
	if (!map->texture->ea)
		map->texture->ea = mlx_texture_to_image(map->mlx, load_txt(map->ea));
	if (!map->texture->door)
		map->texture->door = mlx_texture_to_image(map->mlx,
				load_txt("./textures/door.png"));
}

void	set_texture(t_map *map, t_ray *ray)
{
	mlx_texture_t	*texture;
	char			*txt;

	if (ray->ray_dir == 2)
		txt = map->no ;
	else
		txt = map->so;
	load_textures(map);
	if (ray->is_door)
		map->texture->curr = map->texture->door;
	else if (ray->ray_dir == HIT_VIRT)
	{
		if (ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI)
			map->texture->curr = map->texture->ea;
		else
			map->texture->curr = map->texture->we;
	}
	else
	{
		if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
			map->texture->curr = map->texture->so;
		else
			map->texture->curr = map->texture->no;
	}
}

void	render(t_map *map)
{
	int		i;
	long	bottom;
	long	top;
	float	distoplan;
	float	raydis;

	distoplan = (WIDTH / 2) / tan((float)(map->player->fov / 2));
	i = 0;
	while (i < 1200)
	{
		raydis = (int)(map->rays[i].ray_dis
				* cos(map->rays[i].ray_angle - map->player->rotAngle));
		top = (HEIGHT / 2) - (((float)TILE_SIZE / raydis) * distoplan / 2);
		bottom = (HEIGHT / 2) + (((float)TILE_SIZE / raydis) * distoplan / 2);
		draw_ceill(map, top, i);
		set_texture(map, &map->rays[i]);
		put_img(map, get_wall_info(top, bottom, i), &map->rays[i]);
		draw_floor(map, bottom, i);
		// map->rays[i] = map->rays->next;
		i++;
	}
}

// ((float)TILE_SIZE / raydis) * distoplan is wallheight