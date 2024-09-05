#include "../parsing/parsing.h"

void	up(t_map *map)
{
	int	move_step;
	double	new_x;
	double	new_y;

	move_step = map->player->moveSpeed;
	new_x = move_step * cos(map->player->rotAngle);
	new_y = move_step * sin(map->player->rotAngle);
	if (!is_wall((map->player->pos.x + round(new_x) ), (map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	down(t_map *map)
{
	int	move_step;
	double	new_x;
	double	new_y;

	move_step = map->player->moveSpeed * -1;
	new_x = move_step * cos(map->player->rotAngle);
	new_y = move_step * sin(map->player->rotAngle);
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	left(t_map *map)
{
	int	move_step;
	double	new_x;
	double	new_y;

	move_step = map->player->moveSpeed * -1;
	new_x = cos(map->player->rotAngle + M_PI_2) * move_step;
	new_y = sin(map->player->rotAngle + M_PI_2) * move_step;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}

void	right(t_map *map)
{
	int	move_step;
	double	new_x;
	double	new_y;

	move_step = map->player->moveSpeed;
	new_x = cos(map->player->rotAngle + M_PI_2) * move_step;
	new_y = sin(map->player->rotAngle + M_PI_2) * move_step;
	if (!is_wall((map->player->pos.x + round(new_x)), (map->player->pos.y + round(new_y)), *map))
	{
		map->player->pos.x += round(new_x);
		map->player->pos.y += round(new_y);
	}
}
