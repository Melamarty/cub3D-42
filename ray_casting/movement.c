#include "../parsing/parsing.h"

int	is_wall(int new_x, int new_y, t_map map)
{
	double	ang;
	int		px;
	int		py;
	int		i;

	i = 0;
	ang = map.player->rotAngle;
	while (i < 360)
	{
		px = (new_x) + 100 * cos(ang);
		py = (new_y) + 100 * sin(ang);
		ang += 180 / M_PI;
		if (px < 0 || px / TILE_SIZE >= map.width || py < 0
			|| py / TILE_SIZE >= map.height
			|| map.arr[py / TILE_SIZE][px / TILE_SIZE] == '1'
			|| map.arr[py / TILE_SIZE][px / TILE_SIZE] == 'D')
			return (1);
		i++;
	}
	return (0);
}

void	key_move(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->player->rotAngle = normangle(map->player->rotSpeed
				+ map->player->rotAngle);
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->player->rotAngle = normangle(map->player->rotAngle
				- map->player->rotSpeed);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP))
		up(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		down(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		left(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		right(map);
}

int	key_listenter(t_map *map)
{
	int		move_step;
	double	new_x;
	double	new_y;

	if (!key_pressed(map))
		return (0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_K)
		&& !map->is_shot && !map->is_reload)
		return (map->is_shot = 1, map->frame = 0, 0);
	else if (mlx_is_key_down(map->mlx, MLX_KEY_R)
		&& !map->is_reload && !map->is_shot)
		return (map->is_reload = 1, map->frame = 7, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_Q))
		return (map->is_rot = 2, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_B))
		return (map->is_rot = 0, 0);
	if (mlx_is_key_down(map->mlx, MLX_KEY_O))
		open_door(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_C))
		close_door(map);
	key_move(map);
	cast_rays(map);
	render(map);
	mini_map(map);
	return (0);
}

void	handle_key(void *p)
{
	t_map	*map;

	map = (t_map *)p;
	key_listenter(map);
}

int	key_pressed(t_map *map)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W)
		|| mlx_is_key_down(map->mlx, MLX_KEY_A)
		|| mlx_is_key_down(map->mlx, MLX_KEY_S)
		|| mlx_is_key_down(map->mlx, MLX_KEY_D)
		|| mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(map->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(map->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(map->mlx, MLX_KEY_Q)
		|| mlx_is_key_down(map->mlx, MLX_KEY_B)
		|| mlx_is_key_down(map->mlx, MLX_KEY_K)
		|| mlx_is_key_down(map->mlx, MLX_KEY_R)
		|| mlx_is_key_down(map->mlx, MLX_KEY_O)
		|| mlx_is_key_down(map->mlx, MLX_KEY_C))
		return (1);
	return (0);
}

void	up(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player->moveSpeed * cos(map->player->rotAngle);
	new_y = map->player->moveSpeed * sin(map->player->rotAngle);
	if (!is_wall((map->player->pos.x + round(new_x)),
			(map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	down(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = map->player->moveSpeed
		* cos(normangle(map->player->rotAngle + M_PI));
	new_y = map->player->moveSpeed
		* sin(normangle(map->player->rotAngle + M_PI));
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	left(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = cos(normangle(map->player->rotAngle - M_PI_2))
		* map->player->moveSpeed;
	new_y = sin(normangle(map->player->rotAngle - M_PI_2))
		* map->player->moveSpeed;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	right(t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = cos(normangle(map->player->rotAngle + M_PI_2))
		* map->player->moveSpeed;
	new_y = sin(normangle(map->player->rotAngle + M_PI_2))
		* map->player->moveSpeed;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y
				+ round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}
