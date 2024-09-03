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

//void put_texture(t_map *map)
//{
//    unsigned int *texture;

//    texture = (unsigned int *)my_malloc(64 * 64 * sizeof(unsigned int), 0);
//    int mod = 8;
//    for (int i = 0; i < 64; i++)
//    {
//        for (int j = 0; j < 64; j++)
//        {
//            if (i % mod && j % mod)
//                texture[i * 64 + j] = create_color(0, 0, 255, 255);  // Blue
//            else
//                texture[i * 64 + j] = create_color(0, 0, 0, 255);  // Black
//        }
//    }

//    for (int i = 0; i < map->width * cube_width; i++)
//    {
//        for (int j = 0; j < HEIGHT; j++)
//		{
//			int x = i %64, y = j % 64;
//            mlx_put_pixel(map->img, i, j, texture[x * 64 + y]);
//		}
//    }
//}



//unsigned *gen_texture()
//{
//	unsigned int *texture;

//    texture = (unsigned int *)my_malloc(64 * 64 * sizeof(unsigned int), 0);
//    int mod = 8;
//    for (int i = 0; i < 64; i++)
//    {
//        for (int j = 0; j < 64; j++)
//        {
//            if (i % mod && j % mod)
//                texture[i * 64 + j] = create_color(255, 0, 0, 90);  // Blue
//            else
//                texture[i * 64 + j] = create_color(0, 0, 0, 255);  // Black
//        }
//    }
//	return (texture);
//}

void put_img(t_map *map, int top, int botm, int x, int img_x)
{
    //mlx_texture_t *txt = NULL;
    mlx_image_t *img = NULL;

    //if (!txt) {
    //    //printf("%s\n", map->texture);
    //    txt = mlx_load_png(map->texture);
    //    img = mlx_texture_to_image(map->mlx, txt);
    //}

    img = map->texture->curr;
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
    //mlx_delete_image(map->mlx, img);
    //mlx_delete_texture(txt);
}

void set_texture(t_map *map, t_ray *ray)
{
    mlx_texture_t *texture = NULL;
    char *txt;

    if (ray->ray_dir == 2)
        txt = map->no ;
    else
       txt = map->so;
    if (!map->texture->no || !map->texture->so)
    {
        if (ray->ray_dir == 2)
        {
            texture = mlx_load_png(map->no);
            map->texture->no = mlx_texture_to_image(map->mlx, texture);
        }
        else
        {
            texture = mlx_load_png(map->so);
            map->texture->so = mlx_texture_to_image(map->mlx, texture);
        }
    }
    if (ray->ray_dir == 2)
        map->texture->curr = map->texture->no;
    else
        map->texture->curr = map->texture->so;
}

void render(t_map *map)
{
	t_ray *ray;
	int i = 0;
	float distoplan = (WIDTH / 2) / tan((float)(map->player->fov / 2));
	while (map->rays)
	{
		ray = map->rays;
		float epsilon = 1e-6;
		float raydis = ray->ray_dis * cos(ray->ray_angle - map->player->rotAngle);
        if (raydis <= 0)
            raydis = 1;
        //printf ("%f,   %.2f\n", ray->ray_dis, ray->ray_angle - map->player->rotAngle);
        //printf ("%.2f,  ", ray->ray_angle - map->player->rotAngle);
        int corrected_raydis = (int)raydis;
		float wallStripHight = ((float)TILE_SIZE / corrected_raydis) * distoplan;
        int topPixel = (HEIGHT / 2) - (wallStripHight / 2);
        if (topPixel < 0) topPixel = 0;
        long bottomPixel = (HEIGHT / 2) + (wallStripHight / 2);
        if (bottomPixel > HEIGHT) bottomPixel = HEIGHT;

		int ofsx, ofsy;
        //printf ("%d, %ld\n", topPixel, bottomPixel);
		if (ray->ray_dir == 2)
			ofsx = ray->y_inter % 60;
		else
			ofsx = ray->x_inter % 60;
		for (int y = 0; y < topPixel; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));
        set_texture(map, ray);
        //printf ("%s\n", map->texture);
		put_img(map, topPixel, bottomPixel, i, ofsx);
		for (int y = bottomPixel; y < HEIGHT; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 0, 40));
		i++;
		map->rays = map->rays->next;
	}
}


//void reneder(t_map *map)
//{
//    t_ray *current_ray = map->rays;
//    int wallWidth = 1;
//    float distoplan = (WIDTH / 2) / tan((float)(map->player->fov / 2));

//    int i = 0;
//    while (current_ray)
//    {
//        t_ray *ray = current_ray;
//        int raydis = ray->ray_dis;
//        float wallStripHight = ((float)TILE_SIZE / raydis) * distoplan;

//        int topPixel = (HEIGHT / 2) - (wallStripHight / 2);
//        if (topPixel < 0) topPixel = 0;

//        int bottomPixel = (HEIGHT / 2) + (wallStripHight / 2);
//        if (bottomPixel > HEIGHT) bottomPixel = HEIGHT;

//        for (int y = 0; y < topPixel; y++)
//            mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));

//        for (int y = topPixel; y < bottomPixel; y++)
//            mlx_put_pixel(map->img, i, y, create_color(255, 0, 0, 255));

//        for (int y = bottomPixel; y < HEIGHT; y++)
//            mlx_put_pixel(map->img, i, y, create_color(0, 255, 0, 255));

//        i++;
//        current_ray = current_ray->next;
//    }
//    //mlx_delete_image(map->mlx, map->img);
//}
