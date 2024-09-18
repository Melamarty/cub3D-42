NAME   = cub3D
NAMEB  = cub3DB
CC     = cc
CFLAGS = -Wall -Wextra -Werror
RM     = rm -rf
RF     = mandatory/ray_casting
RFB    = bonus/ray_casting
PR = mandatory/parsing
PRB = bonus/parsing
RSRC = $(RF)/raycasting.c  $(RF)/utils1.c $(RF)/movement.c  $(RF)/ft_itoa.c $(RF)/calc_dis.c  \
		$(RF)/horz_cast.c $(RF)/vert_cast.c $(RF)/movement_utils.c $(RF)/utils2.c
RSRB = $(RFB)/raycasting_bonus.c  $(RFB)/utils1_bonus.c $(RFB)/movement_bonus.c  $(RFB)/ft_itoa_bonus.c $(RFB)/calc_dis_bonus.c  \
		$(RFB)/horz_cast_bonus.c $(RFB)/vert_cast_bonus.c $(RFB)/movement_utils_bonus.c $(RFB)/utils2_bonus.c \
		$(RFB)/animation_bonus.c $(RFB)/door_bonus.c $(RFB)/minimap_bonus.c $(RFB)/minimap_utils_bonus.c $(RFB)/mouse_bonus.c
UTILS = $(PR)/utils/ft_atoi.c $(PR)/utils/ft_split.c $(PR)/utils/my_malloc.c $(PR)/utils/utils1.c $(PR)/utils/lst_utils.c
GNL = $(PR)/gnl/get_next_line.c $(PR)/gnl/get_next_line_utils.c
SRC    = $(RSRC) $(PR)/check_map.c $(PR)/check_walls.c $(PR)/get_map.c $(PR)/main.c $(PR)/map_utils.c $(PR)/parse_map.c \
		 $(PR)/render_utils.c $(PR)/render.c $(PR)/utils2.c $(UTILS) $(GNL)

UTILSB = $(PRB)/utils/ft_atoi_bonus.c $(PRB)/utils/ft_split_bonus.c $(PRB)/utils/my_malloc_bonus.c $(PRB)/utils/utils1_bonus.c $(PRB)/utils/lst_utils_bonus.c
GNLB = $(PRB)/gnl/get_next_line_bonus.c $(PRB)/gnl/get_next_line_utils_bonus.c
SRCB   = $(RSRB) $(PRB)/check_map_bonus.c $(PRB)/check_walls_bonus.c $(PRB)/get_map_bonus.c $(PRB)/main_bonus.c $(PRB)/map_utils_bonus.c $(PRB)/parse_map_bonus.c \
		 $(PRB)/render_utils_bonus.c $(PRB)/render_bonus.c $(PRB)/utils2_bonus.c $(UTILSB) $(GNLB)
OBJ    = $(SRC:.c=.o)
OBJB    = $(SRCB:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ ./MLX42/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

$(NAMEB): $(OBJB)
	$(CC) $(CFLAGS) $^ -o $@ ./MLX42/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

mandatory/%.o: mandatory/%.c mandatory/cub3d_bonus.h
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

bonus/%.o: bonus/%.c bonus/cub3d_bonus.h
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

all : $(NAME)

bonus : $(NAMEB)

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJB)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAMEB)

re : fclean all

.PHONY : all clean fclean re