#include "parsing.h"

void put_img(t_map *map, int top, int botm, int x, t_ray *ray)
{
    mlx_image_t *img = NULL;

    img = map->texture->curr;
    int width = img->width;
    int height = img->height;
    int img_x;
    int a;
    int b;

    //printf ("%d %d, ", width, height);
    if (ray->ray_dir == HIT_VIRT)
			img_x = ray->y_inter % width;
	else
		img_x = ray->x_inter % width;

    a = top;
    b = botm;
    if (top < 0)  top = 0;
    if (botm > HEIGHT) botm = HEIGHT;
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
    int i = 0;
	t_ray *ray;
	float distoplan = (WIDTH / 2) / tan((float)(map->player->fov / 2));
	while (map->rays)
	{
		ray = map->rays;
		float raydis = ray->ray_dis * cos(ray->ray_angle - map->player->rotAngle);
        if (raydis <= 0)
            raydis = 1;
        int corrected_raydis = (int)raydis;
		float wallStripHight = ((float)TILE_SIZE / corrected_raydis) * distoplan;
        int topPixel = (HEIGHT / 2) - (wallStripHight / 2);
        long bottomPixel = (HEIGHT / 2) + (wallStripHight / 2);

		int ofsx, ofsy;
		for (int y = 0; y < topPixel; y++)
			mlx_put_pixel(map->img, i, y, create_color(map->ceiling->r, map->ceiling->g, map->ceiling->b, 255));
        set_texture(map, ray);
		put_img(map, topPixel, bottomPixel, i, ray);
		for (int y = bottomPixel; y < HEIGHT; y++)
			mlx_put_pixel(map->img, i, y, create_color(map->floor->r, map->floor->g, map->floor->b, 255));
		i++;
		map->rays = map->rays->next;
	}
}
