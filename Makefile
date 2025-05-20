CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -g
RM 			= 	rm -rf

NAME 		= 	cub3D
HEADER 		= 	src/cub3D.h

SRCS_FILES	= 	check_lines_before_map.c \
				convert_to_map.c \
				create_local_file_copy.c \
				extract_color.c \
				extract_scene_path.c \
				get_scene_elements.c \
				is_valid_map.c \
				main.c \
				utils.c

RENDER_FILES	=	render/utils.c \
				render/render.c \
				render/move.c \
				render/move_checks.c \
				render/key.c \
				render/initialize.c \
				render/dda.c

SRCS_DIR	= 	./src/
SRC			= 	$(addprefix $(SRCS_DIR), $(SRCS_FILES)) \
				$(addprefix $(SRCS_DIR), $(RENDER_FILES))
			
OBJ			= 	$(SRC:%.c=%.o)

LIBFT		=	lib/libft/libft.a
FT_PRINTF	=	lib/ft_printf/libftprintf.a
MLX_DIR 	= mlx
MLX 		= $(MLX_DIR)/libmlx.a
MFLAGS 		= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

ifeq ($(shell uname), Linux)
	MLX_DIR = mlx_linux
	MLX = $(MLX_DIR)/libmlx.a
	MFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

all:		libft ft_printf $(MLX) $(NAME)

$(NAME):	$(OBJ) $(MLX) 
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

libft:
			@$(MAKE) -C lib/libft/

ft_printf:
			@$(MAKE) -C lib/ft_printf/

$(MLX):
			@$(MAKE) -C $(MLX_DIR)

clean:
			@$(RM) $(OBJ)
			@$(MAKE) -C lib/libft/ clean
			@$(MAKE) -C lib/ft_printf/ clean
			@$(MAKE) -C mlx clean

fclean:		clean
			@$(MAKE) -C lib/libft/ fclean
			@$(MAKE) -C lib/ft_printf/ fclean
			@$(MAKE) -C mlx clean
			@$(RM) $(NAME) 

re:			fclean all

.PHONY:		all	clean fclean re

