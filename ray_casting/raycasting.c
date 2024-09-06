#include "../parsing/parsing.h"

double	calc_dis(t_map map, t_ray ray)
{
	int	dx;
	int	dy;
	double dis;

	dx = abs(ray.x_inter - map.player->pos.x);
	dy = abs(ray.y_inter - map.player->pos.y);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

void cast_rays(t_map *map)
{
	double	ray_angle;
	map->rays = NULL;
	t_ray	*new_ray;
	new_ray = malloc(sizeof(t_ray));
	new_ray->next = NULL;
	double x, y;
	ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
	for (int i = 0; i < WIDTH; i++)
	{
		new_ray->ray_angle = ray_angle;
		x = map->player->pos.x;
		y = map->player->pos.y;
		new_ray->x2 = ((map->player->pos.x) + 10000 * cos(ray_angle));
		new_ray->y2 = ((map->player->pos.y) + 10000 * sin(ray_angle));
		new_ray->dx = new_ray->x2 - (map->player->pos.x);
		new_ray->dy = new_ray->y2 - (map->player->pos.y);
		if (abs(new_ray->dx) > abs(new_ray->dy))
			new_ray->steps = abs(new_ray->dx);
		else
			new_ray->steps = abs(new_ray->dy);
		new_ray->xinc = new_ray->dx / (double)new_ray->steps;
		new_ray->yinc = new_ray->dy / (double)new_ray->steps;
		for (int i = 0; i < new_ray->steps; i++)
		{
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
		new_ray = malloc(sizeof(t_ray));
		new_ray->next = NULL;
		ray_angle = normAngle(map->player->fov / (WIDTH) + ray_angle);
	}
}

int	is_wall(int new_x, int new_y, t_map map)
{
	double	ang;
	// int	temp1;
	// int	temp2;
	int	px;
	int	py;
	ang = map.player->rotAngle;
	for (int i = 0; i < 360; i++)
	{
		// temp1 = 10 * cos(ang) + 150;
		// temp2 = 10 * sin(ang) + 90;
		px = (new_x) + 15 * cos(ang);
		py = (new_y) + 15 * sin(ang);
		// mlx_put_pixel(map.img, temp1, temp2, create_color(0, 0, 0, 255));
		ang += 180 / M_PI;
		if (px < 0 || px / cube_width >= map.width || py < 0 || py / cube_width >= map.height ||  map.arr[py / cube_width][px / cube_width] == '1')
			return (1);
	}
	return (0);
}

// int	is_wall(int new_x, int new_y, t_map map)
// {
// 	if (new_x < 0 || new_x / cube_width > map.width || new_y < 0 || new_y / cube_width > map.height ||  map.arr[new_y / cube_width][new_x / cube_width] == '1')
// 		return (1);
// 	return (0);
// }

int	key_pressed(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D) || mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(map->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_Q) || mlx_is_key_down(map->mlx, MLX_KEY_B))
			return (1);
	return (0);
}

void handle_key(void *p)
{
	int		move_step;
	t_map 	*map;
	double	new_x;
	double	new_y;
	map = (t_map *)p;
	if (!key_pressed(map))
		return ;
	if (mlx_is_key_down(map->mlx, MLX_KEY_Q))
		map->is_rot = 2;
	if (mlx_is_key_down(map->mlx, MLX_KEY_B))
		map->is_rot = 0;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player->rotAngle = normAngle(map->player->rotSpeed + map->player->rotAngle);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player->rotAngle = normAngle(map->player->rotAngle - map->player->rotSpeed);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_UP))
		up(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		down(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		left(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		right(map);
	cast_rays(map);
	render(map);
	mini_map(map);
}

void init_player(t_map *map)
{
	map->player->pos.x = map->player->pos.x * cube_width + 30;
	map->player->pos.y = map->player->pos.y * cube_width + 30;
	map->player->xDir = 0;
	map->player->yDir = 0;
	map->player->moveSpeed = 100;
	map->player->rotAngle = M_PI / 2;
	map->player->rotSpeed = 5 * (M_PI / 180);
	map->player->fov = 60 * M_PI / 180;
}