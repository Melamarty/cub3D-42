#include "../parsing/parsing.h"

the_rays *last_ray(the_rays *rays)
{
	while (rays->next)
		rays = rays->next;
	return (rays);
}

void	add_back_ray(the_rays **rays, the_rays *new_ray)
{
	if (!*rays)
		*rays = new_ray;
	else
		last_ray(*rays)->next = new_ray;
}

unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

double normAngle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
	{
        angle += (2 * M_PI);
    }
    return (angle);
}

double	calc_dis(t_map map, the_rays ray)
{
	int	dx;
	int	dy;
	double dis;

	dx = abs(ray.x_inter - map.player->pos.x * cube_width + 10);
	dy = abs(ray.y_inter - map.player->pos.y * cube_width + 10);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

void cast_rays(t_map *map)
{
	double	ray_angle;
	map->rays = NULL;
	the_rays	*new_ray;
	new_ray = malloc(sizeof(the_rays));
	new_ray->next = NULL;
	double x, y;
	ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
	for (int i = 0; i < 1; i++)
	{
		x = map->player->pos.x * cube_width + 10;
		y = map->player->pos.y * cube_width + 10;
		new_ray->x2 = ((map->player->pos.x * cube_width + 10) + 10000 * cos(ray_angle));
		new_ray->y2 = ((map->player->pos.y * cube_width + 10) + 10000 * sin(ray_angle));
		new_ray->dx = new_ray->x2 - (map->player->pos.x * cube_width + 10);
		new_ray->dy = new_ray->y2 - (map->player->pos.y * cube_width + 10);
		if (abs(new_ray->dx) > abs(new_ray->dy))
			new_ray->steps = abs(new_ray->dx);
		else
			new_ray->steps = abs(new_ray->dy);
		new_ray->xinc = new_ray->dx / (double)new_ray->steps;
		new_ray->yinc = new_ray->dy / (double)new_ray->steps;
		for (int i = 0; i < new_ray->steps; i++)
		{
			// mlx_put_pixel(map->img, round(x), round(y), create_color(255, 255, 0, 255));
			new_ray->x_inter = round(x);
			new_ray->y_inter = round(y);
			x += new_ray->xinc;
			if (map->arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
			{
				new_ray->ray_dir = 2;
				break ;
			}
			y += new_ray->yinc;
			if (map->arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
			{
				new_ray->ray_dir = 1;
				break ;
			}
		}
		new_ray->ray_dis = calc_dis(*map, *new_ray);
		add_back_ray(&map->rays, new_ray);
		// printf("x: %d y: %d inter: %d dis: %f\n", map->ray_x, map->ray_y, map->ray_dir, map->ray_dis);
		new_ray = malloc(sizeof(the_rays));
		new_ray->next = NULL;
		ray_angle = normAngle(map->player->fov / (map->width * cube_width) + ray_angle);

	}
}

int	is_wall(int new_x, int new_y, t_map map)
{
	if (new_x < 0 || new_x > map.width || new_y < 0 || new_y > map.height ||  map.arr[new_y][new_x] == '1')
		return (1);
	return (0);
}

void handle_key(mlx_key_data_t keydata, void *p)
{
	int	move_step;
	t_map 	*map;
	int	new_x;
	int	new_y;
	map = (t_map *)p;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
			map->player->xDir = 1;
		else if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
			map->player->xDir = -1;
		else if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
			map->player->yDir = 1;
		else if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
			map->player->yDir = -1;
		map->player->rotAngle = normAngle(map->player->xDir * map->player->rotSpeed + map->player->rotAngle);
		move_step = map->player->moveSpeed * map->player->yDir;
		new_x = map->player->pos.x +  move_step * cos(map->player->rotAngle);
		new_y = map->player->pos.y +  move_step * sin(map->player->rotAngle);
		if (!is_wall(new_x, new_y, *map))
		{
			map->player->pos.x = new_x;
			map->player->pos.y = new_y;
		}
		raycasting(map);
	}
	else if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_RIGHT)
			map->player->xDir = 0;
		else if (keydata.key == MLX_KEY_LEFT)
			map->player->xDir = 0;
		else if (keydata.key == MLX_KEY_UP)
			map->player->yDir = 0;
		else if (keydata.key == MLX_KEY_DOWN)
			map->player->yDir = 0;
	}
}

void render_cube(int x, int y, t_map *map)
{
	unsigned int color;
	if (map->arr[y / cube_width][x / cube_width] == '1')
		color = create_color(0, 0, 255, 255);
	else
		color = create_color(108, 180, 238, 255);
	for (int i = 0; i < cube_width; i++)
	{
		for (int j = 0; j < cube_width; j++)
		{
			// mlx_put_pixel(map->img, x + j, y + i, color);
		}
	}
}

void init_player(t_map *map)
{
	map->player->xDir = 0;
	map->player->yDir = 0;
	map->player->moveSpeed = 1;
	map->player->rotAngle = M_PI / 2;
	map->player->rotSpeed = 10 * (M_PI / 180);
	map->player->fov = 60 * M_PI / 180;
}

void render_map(t_map *map)
{
	for(int i = 0; i < map->width; i++)
	{
		for (int j = 0; j < map->height; j++)
		{
			render_cube(i * cube_width, j * cube_width, map);
		}
	}
}

void render_player(t_map *map)
{
	// for (int i = 0; i < 20; i++)
	// {
	// 	for (int j = 0; j < 20; j++)
	// 	{
	// 		mlx_put_pixel(map->img, map->player->pos.x * cube_width + j, map->player->pos.y * cube_width + i, create_color(255, 0, 0, 255));
	// 	}
	// }
	cast_rays(map);
}

void	raycasting(t_map *map)
{
	// render_map(map);
	render_player(map);
}
