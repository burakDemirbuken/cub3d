NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -I includes/
# 03 flag
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_PATH = ./includes/minilibx_linux/
	MLX = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm -lz
else ifeq ($(UNAME_S), Darwin)
	MLX_PATH = ./includes/minilibx/
	MLX = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
endif

LIBFT = includes/libft/libft.a

SRC =	src/main.c \
		src/key_mouse_hooks.c \
		src/game_loop/game_loop.c \
		src/game_loop/color_utils.c \
		src/game_loop/minimap.c \
		src/game_loop/paint_floor_ceiling.c \
		src/game_loop/render_scene.c \
		src/game_loop/render_utils.c \
		src/game_loop/track_door.c \
		src/game_loop/update_player_status.c \
		src/ray_casting/initialize_rays.c \
		src/ray_casting/ray_casting_utils.c \
		src/ray_casting/ray_caster.c \
		src/configure_level/configure_level.c \
		src/configure_level/file_reading.c \
		src/configure_level/initialize_mlx.c \
		src/configure_level/separate_content.c \
		src/configure_level/set_elements.c \
		src/configure_level/set_game_map.c \
		src/configure_level/set_game_player.c \
		src/configure_level/set_game_sprites.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C includes/libft/
	make -C $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C includes/libft/
	make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C includes/libft/

re: fclean all

.PHONY: all clean fclean re
