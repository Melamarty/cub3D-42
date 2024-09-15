#include "../parsing/parsing.h"

t_ray *last_ray(t_ray *rays)
{
	while (rays->next)
		rays = rays->next;
	return (rays);
}

void	add_back_ray(t_ray **rays, t_ray *new_ray)
{
	if (!*rays)
		*rays = new_ray;
	else
		last_ray(*rays)->next = new_ray;
}

unsigned int	create_color(unsigned char r, unsigned char g,
		unsigned char b, unsigned char a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

double	normangle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
	{
		angle += (2 * M_PI);
	}
	return (angle);
}

void	init_player(t_map *map)
{
	map->player->pos.x = map->player->pos.x * TILE_SIZE + 150;
	map->player->pos.y = map->player->pos.y * TILE_SIZE + 150;
	map->player->xDir = 0;
	map->player->yDir = 0;
	map->player->moveSpeed = 20;
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
