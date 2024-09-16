NAME = cub3d

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

SRC =	src/game_loop/main.c \
		src/game_loop/minimap.c \
		src/game_loop/cub3d_utils.c \
		src/game_loop/key_hook.c \
		src/game_loop/game_loop.c \
		src/game_loop/update_player_status.c \
		src/game_loop/render_scene.c \
		src/game_loop/paint_floor_ceiling.c \
		src/game_loop/color.c \
		src/game_loop/track_door.c \
		src/ray_casting/initialize_rays.c \
		src/ray_casting/ray_casting_utils.c \
		src/ray_casting/ray_caster.c \
		src/level_utils/configure_level.c \
		src/level_utils/file_reading.c \
		src/level_utils/initialize_mlx.c \
		src/level_utils/print_map.c \
		src/level_utils/separate_content.c \
		src/level_utils/set_elements.c \
		src/level_utils/set_game_map.c \
		src/level_utils/set_game_player.c \
		src/level_utils/set_game_sprites.c \

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
