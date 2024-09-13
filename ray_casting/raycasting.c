#include "../parsing/parsing.h"

void	init_ray(t_ray *new_ray, double ray_angle)
{
	new_ray->next = NULL;
	new_ray->is_door = 0;
	new_ray->is_close_door = 0;
	new_ray->ray_angle = ray_angle;
	new_ray->is_up = 1;
	if (ray_angle > 0 && ray_angle < M_PI)
		new_ray->is_up = 0;
	new_ray->is_right = 1;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		new_ray->is_right = 0;
	new_ray->found_x_inter = 0;
	new_ray->found_y_inter = 0;
}

void	check_horz(t_ray *new_ray, t_map *map)
{
	new_ray->f_y_inter = floor(map->player->pos.y / TILE_SIZE) * TILE_SIZE;
	if (!new_ray->is_up)
		new_ray->f_y_inter += TILE_SIZE;
	new_ray->f_x_inter = map->player->pos.x + (new_ray->f_y_inter - map->player->pos.y) / tan(new_ray->ray_angle);
	new_ray->y_steps = TILE_SIZE;
	if (new_ray->is_up)
		new_ray->y_steps *= -1;
	new_ray->x_steps = TILE_SIZE / tan(new_ray->ray_angle);
	if (!new_ray->is_right && new_ray->x_steps > 0)
		new_ray->x_steps *= -1;
	if (new_ray->is_right && new_ray->x_steps < 0)
		new_ray->x_steps *= -1;
	while (1 && new_ray->f_y_inter <= map->height * TILE_SIZE && new_ray->f_x_inter <= map->width * TILE_SIZE && new_ray->f_y_inter >= 0 && new_ray->f_x_inter >= 0)
	{
		new_ray->h_x_inter = (int)floor(new_ray->f_x_inter);
		new_ray->h_y_inter = (int)floor(new_ray->f_y_inter);
		if (map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == '1'
		|| map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == 'D'
		|| map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == 'O')
		{
			if (map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == 'O')
			{
				new_ray->is_close_door = 1;
				new_ray->c_door_dis = calc_d_dis(*map, *new_ray, 1);
				new_ray->x_door = (new_ray->f_x_inter) / TILE_SIZE;
				new_ray->y_door = (new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE;
			}
			if (map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == '1'
			|| map->arr[(int)floor(new_ray->f_y_inter - new_ray->is_up) / TILE_SIZE][(int)floor(new_ray->f_x_inter) / TILE_SIZE] == 'D')
			{
				new_ray->found_x_inter = 1;
				break;
			}
		}
		new_ray->f_x_inter += new_ray->x_steps;
		new_ray->f_y_inter += new_ray->y_steps;
	}
}

void	check_vert(t_ray *new_ray, t_map *map)
{
	new_ray->f_x_inter = floor(map->player->pos.x / TILE_SIZE) * TILE_SIZE;
	if (new_ray->is_right)
		new_ray->f_x_inter += TILE_SIZE;
	new_ray->f_y_inter = map->player->pos.y + (new_ray->f_x_inter - map->player->pos.x) * tan(new_ray->ray_angle);
	new_ray->x_steps = TILE_SIZE;
	if (!new_ray->is_right)
		new_ray->x_steps *= -1;
	new_ray->y_steps = TILE_SIZE * tan(new_ray->ray_angle);
	if (new_ray->is_up && new_ray->y_steps > 0)
		new_ray->y_steps *= -1;
	if (!new_ray->is_up && new_ray->y_steps < 0)
		new_ray->y_steps *= -1;
	while (1 && new_ray->f_y_inter <= map->height * TILE_SIZE && new_ray->f_x_inter <= map->width * TILE_SIZE && new_ray->f_y_inter >= 0 && new_ray->f_x_inter >= 0)
	{
		new_ray->v_x_inter = (int)floor(new_ray->f_x_inter);
		new_ray->v_y_inter = (int)floor(new_ray->f_y_inter);
		if (map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == '1'
			|| map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == 'D'
			||  map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == 'O')
		{
			if (map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == 'O')
			{
				new_ray->is_close_door = 1;
				new_ray->c_door_dis = calc_d_dis(*map, *new_ray, 2);
				new_ray->x_door = (new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE;
				new_ray->y_door = (new_ray->f_y_inter) / TILE_SIZE;
			}
			if (map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == '1'
			|| map->arr[(int)floor(new_ray->f_y_inter) / TILE_SIZE][(int)floor(new_ray->f_x_inter + new_ray->is_right - 1) / TILE_SIZE] == 'D')
			{
				new_ray->found_y_inter = 2;
				break;
			}
		}
		new_ray->f_x_inter += new_ray->x_steps;
		new_ray->f_y_inter += new_ray->y_steps;
	}
}

void	its_horz(t_ray *new_ray, t_map *map)
{
	new_ray->x_inter = new_ray->h_x_inter;
	new_ray->y_inter = new_ray->h_y_inter;
	new_ray->ray_dis = new_ray->h_dis;
	new_ray->ray_dir = 1;
	if (map->arr[(new_ray->y_inter - new_ray->is_up) / TILE_SIZE][(new_ray->x_inter) / TILE_SIZE] == 'D')
	{
		new_ray->is_door = 1;
		new_ray->x_door = (new_ray->x_inter) / TILE_SIZE;
		new_ray->y_door = (new_ray->y_inter - new_ray->is_up) / TILE_SIZE;
	}
}

void	its_vert(t_ray *new_ray, t_map *map)
{
	new_ray->x_inter = new_ray->v_x_inter;
	new_ray->y_inter = new_ray->v_y_inter;
	new_ray->ray_dis = new_ray->v_dis;
	new_ray->ray_dir = 2;
	if (map->arr[(new_ray->y_inter) / TILE_SIZE][(new_ray->x_inter + new_ray->is_right - 1) / TILE_SIZE] == 'D')
	{
		new_ray->is_door = 1;
		new_ray->x_door = (new_ray->x_inter + new_ray->is_right - 1) / TILE_SIZE;
		new_ray->y_door = (new_ray->y_inter) / TILE_SIZE;
	}
}

void	cast_rays(t_map *map)
{
	t_ray	*new_ray;
	int z = 0;
	double	ray_angle;

	map->can_open = 0;
	map->can_close = 0;
	map->rays = NULL;
	map->door_ray = NULL;
	ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
	while (z < WIDTH)
	{
		new_ray = malloc(sizeof(t_ray));
		if (z == WIDTH / 2)
			map->door_ray = new_ray;
		init_ray(new_ray, ray_angle);
		check_horz(new_ray, map);
		check_vert(new_ray, map);


		new_ray->h_dis = calc_h_dis(*map, *new_ray);
		new_ray->v_dis = calc_v_dis(*map, *new_ray);


		if (new_ray->h_dis < new_ray->v_dis)
			its_horz(new_ray, map);
		else
			its_vert(new_ray, map);


		if (z == WIDTH / 2 && (map->door_ray->is_door || map->door_ray->is_close_door))
		{
			if (map->door_ray->is_door && map->door_ray->c_door_dis < 200)
				map->can_open = 1;
			else if (map->door_ray->is_close_door && map->door_ray->c_door_dis < 200 && map->door_ray->c_door_dis > 100)
				map->can_close = 1;
		}

		add_back_ray(&map->rays, new_ray);
		ray_angle = normAngle(map->player->fov / (WIDTH) + ray_angle);
		z++;
	}
}

