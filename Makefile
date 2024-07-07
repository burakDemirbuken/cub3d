NAME = cub3d

CC = cc
FLAGS = -Wall -Wextra -Werror -I include/

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_PATH = ./include/minilibx_linux/
	MLX = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm -lz
else ifeq ($(UNAME_S), Darwin)
	MLX_PATH = ./include/minilibx/
	MLX = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

LIBFT = include/libft/libft.a

SRC = src/cub3d.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C include/libft/
	make -C $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C include/libft/
	make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C include/libft/

re: fclean all

.PHONY: all clean fclean re
