#include "parsing.h"


void rect(t_map *map, int x, int y, int width, int height)
{
	for (int j = y; j < y + height && j < 660; j++)
	{
		for (int i = x; i < x + width ; i++ )
		{
			printf ("%d %d\n",i, j);
			mlx_put_pixel(map->img, i, j, create_color(0, 0, 255, 255));
		}
	}
}

void put_texture(t_map *map)
{
    unsigned int *texture;

    texture = (unsigned int *)my_malloc(64 * 64 * sizeof(unsigned int), 0);
    int mod = 8;
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (i % mod && j % mod)
                texture[i * 64 + j] = create_color(0, 0, 255, 255);  // Blue
            else
                texture[i * 64 + j] = create_color(0, 0, 0, 255);  // Black
        }
    }

    for (int i = 0; i < map->width * cube_width; i++)
    {
        for (int j = 0; j < map->height * cube_width; j++)
		{
			int x = i %64, y = j % 64;
            mlx_put_pixel(map->img, i, j, texture[x * 64 + y]);
		}
    }
}

unsigned *gen_texture()
{
	unsigned int *texture;

    texture = (unsigned int *)my_malloc(64 * 64 * sizeof(unsigned int), 0);
    int mod = 8;
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (i % mod && j % mod)
                texture[i * 64 + j] = create_color(0, 0, 255, 255);  // Blue
            else
                texture[i * 64 + j] = create_color(0, 0, 0, 255);  // Black
        }
    }
	return (texture);
}
void render(t_map *map)
{
	the_rays *ray;
	int wallWidth = 1;
	double walHight = 200;
	unsigned int *colors;
	//mlx_clear_window(map->mlx, map->we);
	//put_texture(map);
	//mlx_put_image_to_window(map->mlx, map->we, map->img, 0, 0);
	int i = 0;
	while (map->rays)
	{
		ray = map->rays;
		float raydis = ray->ray_dis * cos(ray->ray_angle - map->player->rotAngle);
		float distoplan = (map->width * cube_width / 2) / (tan(map->player->fov / 2));
		float wallStripHight = (60 / raydis )* distoplan;
		int topPixel = (map->height * cube_width / 2) - (wallStripHight / 2);
		if (topPixel < 0) topPixel = 0;
		int bottomPixel = (map->height * cube_width / 2) + (wallStripHight / 2);
		if (bottomPixel > map->height * cube_width) bottomPixel = map->height * cube_width;

		printf ("top %d\n", topPixel);
		for (int y = 0; y < topPixel; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));
		//rect(map, (int)(i * wallWidth), (int)y, (int)wallWidth, (int)wallStripHight);
		i++;
		map->rays = map->rays->next;
	}
}