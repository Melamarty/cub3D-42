#include "../parsing/parsing.h"

double	calc_d_dis(t_map map, t_ray ray, int i)
{
	int	dx;
	int	dy;
	double dis;

	if (i == 1)
	{
		dx = fabs(ray.h_x_inter - map.player->pos.x);
		dy = fabs(ray.h_y_inter - map.player->pos.y);
	}
	else
	{
		dx = fabs(ray.v_x_inter - map.player->pos.x);
		dy = fabs(ray.v_y_inter - map.player->pos.y);
	}
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

double	calc_h_dis(t_map map, t_ray ray)
{
	int	dx;
	int	dy;
	double dis;

	if (!ray.found_x_inter)
		return (INT_MAX);
	dx = fabs(ray.h_x_inter - map.player->pos.x);
	dy = fabs(ray.h_y_inter - map.player->pos.y);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}

double	calc_v_dis(t_map map, t_ray ray)
{
	int	dx;
	int	dy;
	double dis;
	if (!ray.found_y_inter)
		return (INT_MAX);
	dx = fabs(ray.v_x_inter - map.player->pos.x);
	dy = fabs(ray.v_y_inter - map.player->pos.y);
	dis = sqrt(dx * dx + dy * dy);
	return (dis);
}