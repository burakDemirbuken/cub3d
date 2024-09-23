NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -I includes/

MLX_PATH = ./includes/minilibx/
MLX = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

LIBFT = includes/libft/libft.a

SRC =	mandatory/src/main.c \
		mandatory/src/key_mouse_hooks.c \
		mandatory/src/game_loop/game_loop.c \
		mandatory/src/game_loop/color_utils.c \
		mandatory/src/game_loop/paint_floor_ceiling.c \
		mandatory/src/game_loop/render_scene.c \
		mandatory/src/game_loop/render_utils.c \
		mandatory/src/game_loop/update_player_status.c \
		mandatory/src/ray_casting/initialize_rays.c \
		mandatory/src/ray_casting/ray_casting_utils.c \
		mandatory/src/ray_casting/ray_caster.c \
		mandatory/src/configure_level/configure_level.c \
		mandatory/src/configure_level/file_reading.c \
		mandatory/src/configure_level/initialize_mlx.c \
		mandatory/src/configure_level/separate_content.c \
		mandatory/src/configure_level/set_elements.c \
		mandatory/src/configure_level/set_game_map.c \
		mandatory/src/configure_level/set_game_player.c \
		mandatory/src/configure_level/set_game_sprites.c \

OBJ = $(SRC:.c=.o)

BONUS_SRC =	bonus/src/main.c \
		bonus/src/key_mouse_hooks.c \
		bonus/src/game_loop/game_loop.c \
		bonus/src/game_loop/color_utils.c \
		bonus/src/game_loop/minimap.c \
		bonus/src/game_loop/paint_floor_ceiling.c \
		bonus/src/game_loop/render_scene.c \
		bonus/src/game_loop/render_utils.c \
		bonus/src/game_loop/track_door.c \
		bonus/src/game_loop/update_player_status.c \
		bonus/src/ray_casting/initialize_rays.c \
		bonus/src/ray_casting/ray_casting_utils.c \
		bonus/src/ray_casting/ray_caster.c \
		bonus/src/configure_level/configure_level.c \
		bonus/src/configure_level/file_reading.c \
		bonus/src/configure_level/initialize_mlx.c \
		bonus/src/configure_level/separate_content.c \
		bonus/src/configure_level/set_elements.c \
		bonus/src/configure_level/set_game_map.c \
		bonus/src/configure_level/set_game_player.c \
		bonus/src/configure_level/set_game_sprites.c \

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	make -C includes/libft/
	make -C $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	make -C includes/libft/
	make -C $(MLX_PATH)
	$(CC) $(FLAGS) $(BONUS_OBJ) $(LIBFT) $(MLX) -o $(BONUS_NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)
	make clean -C includes/libft/
	make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C includes/libft/

re: fclean all

.PHONY: all clean fclean re
