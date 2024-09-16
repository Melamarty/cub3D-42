#ifndef PARSING_H
#define PARSING_H

#define m_cube 30
#define WIDTH 1200
#define HEIGHT 700
#define TILE_SIZE 300
#define HIT_HORZ 1
#define HIT_VIRT 2

#include "MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include "parsing/gnl/get_next_line.h"
#include <stdio.h>
#include <limits.h>

// raycasting ************************************
typedef struct s_ray
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
    double  rx;
    double  ry;
    int map_x;
    int map_y;
	int	steps;
	double	xinc;
	double	yinc;
    double  ray_angle;
    int     x_inter;
    int     y_inter;
    double  ray_dis;
    int     ray_dir; // 1: hor | 2: ver
    int     is_door;
    int     is_close_door;
    int     x_door;
    int     y_door;
    double  f_x_inter;
    double  f_y_inter;
    int is_right;
    int is_up;
    double x_steps;
    double y_steps;
    int found_x_inter;
    int found_y_inter;
    double h_x_inter;
    double v_x_inter;
    double h_y_inter;
    double v_y_inter;
    double  h_dis;
    double  v_dis;
    double  c_door_dis;
    struct s_ray    *next;
}	t_ray;
// void render_map(mlx_image_t *img, char **s);
// void	rendering(the_data *data);

// raycasting ************************************


//structs

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_mmpam
{
    double          x;
    double          y;
    int				x_start;
	int				y_start;
	int				y_start_save;
	unsigned int	color;
    int             i;
    int             j;
} t_mmap;

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

typedef struct s_texture
{
    mlx_image_t *no;
    mlx_image_t *so;
    mlx_image_t *ea;
    mlx_image_t *we;
    mlx_image_t *door;
    mlx_image_t *curr;
} t_texture;
typedef struct s_map {
    void *mlx;
	mlx_image_t *img;
    t_player *player;
    t_ray    rays[1200];
    t_ray    *m_rays;
    int line_width;
    int width;
    int height;
    char **arr;
    t_color *floor;
    t_color *ceiling;
    char *no;
    char *so;
    char *we;
    char *ea;
    //char *texture;
    int is_error;
    int is_rot;
    t_texture *texture;
    mlx_texture_t   *sprite[31];
    mlx_texture_t   *bullet[10];
    mlx_image_t     *sprite_img;
    mlx_image_t     *bullet_img;
    int timing;
    int frame;
    int is_reload;
    int is_shot;
    t_ray   *door_ray;
    int     can_open;
    int     can_close;
    int     bullet_nb;
    mlx_texture_t   *txts[5];
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

typedef struct s_wall
{
    int     top;
    int     botm;
    int     x;
}   t_wall;


// raycasting ***********************
void    handle_key(void *p);
void    init_player(t_map *map);
void	mini_map(t_map *map);
void    cast_rays(t_map *map);
void	mouse_handler(double x, double y, void *p);
double  normangle(double angle);
void	mouse_rot(void *p);
void	add_back_ray(t_ray **rays, t_ray *new_ray);
unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void	mini_map(t_map *map);
void mouse_handler(double x, double y, void *p);
void	mouse_rot(void *p);
double normangle(double angle);
void	up(t_map *map);
void	down(t_map *map);
void	left(t_map *map);
void	right(t_map *map);
int	    is_wall(int new_x, int new_y, t_map map);
char	*ft_itoa(int n);
void	create_textures(t_map *map);
void	shot(t_map *map);
void	reload(t_map *map);
int	key_pressed(t_map *map);
void    animation(void *p);
double	calc_h_dis(t_map map, t_ray ray);
double	calc_v_dis(t_map map, t_ray ray);
double	calc_d_dis(t_map map, t_ray ray, int i);
void	open_door(t_map *map);
void	close_door(t_map *map);
void	check_horz(t_ray *new_ray, t_map *map);
void	check_vert(t_ray *new_ray, t_map *map);
void	get_color(t_mmap *mmap, t_map *map);
void	draw_rays(t_map *map);
void	up(t_map *map);
void	down(t_map *map);
void	left(t_map *map);
void	right(t_map *map);
void	clear_all(t_map *map);
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
int empty_line(char *line);
void get_map(t_list *list, t_map *map);
void set_null(t_map *map);
char *rm_spaces(char *line);
int is_digits(char *str);
int spl_len(char **spl);
char *get_texture(char *line);
int set_checked(t_list *list);
void clear_map(t_map *map);
int check_player(char **map, int height);
void optimize_map(t_map *map);
int	get_player_pos(t_map *map);

t_map *parse_map(t_list *list);
int check_arr(t_map *map);
int check_textures (t_map *map, t_list *list);
int empty_line(char *line);
int check_walls(char **map, int height, int width);
void render(t_map *map);
unsigned int create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void	draw_ceill(t_map *map, int topPixel, int i);
void	draw_floor(t_map *map, int bottomPixel, int i);
t_wall	*get_wall_info(int top, int bottom, int x);

#endif