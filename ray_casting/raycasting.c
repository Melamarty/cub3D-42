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

void	draw_rays(t_map *map)
{
	map->m_rays = malloc(sizeof(the_rays));
	double	x, y;
	map->m_rays->x1 = 5 * m_cube + 5;
	map->m_rays->y1 = 3 * m_cube + 5;
	map->m_rays->ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
	for (int i = 0; i < 30 * m_cube; i++)
	{
		x = map->m_rays->x1;
		y = map->m_rays->y1;
		map->m_rays->x2 = (map->m_rays->x1 + 30 * cos(map->m_rays->ray_angle));
		map->m_rays->y2 = (map->m_rays->y1 + 30 * sin(map->m_rays->ray_angle));
		map->m_rays->dx = map->m_rays->x2 - map->m_rays->x1;
		map->m_rays->dy = map->m_rays->y2 - map->m_rays->y1;
		if (abs(map->m_rays->dx) > abs(map->m_rays->dy))
			map->m_rays->steps = abs(map->m_rays->dx);
		else
			map->m_rays->steps = abs(map->m_rays->dy);
		map->m_rays->xinc = map->m_rays->dx / (double)map->m_rays->steps;
		map->m_rays->yinc = map->m_rays->dy / (double)map->m_rays->steps;
		for (int i = 0; i < map->m_rays->steps; i++)
		{
			mlx_put_pixel(map->img, round(x), round(y), create_color(255, 255, 0, 255));
			x += map->m_rays->xinc;
			y += map->m_rays->yinc;
		}
		// printf("x: %d y: %d inter: %d dis: %f\n", map->ray_x, map->ray_y, map->ray_dir, map->ray_dis);
		map->m_rays->ray_angle = normAngle(map->player->fov / (map->width * m_cube) + map->m_rays->ray_angle);
	}
}

double	calc_dis(t_map map, the_rays ray)
{
	int	dx;
	int	dy;
	double dis;

	dx = abs(ray.x_inter - map.player->pos.x + 10);
	dy = abs(ray.y_inter - map.player->pos.y + 10);
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
	for (int i = 0; i < map->width * cube_width; i++)
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

int	key_pressed(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_A) || mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D) || mlx_is_key_down(map->mlx, MLX_KEY_RIGHT) || mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
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
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player->rotAngle = normAngle(map->player->rotSpeed + map->player->rotAngle);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player->rotAngle = normAngle(map->player->rotAngle - map->player->rotSpeed);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		move_step = map->player->moveSpeed;
		new_x = move_step * cos(map->player->rotAngle);
		new_y = move_step * sin(map->player->rotAngle);
		if (!is_wall((map->player->pos.x + round(new_x) ) / cube_width,( map->player->pos.y + round(new_y)) / cube_width, *map))
		{
			map->player->pos.x += round(new_x);
			map->player->pos.y += round(new_y);
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		move_step = map->player->moveSpeed * -1;
		new_x = move_step * cos(map->player->rotAngle);
		new_y = move_step * sin(map->player->rotAngle);
		if (!is_wall((map->player->pos.x + round(new_x)) / cube_width, (map->player->pos.y + round(new_y)) / cube_width, *map))
		{
			map->player->pos.x += round(new_x);
			map->player->pos.y += round(new_y);
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		move_step = map->player->moveSpeed * -1;
		new_x = cos(map->player->rotAngle + M_PI_2) * move_step;
		new_y = sin(map->player->rotAngle + M_PI_2) * move_step;
		if (!is_wall((map->player->pos.x + round(new_x)) / cube_width, (map->player->pos.y + round(new_y)) / cube_width, *map))
		{
			map->player->pos.x += round(new_x);
			map->player->pos.y += round(new_y);
		}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		move_step = map->player->moveSpeed;
		new_x = cos(map->player->rotAngle + M_PI_2) * move_step;
		new_y = sin(map->player->rotAngle + M_PI_2) * move_step;
		if (!is_wall((map->player->pos.x + round(new_x)) / cube_width, (map->player->pos.y + round(new_y)) / cube_width, *map))
		{
			map->player->pos.x += round(new_x);
			map->player->pos.y += round(new_y);
		}
	}
	cast_rays(map);
	render(map);
	// mini_map(map);
}

void init_player(t_map *map)
{
	map->player->pos.x *= cube_width;
	map->player->pos.y *= cube_width;
	map->player->xDir = 0;
	map->player->yDir = 0;
	map->player->moveSpeed = 5;
	map->player->rotAngle = M_PI / 2;
	map->player->rotSpeed = 5 * (M_PI / 180);
	map->player->fov = 60 * M_PI / 180;
}

void render_map(t_map *map)
{
	int	xStart;
	int	yStart;
	int	yStartSave;
	unsigned int	color;

	xStart = (map->player->pos.x - (5 * cube_width)) * m_cube / cube_width;
    yStart = (map->player->pos.y - (3 * cube_width)) * m_cube / cube_width;
	yStartSave = yStart;
	for(int i = 0; i < 10 * m_cube; i ++)
	{
		yStart = yStartSave;
		for (int j = 0; j <  6 * m_cube; j++)
		{
			if (map->arr[yStart / m_cube][xStart / m_cube] == '1')
				color = create_color(0, 100, 0, 255);
			else
				color = create_color(144, 238, 144, 255);
			mlx_put_pixel(map->img, i, j, color);
			yStart ++;
		}
		xStart ++;
	}
}

void render_player(t_map *map)
{
	int	x;
	int	y;
	unsigned int	color;

	x = 5 * m_cube;
	y = 3 * m_cube;
	color = create_color(255, 0, 0, 255);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mlx_put_pixel(map->img, x + j, y + i, color);
		}
	}
	draw_rays(map);
}

void	mini_map(t_map *map)
{
	render_map(map);
	render_player(map);
}
