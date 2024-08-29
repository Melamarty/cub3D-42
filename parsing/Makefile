NAME   = cub3D
CC     = cc
CFLAGS = #-Wall -Wextra -Werror
RM     = rm -rf
RSRC := ../ray_casting/raycasting.c
SRC    := $(shell find . -name '*.c') $(RSRC)
OBJ    = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re