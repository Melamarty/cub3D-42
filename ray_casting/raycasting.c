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
	int z = 0;
	map->can_open = 0;
	map->can_close = 0;
	double	ray_angle;
	map->rays = NULL;
	t_ray	*new_ray;
	new_ray = malloc(sizeof(t_ray));
	new_ray->next = NULL;
	new_ray->is_door = 0;
	new_ray->is_close_door = 0;
	double x, y;
	map->door_ray = NULL;
	ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
	while (z < WIDTH)
	{
		if (z == WIDTH / 2)
			map->door_ray = new_ray;
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
			if ((map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == '1') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'O'))
			{
				if (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D' || map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'O')
				{
					if (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D')
						new_ray->is_door = 1;
					else
						new_ray->is_close_door = 1;
					if (z == WIDTH / 2)
					{
						map->door_ray->x_door = (int)round(x) / TILE_SIZE;
						map->door_ray->y_door = (int)round(y) / TILE_SIZE;
					}
				}
				new_ray->ray_dir = 2;
				if ((map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == '1') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D'))
					break ;
			}
			y += new_ray->yinc;
			if ((map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == '1') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'O'))
			{
				if (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D' || map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'O')
				{
					if (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D')
						new_ray->is_door = 1;
					else
						new_ray->is_close_door = 1;
					if (z == WIDTH / 2)
					{
						map->door_ray->x_door = (int)round(x) / TILE_SIZE;
						map->door_ray->y_door = (int)round(y) / TILE_SIZE;
					}
				}
				new_ray->ray_dir = 1;
				if ((map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == '1') || (map->arr[(int)round(y) / TILE_SIZE][(int)round(x) / TILE_SIZE] == 'D'))
					break ;
			}
		}
		new_ray->ray_dis = calc_dis(*map, *new_ray);
		if (z == WIDTH / 2 && (map->door_ray->is_door || map->door_ray->is_close_door))
		{
			if (map->door_ray->is_door && map->door_ray->ray_dis < 100)
				map->can_open = 1;
			else if (map->door_ray->is_close_door && map->door_ray->ray_dis < 100 && map->door_ray->ray_dis > 50)
				map->can_close = 1;
		}
		add_back_ray(&map->rays, new_ray);
		// printf("x: %d y: %d inter: %d dis: %f\n", map->ray_x, map->ray_y, map->ray_dir, map->ray_dis);
		new_ray = malloc(sizeof(t_ray));
		new_ray->is_door = 0;
		new_ray->is_close_door = 0;
		new_ray->next = NULL;
		ray_angle = normAngle(map->player->fov / (WIDTH) + ray_angle);
		z++;
	}
	// printf("%c\n", map->arr[map->door_ray->y_inter / TILE_SIZE][map->door_ray->x_inter / m_cube]);
}

int	is_wall(int new_x, int new_y, t_map map)
{
	double	ang;
	// int	temp1;
	// int	temp2;
	int	px;
	int	py;
	ang = map.player->rotAngle;
	// for (int i = 0; i < 360; i++)
	// {
		// temp1 = 10 * cos(ang) + 150;
		// temp2 = 10 * sin(ang) + 90;
		// px = (new_x) + 15 * cos(ang);
		// py = (new_y) + 15 * sin(ang);
		// mlx_put_pixel(map.img, temp1, temp2, create_color(0, 0, 0, 255));
		// ang += 180 / M_PI;
		if (new_x < 0 || new_x / m_cube >= map.width || new_y < 0 || new_y / m_cube >= map.height ||  map.arr[new_y / m_cube][new_x / m_cube] == '1' || map.arr[new_y / m_cube][new_x / m_cube] == 'D')
			return (1);
	// }
	return (0);
}

// int	is_wall(int new_x, int new_y, t_map map)
// {
// 	if (new_x < 0 || new_x / TILE_SIZE > map.width || new_y < 0 || new_y / TILE_SIZE > map.height ||  map.arr[new_y / TILE_SIZE][new_x / TILE_SIZE] == '1')
// 		return (1);
// 	return (0);
// }

int	key_pressed(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D) || mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(map->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_Q) || mlx_is_key_down(map->mlx, MLX_KEY_B)
		|| mlx_is_key_down(map->mlx, MLX_KEY_K) || mlx_is_key_down(map->mlx, MLX_KEY_R) || mlx_is_key_down(map->mlx, MLX_KEY_O) || mlx_is_key_down(map->mlx, MLX_KEY_C))
			return (1);
	return (0);
}

void	open_door(t_map *map)
{
	if (map->can_open)
	{
		map->arr[map->door_ray->y_door][map->door_ray->x_door] = 'O';
		map->can_open = 0;
	}
}

void	close_door(t_map *map)
{
	if (map->can_close)
	{
		map->arr[map->door_ray->y_door][map->door_ray->x_door] = 'D';
		map->can_close = 0;
	}
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
	{
		map->is_rot = 2;
		return ;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_B))
	{
		map->is_rot = 0;
		return ;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_O))
		open_door(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_C))
		close_door(map);
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
	if (mlx_is_key_down(map->mlx, MLX_KEY_K) && !map->is_shot)
	{
		map->is_shot = 1;
		map->frame = 0;
		return ;
	}
	else if (mlx_is_key_down(map->mlx, MLX_KEY_R) && !map->is_reload)
	{
		map->is_reload = 1;
        map->frame = 7;
		return ;
	}
	cast_rays(map);
	render(map);
	mini_map(map);
}

// void handle_key(void *p)
// {
// 	int		move_step;
// 	t_map 	*map;
// 	double	new_x;
// 	double	new_y;
// 	map = (t_map *)p;
// 	if (!key_pressed(map))
// 		return ;
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_Q))
// 		map->is_rot = 2;
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_B))
// 		map->is_rot = 0;
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
// 		map->player->rotAngle = normAngle(map->player->rotSpeed + map->player->rotAngle);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
// 		map->player->rotAngle = normAngle(map->player->rotAngle - map->player->rotSpeed);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_UP))
// 		up(map);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_S) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
// 		down(map);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
// 		left(map);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
// 		right(map);
// 	if (mlx_is_key_down(map->mlx, MLX_KEY_K))
// 	{
// 		shot(map);
// 		return ;
// 	}
// 	else if (mlx_is_key_down(map->mlx, MLX_KEY_R))
// 	{
// 		reload(map);
// 		return ;
// 	}
// 	cast_rays(map);
// 	render(map);
// 	mini_map(map);
// }

void init_player(t_map *map)
{
	map->player->pos.x = map->player->pos.x * TILE_SIZE + 150;
	map->player->pos.y = map->player->pos.y * TILE_SIZE  + 150;
	map->player->xDir = 0;
	map->player->yDir = 0;
	map->player->moveSpeed = 100;
	if (map->player->dir == 'E')
		map->player->rotAngle = 0;
	else if (map->player->dir == 'S')
		map->player->rotAngle = M_PI / 2;
	else if (map->player->dir == 'W')
		map->player->rotAngle = M_PI;
	else if (map->player->dir == 'N')
		map->player->rotAngle = 3 * M_PI / 2;
	map->player->rotSpeed = 5 * (M_PI / 180);
	map->player->fov = 60 * M_PI / 180;
}
