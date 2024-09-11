#include "../parsing/parsing.h"

void	draw_rays(t_map *map)
{
	map->m_rays = malloc(sizeof(t_ray));
	double	x, y;
	map->m_rays->x1 = 5 * m_cube;
	map->m_rays->y1 = 3 * m_cube;
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

void render_map(t_map *map)
{
	int	xStart;
	int	yStart;
	int	yStartSave;
	unsigned int	color;

	xStart = (map->player->pos.x - (5 * TILE_SIZE)) * m_cube / TILE_SIZE;
    yStart = (map->player->pos.y - (3 * TILE_SIZE)) * m_cube / TILE_SIZE;
	yStartSave = yStart;
	for(int i = 0; i < 10 * m_cube; i ++)
	{
		yStart = yStartSave;
		for (int j = 0; j <  6 * m_cube; j++)
		{
			if (yStart < 0 || xStart < 0 || yStart / m_cube >= map->height || xStart / m_cube >= map->width)
				color = create_color(0, 0, 0, 255);
			else if ( map->arr[yStart / m_cube][xStart / m_cube] == '1')
				color = create_color(50, 50, 50, 255);
			else if ( map->arr[yStart / m_cube][xStart / m_cube] == 'D')
				color = create_color(0, 255, 0, 255);
			else
				color = create_color(211, 211, 211, 255);
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

	x = 5 * m_cube - 5;
	y = 3 * m_cube - 5;
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

void	draw_cercle(t_map *map)
{
	int	x;
	int	y;
	int	px;
	int	py;
	double	ang;

	x = 5 * m_cube;
	y = 3 * m_cube;
	ang = map->player->rotAngle;
	for (int i = 0; i < 360; i++)
	{
		px = x + 10 * cos(ang);
		py = y + 10 * sin(ang);
		ang += 180 / M_PI;
		mlx_put_pixel(map->img, px, py, create_color(255, 255, 255, 51));
	}
}

void	mini_map(t_map *map)
{
	render_map(map);
	render_player(map);
	draw_cercle(map);
}
