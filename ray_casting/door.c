#include "../parsing/parsing.h"

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
