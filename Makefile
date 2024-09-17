NAME   = cub3D
CC     = cc
CFLAGS = -Wall -Wextra -Werror
RM     = rm -rf
RF     = ./ray_casting
RSRC := $(RF)/raycasting.c $(RF)/minimap_bonus.c $(RF)/mouse_bonus.c $(RF)/utils1.c $(RF)/movement.c $(RF)/animation.c $(RF)/ft_itoa.c $(RF)/calc_dis.c $(RF)/door.c \
		$(RF)/horz_cast.c $(RF)/vert_cast.c $(RF)/minimap_bonus_utils.c $(RF)/movement_utils.c $(RF)/utils2.c
SRC    := $(RSRC) $(shell find ./parsing -name '*.c')
OBJ    = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ ./MLX42/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re