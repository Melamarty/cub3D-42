#include "../parsing/parsing.h"

void	mouse_rot(void *p)
{
	t_map *map = (t_map *)p;
	if (map->is_rot == 1)
	{
		cast_rays(map);
		render(map);
		mini_map(map);
		map->is_rot = 0;
	}
}

void mouse_handler(double x, double y, void *p)
{
	t_map *map;
	int	half_width;
	int	half_height;

	map = (t_map *)p;
	if (map->is_rot == 2)
	{
		mlx_set_cursor_mode(map->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	half_width = map->width * cube_width / 2;
	half_height = map->height * cube_width / 2;
	if (x > half_width)
	{
		map->player->rotAngle = normAngle(map->player->rotAngle + map->player->rotSpeed);
		map->is_rot = 1;
	}
	else
	{
		map->player->rotAngle = normAngle(map->player->rotAngle - map->player->rotSpeed);
		map->is_rot = 1;
	}
	mlx_set_mouse_pos(map->mlx, half_width, half_height);
	mlx_set_cursor_mode(map->mlx, MLX_MOUSE_HIDDEN);
}