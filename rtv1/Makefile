# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/30 19:59:01 by vcombey           #+#    #+#              #
#    Updated: 2017/09/27 00:35:14 by vcombey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

APPEND=
ASAN=
TEST_FILE=

OPTIMIZATION ?= -O0

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address
endif

NAME =	rtv1

SRC =	main.c			\
		mlx/key_pressed.c	\
		mlx/move_arrows.c	\
		mlx/rot_obj.c	\
		mlx/key_event.c	\
		mlx/env.c			\
		parsing/parse_lights.c	\
		parsing/parsing.c	\
		parsing/parse_scene.c	\
		parsing/parse_objects.c	\
		parsing/get_coordinates.c	\
		parsing/init_cam_dir.c	\
		opencl/cl_methods.c \
		opencl/cl_methods2.c	\
		mouse/mouse_ray.c \
		mouse/matrix.c \
		mouse/opp_double.c \
		mouse/opp_double_vect.c \
		mouse/opp_vect.c \
		mouse/rot.c \
		mouse/figures.c	\

INCLUDE = -I ./libft -I ./includes -I ./minilibx_macos/

OBJS = $(addprefix objs/, $(SRC:.c=.o))

CFLAGS += -Wall -g3 -O0 -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	@gcc -g $(OBJS) $(SANITIZER) -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework OpenCl -framework AppKit -g3 -O0 -o $(NAME)

clean:
	make clean -C ./libft/
	/bin/rm -rf objs

fclean: clean
	/bin/rm -f ./libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all

objs/%.o : src/%.c
	@mkdir -p ./objs/mouse
	@mkdir -p ./objs/opencl
	@mkdir -p ./objs/mlx
	@mkdir -p ./objs/parsing
	@/bin/mkdir -p objs
	gcc $(INCLUDE) $(SANITIZER) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re
