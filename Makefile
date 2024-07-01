NAME = cub3d

CC = cc
FLAGS = -Wall -Wextra -Werror -I include/ ###!
MLX = -Linclude/minilibx/ -lmlx -framework OpenGL -framework AppKit
LIBFT = include/libft/libft.a

SRC = src/cub3d.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C include/libft/
	make -C include/minilibx/
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C include/libft/
	make clean -C include/minilibx/

fclean: clean
	rm -f $(NAME)
	make fclean -C include/libft/

re: fclean all

.PHONY: all clean fclean re
