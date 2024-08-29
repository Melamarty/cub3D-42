// #include "../parsing/parsing.h"

// // unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
// //     return (r << 24) | (g << 16) | (b << 8) | a;
// // }

// // double normAngle(double angle)
// // {
// //     angle = fmod(angle, 2 * M_PI);
// //     if (angle < 0)
// // 	{
// //         angle += (2 * M_PI);
// //     }
// //     return (angle);
// // }

// // double	calc_dis(t_map map, the_rays ray)
// // {
// // 	int	dx;
// // 	int	dy;
// // 	double dis;

// // 	dx = abs(map.rays->x_inter - ray.x1);
// // 	dy = abs(map.rays->y_inter - ray.y1);
// // 	dis = sqrt(dx * dx + dy * dy);

// // 	return (dis);
// // }

// void cast_rays(t_map *map)
// {
// 	the_rays	ray;
// 	ray.x1 = map->player->pos.x + 5;
// 	ray.y1 = map->player->pos.y + 5;
// 	double x, y;
// 	map->rays->ray_angle = normAngle(map->player->rotAngle - map->player->fov / 2);
// 	for (int i = 0; i < map->width * cube_width; i++)
// 	{
// 		x = ray.x1;
// 		y = ray.y1;
// 		ray.x2 = (ray.x1 + 10000 * cos(map->rays->ray_angle));
// 		ray.y2 = (ray.y1 + 10000 * sin(map->rays->ray_angle));
// 		ray.dx = ray.x2 - ray.x1;
// 		ray.dy = ray.y2 - ray.y1;
// 		if (abs(ray.dx) > abs(ray.dy))
// 			ray.steps = abs(ray.dx);
// 		else
// 			ray.steps = abs(ray.dy);
// 		ray.xinc = ray.dx / (double)ray.steps;
// 		ray.yinc = ray.dy / (double)ray.steps;
// 		for (int i = 0; i < ray.steps; i++)
// 		{
// 			mlx_put_pixel(map->img, round(x), round(y), create_color(255, 255, 0, 255));
// 			map->rays->x_inter = round(x);
// 			map->rays->y_inter = round(y);
// 			x += ray.xinc;
// 			if (map->arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
// 			{
// 				map->rays->ray_dir = 2;
// 				break ;
// 			}
// 			y += ray.yinc;
// 			if (map->arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
// 			{
// 				map->rays->ray_dir = 1;
// 				break ;
// 			}
// 		}
// 		map->rays->ray_dis = calc_dis(*map, ray);
// 		// printf("x: %d y: %d inter: %d dis: %f\n", map->ray_x, map->ray_y, map->ray_dir, map->ray_dis);
// 		map->rays->ray_angle = normAngle(map->player->fov / map->width + map->rays->ray_angle);
// 	}
// }
// // void cast_rays(t_map map)
// // {
// // 	the_rays	ray;
// // 	ray.x1 = map.player->pos.x + 5;
// // 	ray.y1 = map.player->pos.y + 5;
// // 	double x, y;
// // 	map.rays->ray_angle = normAngle(map.player->rotAngle - map.player->fov / 2);
// // 	for (int i = 0; i < ft_strlen(map.arr[0]); i++)
// // 	{
// // 		x = ray.x1;
// // 		y = ray.y1;
// // 		ray.x2 = (ray.x1 + 10000 * cos(map.rays->ray_angle));
// // 		ray.y2 = (ray.y1 + 10000 * sin(map.rays->ray_angle));
// // 		ray.dx = ray.x2 - ray.x1;
// // 		ray.dy = ray.y2 - ray.y1;
// // 		if (abs(ray.dx) > abs(ray.dy))
// // 			ray.steps = abs(ray.dx);
// // 		else
// // 			ray.steps = abs(ray.dy);
// // 		ray.xinc = ray.dx / (double)ray.steps;
// // 		ray.yinc = ray.dy / (double)ray.steps;
// // 		for (int i = 0; i < ray.steps; i++)
// // 		{
// // 			mlx_put_pixel(map.img, round(x), round(y), create_color(255, 255, 0, 255));
// // 			map.rays->x_inter = round(x);
// // 			map.rays->y_inter = round(y);
// // 			x += ray.xinc;
// // 			if (map.arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
// // 			{
// // 				map.rays->ray_dir = 2;
// // 				break ;
// // 			}
// // 			y += ray.yinc;
// // 			if (map.arr[(int)round(y) / cube_width][(int)round(x) / cube_width] == '1')
// // 			{
// // 				map.rays->ray_dir = 1;
// // 				break ;
// // 			}
// // 		}
// // 		map.rays->ray_dis = calc_dis(map, ray);
// // 		// printf("x: %d y: %d inter: %d dis: %f\n", map.x_inter, map.y_inter, map.ray_dir, map.ray_dis);
// // 		map.rays->ray_angle = normAngle(map.player->fov / ft_strlen(map.arr[0]) + map.rays->ray_angle);
// // 	}
// // }

// // int	is_wall(int new_x, int new_y, t_map map)
// // {
// // 	if (map.arr[new_y / cube_width][new_x / cube_width] == '1')
// // 		return (1);
// // 	return (0);
// // }

// // void handle_key(mlx_key_data_t keydata, void *p)
// // {
// // 	int	move_step;
// // 	t_map *map;
// // 	int	new_x;
// // 	int	new_y;
// // 	map = (t_map *)p;
// // 	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
// // 	{
// // 		if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
// // 			map->player->xDir = 1;
// // 		else if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
// // 			map->player->xDir = -1;
// // 		else if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
// // 			map->player->yDir = 1;
// // 		else if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
// // 			map->player->yDir = -1;
// // 		map->player->rotAngle = normAngle(map->player->xDir * map->player->rotSpeed + map->player->rotAngle);
// // 		move_step = map->player->moveSpeed * map->player->yDir;
// // 		new_x = map->player->pos.x +  move_step * cos(map->player->rotAngle);
// // 		new_y = map->player->pos.y +  move_step * sin(map->player->rotAngle);
// // 		if (!is_wall(new_x, new_y, *map))
// // 		{
// // 			map->player->pos.x = new_x;
// // 			map->player->pos.y = new_y;
// // 		}
// // 		rendering(map);
// // 	}
// // 	else if (keydata.action == MLX_RELEASE)
// // 	{
// // 		if (keydata.key == MLX_KEY_RIGHT)
// // 			map->player->xDir = 0;
// // 		else if (keydata.key == MLX_KEY_LEFT)
// // 			map->player->xDir = 0;
// // 		else if (keydata.key == MLX_KEY_UP)
// // 			map->player->yDir = 0;
// // 		else if (keydata.key == MLX_KEY_DOWN)
// // 			map->player->yDir = 0;
// // 	}
// // }

// void render_cube(int x, int y, t_map *map)
// {
// 	unsigned int color;
// 	if (map->arr[y / cube_width][x / cube_width] == '1')
// 		color = create_color(0, 0, 255, 255);
// 	else
// 		color = create_color(108, 180, 238, 255);
// 	for (int i = 0; i < cube_width; i++)
// 	{
// 		for (int j = 0; j < cube_width; j++)
// 		{
// 			mlx_put_pixel(map->img, x + j, y + i, color);
// 		}
// 	}
// }

// void init_player(t_map *map)
// {
// 	map->player->xDir = 0;
// 	map->player->yDir = 0;
// 	map->player->moveSpeed = 10;
// 	map->player->rotAngle = M_PI;
// 	map->player->rotSpeed = map->player->moveSpeed * (M_PI / 180);
// 	map->player->fov = 60 * M_PI / 180;
// }

// void render_map(t_map *map)
// {
// 	for(int i = 0; i < map->width; i++)
// 	{
// 		for (int j = 0; j < map->height; j++)
// 		{
// 			render_cube(i * cube_width, j * cube_width, map);
// 		}
// 	}
// }

// void render_player(t_map map)
// {
// 	for (int i = 0; i < 10; i++)
// 	{
// 		for (int j = 0; j < 10; j++)
// 		{
// 			mlx_put_pixel(map.img, map.player->pos.x + j, map.player->pos.y + i, create_color(255, 0, 0, 255));
// 		}
// 	}
// 	cast_rays(&map);
// }

// void	raycasting(t_map *map)
// {
// 	render_map(map);
// 	render_player(*map);
// }

// // void render_cube(int x, int y, mlx_image_t *img, char **s)
// // {
// // 	unsigned int color;
// // 	if (s[y / cube_width][x / cube_width] == '1')
// // 		color = create_color(0, 0, 255, 255);
// // 	else
// // 		color = create_color(108, 180, 238, 255);
// // 	for (int i = 0; i < cube_width; i++)
// // 	{
// // 		for (int j = 0; j < cube_width; j++)
// // 		{
// // 			mlx_put_pixel(img, x + j, y + i, color);
// // 		}
// // 	}
// // }

// // void init_player(t_player *player)
// // {
// // 	player->xDir = 0;
// // 	player->yDir = 0;
// // 	player->moveSpeed = 10;
// // 	player->rotAngle = M_PI;
// // 	player->rotSpeed = player->moveSpeed * (M_PI / 180);
// // 	player->fov = 60 * M_PI / 180;
// // }

// // void render_map(t_map *map)
// // {
// // 	for(int i = 0; i < map->height; i++)
// // 	{
// // 		for (int j = 0; j < map->height; j++)
// // 		{
// // 			render_cube(i * cube_width, j * cube_width, map->img, map->arr);
// // 		}
// // 	}
// // }

// // void render_player(t_map *map)
// // {
// // 	for (int i = 0; i < 10; i++)
// // 	{
// // 		for (int j = 0; j < 10; j++)
// // 		{
// // 			mlx_put_pixel(map->img, map->player->pos.x + j, map->player->pos.y + i, create_color(255, 0, 0, 255));
// // 		}
// // 	}
// // 	cast_rays(*map);
// // }

// // void	rendering(t_map *map)
// // {
// // 	render_map(map);
// // 	render_player(map);
// // }

// // void	raycasting(t_map *map)
// // {
// // 	init_player(map->player);
// // 	rendering(map);
// // }
