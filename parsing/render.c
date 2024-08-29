#include "parsing.h"

//void put_texture(t_map *map)
//{
//	int mod = 8;
//    for (int i = 0; i < map->width * cube_width; i++)
//    {
//        for(int j = 0; j < map->height * cube_width; j++)
//        {
//            if (i % mod && j % mod)
//				mlx_put_pixel(map->img, i, j, create_color(0, 0, 255, 255));
//            else
//                mlx_put_pixel(map->img, i, j, create_color(0, 0, 0, 255));
//        }
//    }
//}

void rect(t_map *map, int x, int y, int width, int height)
{
	for (int j = y; j < y + height; j++)
	{
		for (int i = x; i < x + width; i++ )
		{
			mlx_put_pixel(map->img, i, j, create_color(0, 0, 255, 255));
		}
	}
}


void render(t_map *map)
{
	the_rays *ray;
	int wallWidth = 1;
	double walHight = 500;
	//mlx_clear_window(map->mlx, map->we);
	//put_texture(map);
	//mlx_put_image_to_window(map->mlx, map->we, map->img, 0, 0);
	int raydis;
	int i = 0;
	while (map->rays)
	{
		ray = map->rays;
		raydis = ray->ray_dis;
		int distoplan = (map->width * cube_width / 2) / (tan(map->player->fov / 2));
		int wallH = 60 * distoplan / raydis;
		int y = (map->height * cube_width / 2) - (cube_width / 2);
		rect(map, i * wallWidth, y, wallWidth, wallH);
		i++;
		map->rays = map->rays->next;
	}
}