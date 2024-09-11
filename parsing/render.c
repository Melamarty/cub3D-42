#include "parsing.h"

void put_img(t_map *map, int top, int botm, int x, t_ray *ray, int a, int b)
{
    mlx_image_t *img = NULL;

    img = map->texture->curr;
    int width = img->width;
    int height = img->height;
    int img_x;

    //printf ("%d %d, ", width, height);
    if (ray->ray_dir == HIT_VIRT)
			img_x = ray->y_inter % width;
	else
		img_x = ray->x_inter % width;

    for (int y = top; y < botm; y++) {

        float ratio = (float)(y - a) / (float)(b - a);
        int img_y = (int)(ratio * height) % height;

        int of = (img_y * width + (img_x)) * 4;
        int r = img->pixels[of];
        int g = img->pixels[of + 1];
        int b = img->pixels[of + 2];
        int a = img->pixels[of + 3];
        mlx_put_pixel(map->img, x, y, create_color(r, g, b, a));
    }
}


void load_textures(t_map *map)
{
    mlx_texture_t *texture;
    if (!map->texture->no)
    {
        texture = mlx_load_png(map->no);
        map->texture->no = mlx_texture_to_image(map->mlx, texture);
    }
    if (!map->texture->so)
    {
        texture = mlx_load_png(map->so);
        map->texture->so = mlx_texture_to_image(map->mlx, texture);
    }
    if (!map->texture->we)
    {
        texture = mlx_load_png(map->we);
        map->texture->we = mlx_texture_to_image(map->mlx, texture);
    }
    if (!map->texture->ea)
    {
        texture = mlx_load_png(map->ea);
        map->texture->ea = mlx_texture_to_image(map->mlx, texture);
    }
    if (!map->texture->door)
    {
        texture = mlx_load_png("textures/door.png");
        map->texture->door = mlx_texture_to_image(map->mlx, texture);
    }
}

void set_texture(t_map *map, t_ray *ray)
{
    mlx_texture_t *texture = NULL;
    char *txt;

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

void render(t_map *map)
{

	t_ray *ray;
	int i = 0;
    int a, b;
	float distoplan = (WIDTH / 2) / tan((float)(map->player->fov / 2));
	while (map->rays)
	{
		ray = map->rays;
		float epsilon = 1e-6;
		float raydis = ray->ray_dis * cos(ray->ray_angle - map->player->rotAngle);
        if (raydis <= 0)
            raydis = 1;
        int corrected_raydis = (int)raydis;
		float wallStripHight = ((float)TILE_SIZE / corrected_raydis) * distoplan;
        int topPixel = (HEIGHT / 2) - (wallStripHight / 2);
        a = topPixel;
        if (topPixel < 0) topPixel = 0;
        long bottomPixel = (HEIGHT / 2) + (wallStripHight / 2);
        b = bottomPixel;
        if (bottomPixel > HEIGHT) bottomPixel = HEIGHT;

		int ofsx, ofsy;
		for (int y = 0; y < topPixel; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 255, 255));
        set_texture(map, ray);
        //if (ray->is_door)
        //{
        //    for (int y = topPixel; y < bottomPixel; y++)
        //        mlx_put_pixel(map->img, i, y, create_color(0, 0, 0, 255));
        //}
        //else
		    put_img(map, topPixel, bottomPixel, i, ray, a, b);
		for (int y = bottomPixel; y < HEIGHT; y++)
			mlx_put_pixel(map->img, i, y, create_color(0, 0, 0, 40));
		i++;
		map->rays = map->rays->next;
	}
}