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

SRCS_DIR	= 	./src/
SRC			= 	$(addprefix $(SRCS_DIR), $(SRCS_FILES))
			
OBJ			= 	$(SRC:%.c=%.o)

LIBFT		=	lib/libft/libft.a
FT_PRINTF	=	lib/ft_printf/libftprintf.a
MLX			=	mlx/libmlx.a

all:		libft ft_printf $(NAME)

$(NAME):	$(OBJ) $(MLX) 
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

libft:
			@$(MAKE) -C lib/libft/

ft_printf:
			@$(MAKE) -C lib/ft_printf/

$(MLX):
			@$(MAKE) -C mlx/

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

