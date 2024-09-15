#include "../parsing/parsing.h"

void	dda_calc(t_map *map)
{
	map->m_rays->x2 = (map->m_rays->x1 + 1000 * cos(map->m_rays->ray_angle));
	map->m_rays->y2 = (map->m_rays->y1 + 1000 * sin(map->m_rays->ray_angle));
	map->m_rays->dx = map->m_rays->x2 - map->m_rays->x1;
	map->m_rays->dy = map->m_rays->y2 - map->m_rays->y1;
	if (abs(map->m_rays->dx) > abs(map->m_rays->dy))
		map->m_rays->steps = abs(map->m_rays->dx);
	else
		map->m_rays->steps = abs(map->m_rays->dy);
	map->m_rays->xinc = map->m_rays->dx / (double)map->m_rays->steps;
	map->m_rays->yinc = map->m_rays->dy / (double)map->m_rays->steps;
}

int	dda_x(t_map *map, double *x, double *y)
{
	*x += map->m_rays->xinc;
	map->m_rays->rx = (map->player->pos.x + (*x - map->m_rays->x1)
			* TILE_SIZE / m_cube);
	map->m_rays->ry = (map->player->pos.y + (*y - map->m_rays->y1)
			* TILE_SIZE / m_cube);
	map->m_rays->map_x = (int)round(map->m_rays->rx) / TILE_SIZE;
	map->m_rays->map_y = (int)round(map->m_rays->ry) / TILE_SIZE;
	if (map->m_rays->map_x < 0 || map->m_rays->map_y < 0
		|| map->m_rays->map_x >= map->width
		|| map->m_rays->map_y >= map->height)
		return (1);
	if (map->arr[map->m_rays->map_y][map->m_rays->map_x] == '1'
		|| map->arr[map->m_rays->map_y][map->m_rays->map_x] == 'D')
		return (1);
	return (0);
}

int	dda_y(t_map *map, double *x, double *y)
{
	*y += map->m_rays->yinc;
	map->m_rays->rx = (map->player->pos.x + (*x - map->m_rays->x1)
			* TILE_SIZE / m_cube);
	map->m_rays->ry = (map->player->pos.y + (*y - map->m_rays->y1)
			* TILE_SIZE / m_cube);
	map->m_rays->map_x = (int)round(map->m_rays->rx) / TILE_SIZE;
	map->m_rays->map_y = (int)round(map->m_rays->ry) / TILE_SIZE;
	if (map->m_rays->map_x < 0 || map->m_rays->map_y < 0
		|| map->m_rays->map_x >= map->width
		|| map->m_rays->map_y >= map->height)
		return (1);
	if (map->arr[map->m_rays->map_y][map->m_rays->map_x] == '1'
		|| map->arr[map->m_rays->map_y][map->m_rays->map_x] == 'D')
		return (1);
	return (0);
}

void	draw_rays(t_map *map)
{
	double	x;
	double	y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map->m_rays = malloc(sizeof(t_ray));
	map->m_rays->x1 = 5 * m_cube;
	map->m_rays->y1 = 3 * m_cube;
	map->m_rays->ray_angle = normAngle(map->player->rotAngle
			- map->player->fov / 2);
	while (i < m_cube * 30)
	{
		x = map->m_rays->x1;
		y = map->m_rays->y1;
		j = 0;
		dda_calc(map);
		while (j < map->m_rays->steps)
		{
			if (dda_x(map, &x, &y))
				break ;
			if (dda_y(map, &x, &y))
				break ;
			if (round(x) >= 0 && round(x) < 300
				&& round(y) >= 0 && round(y) < 180)
				mlx_put_pixel(map->img, round(x), round(y),
					create_color(255, 255, 0, 255));
			j++;
		}
		map->m_rays->ray_angle = normAngle(map->player->fov
				/ (30 * m_cube) + map->m_rays->ray_angle);
		i++;
	}
}

void 	render_map(t_map *map)
{
	t_mmap	mmap;

	mmap.x_start = (map->player->pos.x - (5 * TILE_SIZE)) * m_cube / TILE_SIZE;
	mmap.y_start = (map->player->pos.y - (3 * TILE_SIZE)) * m_cube / TILE_SIZE;
	mmap.y_start_save = mmap.y_start;
	mmap.i = 0;
	mmap.j = 0;
	while (mmap.i < 10 * m_cube)
	{
		mmap.y_start = mmap.y_start_save;
		mmap.j = 0;
		while (mmap.j <  6 * m_cube)
		{
			if (mmap.y_start < 0 || mmap.x_start < 0
				|| mmap.y_start / m_cube >= map->height
				|| mmap.x_start / m_cube >= map->width)
				mmap.color = create_color(0, 0, 0, 255);
			else if (map->arr[mmap.y_start
					/ m_cube][mmap.x_start / m_cube] == '1')
				mmap.color = create_color(50, 50, 50, 255);
			else if (map->arr[mmap.y_start
					/ m_cube][mmap.x_start / m_cube] == 'D')
				mmap.color = create_color(0, 255, 0, 255);
			else
				mmap.color = create_color(211, 211, 211, 255);
			mlx_put_pixel(map->img, mmap.i, mmap.j, mmap.color);
			mmap.y_start ++;
			mmap.j++;
		}
		mmap.x_start ++;
		mmap.i ++;
	}
}

void render_player(t_map *map)
{
	t_mmap	mmap;

	mmap.x_start = 5 * m_cube - 5;
	mmap.y_start = 3 * m_cube - 5;
	mmap.color = create_color(255, 0, 0, 255);
	mmap.i = 0;
	mmap.j = 0;
	while (mmap.i < 10)
	{
		mmap.j = 0;
		while (mmap.j < 10)
		{
			mlx_put_pixel(map->img, mmap.x_start + mmap.j,
				mmap.y_start + mmap.i, mmap.color);
			mmap.j ++;
		}
		mmap.i ++;
	}
	draw_rays(map);
}

void	draw_cercle(t_map *map)
{
	int		px;
	int		py;
	double	ang;
	int		i;

	ang = map->player->rotAngle;
	i = 0;
	while (i < 360)
	{
		px = (5 * m_cube) + 10 * cos(ang);
		py = (3 * m_cube) + 10 * sin(ang);
		ang += 180 / M_PI;
		mlx_put_pixel(map->img, px, py, create_color(255, 255, 255, 51));
		i++;
	}
}

void	mini_map(t_map *map)
{
	render_map(map);
	render_player(map);
	draw_cercle(map);
}
