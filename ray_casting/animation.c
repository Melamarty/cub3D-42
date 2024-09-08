#include "../parsing/parsing.h"

void	create_textures(t_map *map)
{
	int	i;

	map->timing = 0;
    map->is_reload = 0;
	map->is_shot = 0;
	i = 0;
	while (i < 31)
	{
		map->sprite[i] = mlx_load_png(ft_strjoin(ft_strjoin("../parsing/textures/bonus/frame", ft_itoa(i + 1)), ".png"));
		i++;
	}
}

void	put_frame(t_map *map)
{
	// static int	i;
	// if (i)
	// {
		mlx_delete_image(map->mlx, map->sprite_img);
		map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[map->frame]);
		mlx_image_to_window(map->mlx, map->sprite_img, WIDTH - 666 - ((WIDTH - 666) / 2), HEIGHT - 375);
	// }
	// else
	// {
	// 	map->sprite_img = mlx_texture_to_image(map->mlx, map->sprite[map->frame]);
	// 	mlx_image_to_window(map->mlx, map->sprite_img,  WIDTH - 666 - ((WIDTH - 666) / 2), HEIGHT - 375);
	// 	if (!i)
	// 		i++;
	// }
}

void	shot(t_map *map)
{
	// if (map->timing == 5)
	// {
		put_frame(map);
		if (map->frame == 6)
		{
			map->frame = 0;
			// map->timing = 0;
			map->is_shot = 0;
		}
		else
			map->frame += 1;
		// map->timing = 0;
	// }
	// map->timing += 1;
}

void	reload(t_map *map)
{
    if (map->timing == 4)
    {
        put_frame(map);
        if (map->frame == 30)
        {
            map->frame = 0;
            map->timing = 0;
            map->is_reload = 0;
        }
        else
            map->frame += 1;
        map->timing = 0;
    }
    map->timing += 1;
}

void    animation(void *p)
{
    t_map *map = (t_map *)p;
    if (map->is_reload)
        reload(map);
	else if (map->is_shot)
		shot(map);
}
