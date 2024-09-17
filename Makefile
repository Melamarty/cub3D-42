NAME   = cub3D
NAMEB  = cub3DB
CC     = cc
CFLAGS = -Wall -Wextra -Werror
RM     = rm -rf
RF     = mandatory/ray_casting
RFB    = bonus/ray_casting
RSRC = $(RF)/raycasting.c  $(RF)/utils1.c $(RF)/movement.c  $(RF)/ft_itoa.c $(RF)/calc_dis.c  \
		$(RF)/horz_cast.c $(RF)/vert_cast.c $(RF)/movement_utils.c $(RF)/utils2.c
RSRB = $(RFB)/raycasting_bonus.c  $(RFB)/utils1_bonus.c $(RFB)/movement_bonus.c  $(RFB)/ft_itoa_bonus.c $(RFB)/calc_dis_bonus.c  \
		$(RFB)/horz_cast_bonus.c $(RFB)/vert_cast_bonus.c $(RFB)/movement_utils_bonus.c $(RFB)/utils2_bonus.c \
		$(RFB)/animation_bonus.c $(RFB)/door_bonus.c $(RFB)/minimap_bonus.c $(RFB)/minimap_utils_bonus.c $(RFB)/mouse_bonus.c
SRC    = $(RSRC) $(shell find mandatory/parsing -name '*.c')
SRCB   = $(RSRB) $(shell find bonus/parsing -name '*.c')
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