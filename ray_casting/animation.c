#include "../parsing/parsing.h"

void	create_textures(t_map *map)
{
	int	i;

	map->timing = 0;
	map->frame = 0;
	i = 0;
	while (i < 5)
	{
		map->sprite[i] = mlx_load_png(ft_strjoin(ft_strjoin("../parsing/textures/bonus/frame", ft_itoa(i + 1)), ".png"));
		i++;
	}
}

void	put_frame(t_map *map)
{
	static int	i;

	if (i)
	{
		mlx_delete_image(map->mlx, map->sprite_img);
		map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[map->frame]);
		mlx_image_to_window(map->mlx, map->sprite_img, 0, HEIGHT - 223);
	}
	else
	{
		map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[map->frame]);
		mlx_image_to_window(map->mlx, map->sprite_img, 0, HEIGHT - 223);
		if (!i)
			i++;
	}
}

void	animation(void	*p)
{
	t_map *map;

	map = (t_map *)p;
	if (map->timing == 8)
	{
		put_frame(map);
		if (map->frame == 4)
			map->frame = 0;
		else
			map->frame += 1;
		map->timing = 0;
	}
	map->timing += 1;
}
