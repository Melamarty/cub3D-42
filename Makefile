NAME   = cub3D
CC     = cc
CFLAGS = #-Wall -Wextra -Werror
RM     = rm -rf
RF     = ./ray_casting
RSRC := $(RF)/raycasting.c $(RF)/minimap_bonus.c $(RF)/mouse_bonus.c $(RF)/utils1.c $(RF)/movement.c $(RF)/animation.c $(RF)/ft_itoa.c $(RF)/calc_dis.c $(RF)/door.c
SRC    := $(shell find ./parsing -name '*.c') $(RSRC)
OBJ    = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ ./MLX42/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

%.o: %.c parsing.h
	$(CC) $(CFLAGS) -c -Imlx $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re