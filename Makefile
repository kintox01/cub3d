
NAME = cub3D

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I minilibx -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

SRCS = 	src/dlst.c\
		src/draw.c\
		src/free.c\
		src/init.c\
		src/keys.c\
		src/main.c\
	    src/raycaster.c\
		src/raycaster2.c\
		src/split1.c\
		src/up_param.c\
		src/utils.c\
		src/utils2.c\
		src/utils3.c\
		src/parsing/check_map.c\
		src/parsing/colors.c\
		src/parsing/cp_map.c\
		src/parsing/map_elem.c\
		src/parsing/parsing.c\
		src/parsing/parsing_utils.c\
		src/parsing/parsing_utils2.c\
		src/parsing/read_file.c



$(NAME) : ${SRCS}
	make all -C minilibx_macos
	make bonus -C libft
	gcc $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make clean -C minilibx_macos
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C minilibx_macos
	make clean -C libft

re : fclean all
