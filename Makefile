
NAME = cub3D

CC = gcc

CFLAGS = -Werror -Wextra -Wall

RM = rm -rf

SRCS_LINUX = 	src_linux/dlst.c\
		src_linux/draw.c\
		src_linux/free.c\
		src_linux/init.c\
		src_linux/keys.c\
		src_linux/main.c\
	    src_linux/raycaster.c\
		src_linux/raycaster2.c\
		src_linux/split1.c\
		src_linux/up_param.c\
		src_linux/utils.c\
		src_linux/utils2.c\
		src_linux/utils3.c\
		src_linux/parsing/check_map.c\
		src_linux/parsing/colors.c\
		src_linux/parsing/cp_map.c\
		src_linux/parsing/map_elem.c\
		src_linux/parsing/parsing.c\
		src_linux/parsing/parsing_utils.c\
		src_linux/parsing/parsing_utils2.c\
		src_linux/parsing/read_file.c

SRCS_MACOS = 	src_macos/dlst.c\
		src_macos/draw.c\
		src_macos/free.c\
		src_macos/init.c\
		src_macos/keys.c\
		src_macos/main.c\
	    src_macos/raycaster.c\
		src_macos/raycaster2.c\
		src_macos/split1.c\
		src_macos/up_param.c\
		src_macos/utils.c\
		src_macos/utils2.c\
		src_macos/utils3.c\
		src_macos/parsing/check_map.c\
		src_macos/parsing/colors.c\
		src_macos/parsing/cp_map.c\
		src_macos/parsing/map_elem.c\
		src_macos/parsing/parsing.c\
		src_macos/parsing/parsing_utils.c\
		src_macos/parsing/parsing_utils2.c\
		src_macos/parsing/read_file.c

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -Lmlx_linux -lmlx_Linux -Lminilibx-linux -Imlx_linux -lXext -lX11 -lm -lz
	MLX 			= minilibx-linux
	SRCS 			= $(SRCS_LINUX)
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -I minilibx -L minilibx_macos -lmlx -framework OpenGL -framework AppKit
	MLX 			= minilibx_macos
	SRCS 			= $(SRCS_MACOS)
endif

$(NAME) : ${SRCS}
	make all -C $(MLX)
	make bonus -C libft/libft/
	gcc $(CFLAGS) $(SRCS) libft/libft/libft.a $(LIBS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make clean -C $(MLX)
	make fclean -C libft/libft

clean :
	$(RM) $(NAME)
	make clean -C $(MLX)
	make clean -C libft/libft


re : fclean all
