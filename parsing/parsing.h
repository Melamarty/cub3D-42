#ifndef PARSING_H
#define PARSING_H

#define cube_width 60


#include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./gnl/get_next_line.h"
#include <stdio.h>
#include <limits.h>

// raycasting ************************************
typedef struct the_rays
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	steps;
	double	xinc;
	double	yinc;
    double  ray_angle;
    int     x_inter;
    int     y_inter;
    double  ray_dis;
    int     ray_dir; // 1: hor | 2: ver
    struct the_rays    *next;
}	the_rays;
// void render_map(mlx_image_t *img, char **s);
// void	rendering(the_data *data);

// raycasting ************************************


//structs

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_pos
{
    int x;
    int y;
} t_pos;

typedef struct s_player
{
    t_pos pos;
    char    dir;
    int xDir;
	int yDir;
	double rotAngle;
	int moveSpeed;
	double rotSpeed;
	double	fov;
} t_player;

typedef struct s_map {
    void *mlx;
	mlx_image_t *img;
    t_player *player;
    the_rays    *rays;
    int line_width;
    int width;
    int height;
    char **arr;
    t_color floor;
    t_color ceiling;
    char *no;
    char *so;
    char *we;
    char *ea ;
    int is_error;
} t_map;

typedef struct s_adress
{
	void			*addr;
	int				fd;
	struct s_adress	*next;
}	t_adress;

typedef struct s_list
{
    char            *line;
    struct s_list   *last;
    struct s_list   *next;
    int             checked;
} t_list;


// raycasting ***********************
void    raycasting(t_map *map);
void    handle_key(mlx_key_data_t keydata, void *p);
void init_player(t_map *map);
// raycasting ***********************


//utils
void ft_putstr(char *str, int fd);
void print_list(t_list *list);
void add_line(t_list **list, const char *line);
void free_list(t_list *head);
int lst_len(t_list **list);
int	ft_strncmp(char *str1, char *str2, int n);
char **ft_split(const char *s, char c);
int    ft_atoi(const char *str);
void	*my_malloc(size_t size, int mode);
int	ft_strcmp(char *str1, char *str2);

t_map *parse_map(t_list *list);
int check_arr(t_map *map);
int check_textures (t_list *list);
int empty_line(char *line);
int check_walls(char **map, int height, int width);
void render(t_map *map);
unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif