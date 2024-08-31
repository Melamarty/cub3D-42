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
                texture[i * 64 + j] = create_color(255, 0, 0, 90);  // Blue
            else
                texture[i * 64 + j] = create_color(0, 0, 0, 255);  // Black
        }
    }
	return (texture);
}

void put_img(t_map *map, int top, int botm, int x, int img_x)
{
    static mlx_texture_t *txt = NULL;
    static mlx_image_t *img = NULL;

    if (!txt) {
        txt = mlx_load_png("./text.png");
        img = mlx_texture_to_image(map->mlx, txt);
    }

    int width = img->width;
    int height = img->height;

	int ofsy;
    for (int y = top; y < botm; y++) {
        float ratio = (float)(y - top) / (float)(botm - top);
        int img_y = (int)(ratio * height);

        int of = (img_y * width + (img_x % width)) * 4;
        int r = img->pixels[of];
        int g = img->pixels[of + 1];
        int b = img->pixels[of + 2];
        int a = img->pixels[of + 3];

        mlx_put_pixel(map->img, x, y, create_color(r, g, b, a));
    }
}


void render(t_map *map)
{
	the_rays *ray;
	double walHight = 200;
	unsigned int *texture = gen_texture();
	int i = 0;
	float distoplan = (map->width * cube_width / 2) / tan((float)(map->player->fov / 2));
	while (map->rays)
	{
		ray = map->rays;
		float epsilon = 1e-6;
		float raydis = ray->ray_dis * cos(ray->ray_angle - map->player->rotAngle);
        printf ("%.2f,  ", ray->ray_angle - map->player->rotAngle);
        int corrected_raydis = ray->ray_dis;
        //if (raydis < 0.2)
        //    corrected_raydis = ray->ray_dis;
        //else
        //    corrected_raydis = (int)raydis;

		float wallStripHight = ((float)cube_width / corrected_raydis) * distoplan;

        int topPixel = (map->height * cube_width / 2) - (wallStripHight / 2);
        if (topPixel < 0) topPixel = 0;
        int bottomPixel = (map->height * cube_width / 2) + (wallStripHight / 2);
        if (bottomPixel > map->height * cube_width) bottomPixel = map->height * cube_width;

		int ofsx, ofsy;
		if (ray->ray_dir == 2)
			ofsx = ray->y_inter % cube_width;
		else
			ofsx = ray->x_inter % cube_width;
		for (int y = 0; y < topPixel; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));
		put_img(map, topPixel, bottomPixel, i, ofsx);
		for (int y = bottomPixel; y < map->height * cube_width; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 0, 40));
		i++;
		map->rays = map->rays->next;
		//exit (0);
	}
}


//void rendeer(t_map *map)
//{
//    the_rays *current_ray = map->rays;
//    int wallWidth = 1;
//    float distoplan = (map->width * cube_width / 2) / tan((float)(map->player->fov / 2));

//    int i = 0;
//    while (current_ray)
//    {
//        the_rays *ray = current_ray;
//        int raydis = ray->ray_dis;
//        float wallStripHight = ((float)cube_width / raydis) * distoplan;

//        int topPixel = (map->height * cube_width / 2) - (wallStripHight / 2);
//        if (topPixel < 0) topPixel = 0;

//        int bottomPixel = (map->height * cube_width / 2) + (wallStripHight / 2);
//        if (bottomPixel > map->height * cube_width) bottomPixel = map->height * cube_width;

//        for (int y = 0; y < topPixel; y++)
//            mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));

//        for (int y = topPixel; y < bottomPixel; y++)
//            mlx_put_pixel(map->img, i, y, create_color(255, 0, 0, 255));

//        for (int y = bottomPixel; y < map->height * cube_width; y++)
//            mlx_put_pixel(map->img, i, y, create_color(0, 255, 0, 255));

//        i++;
//        current_ray = current_ray->next;
//    }
//}
